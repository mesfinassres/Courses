# Student Record Management: OOP Example

## 1. Problem description

A school office keeps a text file of students. Each student has an ID, a name and
three test scores. The office wants a program that lets a clerk:

1. list all students with their average and letter grade,
2. look up one student by ID,
3. add a new student,
4. see the class average,
5. save the records back to the file.

## 2. Object-oriented analysis

### Step 1: List the nouns in the description

office, student, text file, ID, name, test scores, clerk, program, average, letter grade, class

### Step 2: Refine the list

| Candidate | Decision |
|---|---|
| student | **Class** (historical data: a record) |
| ID, name, test scores | Attributes of Student |
| average, letter grade | Behaviors of Student (calculated, not stored) |
| class / the set of students | **Class** `StudentRegistry` (collection of records) |
| text file | I/O device, handled by `StudentRegistry` |
| clerk, office, program | Human role / context, not classes (the clerk is the user of `main`) |

### Step 3: Attributes

| Class | Attributes |
|---|---|
| `Student` | `id`, `name`, `scores[3]` |
| `StudentRegistry` | `students` (a vector of `Student`) |

### Step 4: Behaviors (responsibilities)

| Class | Responsible to know | Responsible to do |
|---|---|---|
| `Student` | its id, name, scores | `getAverage()`, `getGrade()`, `display()`, `toFileLine()` |
| `StudentRegistry` | all its students | `loadFromFile()`, `saveToFile()`, `addStudent()`, `findById()`, `listAll()`, `classAverage()` |

### Step 5: Relationships

- `StudentRegistry` **has-a** (composition) collection of `Student` objects.
- `main()` **uses-a** (access) `StudentRegistry`.
- No inheritance is needed. It would be forced here, so we leave it out.

## 3. File layout (specification / implementation / client)

| File | Role |
|---|---|
| `Student.h` | Class specification, with header guard |
| `Student.cpp` | Class implementation |
| `StudentRegistry.h` | Class specification, with header guard |
| `StudentRegistry.cpp` | Class implementation |
| `main.cpp` | Client: menu that uses the classes |
| `students.txt` | Input file, one student per line: `id,name,score1,score2,score3` |

The client `#include`s the `.h` files and is compiled and linked with the `.cpp` files.
`Student` and `StudentRegistry` could be reused unchanged in another program.

## 4. Build and run

```
g++ main.cpp Student.cpp StudentRegistry.cpp -o students
./students            (on Windows: students.exe)
```

Run it from the folder that contains `students.txt`.
