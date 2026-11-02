import matplotlib.pyplot as plt
import tensorflow as tf
import tensorflow.keras as keras
from IPython.display import clear_output
import pandas as pd
import numpy as np
from skimage.segmentation import mark_boundaries
from lime import lime_image
import random

import cv2
import os
import seaborn as sns
from sklearn.metrics import classification_report


class PlotLosses(keras.callbacks.Callback):
    def on_train_begin(self, logs={}):
        self.i = 0
        self.x = []
        self.losses = []
        self.val_losses = []

        self.fig = plt.figure()

        self.logs = []

    def on_epoch_end(self, epoch, logs={}):

        self.logs.append(logs)
        self.x.append(self.i)
        self.losses.append(logs.get('loss'))
        self.val_losses.append(logs.get('val_loss'))
        self.i += 1

        clear_output(wait=True)
        plt.plot(self.x, self.losses, label="Training loss")
        plt.plot(self.x, self.val_losses, label="Validation loss")
        plt.legend()
        plt.show()
        
plot_losses = PlotLosses()


def read_images(data_dir:str, img_size:int=224) -> np.array:
    """
    Read and resize images from a given directory
    """
    data = [] 
    for img in os.listdir(data_dir):
        if '.jpg' in img:
            try:
                img_arr = cv2.imread(os.path.join(data_dir, img))[...,::-1] #convert BGR to RGB format
                resized_arr = cv2.resize(img_arr, (img_size, img_size)) # Reshaping images to preferred size
                data.append(resized_arr)
            except Exception as e:
                print(e)
                
    return np.array(data)

def plot_cm(cm, label_names) -> None:
    """
    Plots the confusion matrix.
    @param cm: confusion matrix as returned by sklearn.metrics.confusion_matrix.
    @param label_names: label names corresponding to the classes used in prediction. 
    """
    ax = plt.subplot()
    sns.heatmap(cm, annot=True, ax=ax, cmap='Reds')
    plt.title('Confusion matrix')
    ax.set_xlabel('Predicted labels')
    ax.set_ylabel('True labels')
    ax.set_title('Confusion Matrix')
    ax.xaxis.set_ticklabels(label_names)
    ax.yaxis.set_ticklabels(label_names)
    plt.show()
    
def plot_history(history) -> None:
    """
    Plots the training history of the algorithm expressed in the accuracy and loss values for training and validation data.
    """
    acc = history.history['accuracy']
    val_acc = history.history['val_accuracy']
    loss = history.history['loss']
    val_loss = history.history['val_loss']

    epochs_range = range(len(history.epoch))

    plt.figure(figsize=(15, 15))
    plt.subplot(2, 2, 1)
    plt.plot(epochs_range, acc, label='Training Accuracy')
    plt.plot(epochs_range, val_acc, label='Validation Accuracy')
    plt.ylim(0,1)
    plt.legend(loc='lower right')
    plt.title('Training and Validation Accuracy')

    plt.subplot(2, 2, 2)
    plt.plot(epochs_range, loss, label='Training Loss')
    plt.plot(epochs_range, val_loss, label='Validation Loss')
    plt.legend(loc='upper right')
    plt.title('Training and Validation Loss')
    plt.show()
    
def predict_labels(X, model):
    """
    Predict labels over the threshold of 0.5 as 1 and below as 0.
    @param X: input data
    @param model: trained model
    @return: a list model predictions (0 or 1) for the inputs
    """
    predictions = (model.predict(X)>0.5).astype("int32")[:,1]
    
    return predictions

def plot_predicted(y, y_pred, X, real_class, pred_class, class_dict, nr_pic=10):
    """
    Plot algorithm predictions with the specified real and predicted class.
    @param y: true labels
    @param y_pred: predicted labels
    @param X: input data (preprocessed images)
    @param real_class: the real class of the images to be plotted
    @param pred_class: the predicted class of the images to be plotted
    @param class_dict: a dictionary defining the classes in the form {label:name}, as used in training
    @param nr_pic: the total number of pictures to be plotted
    """
    
    n=0
    for i in range(0,len(y)):
        if n<nr_pic:
            if y[i]==real_class and y_pred[i]==pred_class:
                plt.imshow(X[i])
                plt.title("Faktisk: {0}, Predikert: {1}".format(class_dict[real_class], class_dict[pred_class]))
                plt.show()
                n+=1
                
def show_explanation(model, X, class_dict, pic_ind, negative=False):
    """
    Plot X[pic_ind] image, marking the segments which increase/decrease the probability of the class predicted by the model.
    Uses LimeImageExplainer().
    @param model: trained model
    @param X: input data (preprocessed images)
    @param class_dict: a dictionary defining the classes in the form {label:name}, as used in training
    @param pic_nr: the index defining which image should be plotted
    @param negative: if True then the image shows areas which decrease the probability of classifying the image 
                     as the predicted label
    """
    
    set_seed(7)
    explainer = lime_image.LimeImageExplainer()
    explanation = explainer.explain_instance(X[pic_ind].astype('double'), model.predict,  
                                         top_labels=2, hide_color=0, num_samples=500)
    shape = X[pic_ind].shape
    y_pred_i = predict_labels(X[pic_ind].reshape(1, shape[0], shape[1], shape[2]), model)
    num_features = 2
    
    if negative==False:
        temp_1, mask_1 = explanation.get_image_and_mask(explanation.top_labels[0], 
                                                        positive_only=True, 
                                                        num_features=num_features, 
                                                        hide_rest=True)
    else:
        temp_1, mask_1 = explanation.get_image_and_mask(explanation.top_labels[0], 
                                                        positive_only=False, 
                                                        negative_only=True, 
                                                        num_features=num_features, 
                                                        hide_rest=True)
    
    fig,(ax1,ax2) = plt.subplots(1, 2, figsize=(15,15))
    ax1.imshow(X[pic_ind])
    ax2.imshow(mark_boundaries(temp_1, mask_1))
    ax1.set_title("Predikert klasse: " + str(class_dict[y_pred_i.item()]))    
                
def print_classification_report(y, y_pred, label_names):
    """
    Printing the classification report without the macro avg and weighted avg. 
    """
    
    report = classification_report(y, y_pred, target_names=label_names)
    for line in report.split('\n')[0:6]:
        print(line)
        
def set_seed(seed=9, gpu=False):
    """
    Set the seed for reproducibility.
    """
    
    os.environ['PYTHONHASHSEED']=str(seed)
    random.seed(seed)
    tf.random.set_seed(seed)
    np.random.seed(seed)


    if gpu:
        os.environ["TF_DETERMINISTIC_OPS"] = str(seed)
    else:
        os.environ['CUDA_VISIBLE_DEVICES'] = ''

    return seed