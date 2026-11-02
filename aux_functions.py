import matplotlib.pyplot as plt
import tensorflow.keras as keras
from IPython.display import clear_output
import pandas as pd
import numpy as np

def plot_acc_loss(training_history, logx=False, logy=False, var1=None, var2=None):
    fig, axs = plt.subplots(1, 2, figsize=(12,4))
    if logx==True:
        axs[0].set_xscale("log", nonposx='clip')
        axs[1].set_xscale("log", nonposx='clip')
    if logy==True:
        axs[0].set_yscale("log", nonposy='clip')
        axs[1].set_yscale("log", nonposy='clip')

    if var1!=None:
        axs[0].plot(training_history.history[var1])
        axs[0].plot(training_history.history['val_'+var1])
        axs[0].set_ylabel(var1)
        axs[0].set_xlabel('Epoch')
        axs[0].legend(['Train', 'Validation'], loc='upper left')

    if var2!=None:
    # Plot training & validation loss values
        axs[1].plot(training_history.history[var2])
        axs[1].plot(training_history.history['val_'+var2])
        axs[1].set_ylabel(var2)
        axs[1].set_xlabel('Epoch')
        axs[1].legend(['Train', 'Validation'], loc='upper left')

# updatable plot
# a minimal example (sort of) https://gist.github.com/stared/dfb4dfaf6d9a8501cd1cc8b8cb806d2e
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
        plt.plot(self.x, self.losses, label="loss")
        plt.plot(self.x, self.val_losses, label="val_loss")
        plt.legend()
        plt.show();

plot_losses = PlotLosses()

def load_data(filename):

    #Load all data
    store = pd.HDFStore(filename)
    plant = store.get('plant/plant1')
    gen0 = store.get('generator/generator0')
    gen1 = store.get('generator/generator1')
    gen2 = store.get('generator/generator2')
    gen3 = store.get('generator/generator3')
    gen4 = store.get('generator/generator4')
    gen5 = store.get('generator/generator5')
    resrv1 = store.get('reservoir/rsv1')
    resrv2 = store.get('reservoir/rsv2')
    store.close()

    df_in = pd.DataFrame()
    df_in['h_r1'] = np.array(resrv1['head'])
    df_in['h_r2'] = np.array(resrv2['head'])
    df_in['P_0'] = np.array(gen0['production'])
    df_in['P_1'] = np.array(gen1['production'])
    df_in['P_2'] = np.array(gen2['production'])
    df_in['P_3'] = np.array(gen3['production'])
    df_in['P_4'] = np.array(gen4['production'])
    df_in['P_5'] = np.array(gen5['production'])
    #    df_in['P_tot'] = plant['production'][:]
    
    df_out = pd.DataFrame()
    df_out['loss_head_0'] = np.array(gen0['head_loss'])
    df_out['loss_head_1'] = np.array(gen1['head_loss'])
    df_out['loss_head_2'] = np.array(gen2['head_loss'])
    df_out['loss_head_3'] = np.array(gen3['head_loss'])
    df_out['loss_head_4'] = np.array(gen4['head_loss'])
    df_out['loss_head_5'] = np.array(gen5['head_loss'])
    df_out['loss_tail'] = np.array(plant['tailrace_loss'])

    df = pd.concat([df_in, df_out], axis=1)

   
    return df
