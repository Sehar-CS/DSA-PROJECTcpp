# Library Management System (C++)

A console-based Library Management System that combines the data-structure concepts practiced in Labs 01–07.

## Project structure

```text
Library_Management_System/
├── main.cpp
├── structures.h
├── Library.h
├── Library.cpp
└── README.md
```

## Lab concepts included

| Lab | Data structure | Use in this project |
|---|---|---|
| Lab 01 | Singly linked list | Student records |
| Lab 02 | Stack (LIFO) | Recently viewed book history |
| Lab 03 | Queue (FIFO) | Normal book requests |
| Lab 04 | Priority queue | High/medium/low priority requests |
| Lab 05 | Singly linked list operations | Add/remove/insert-at/remove-at/swap/sort/reverse/display books |
| Lab 06 | Circular linked list | Featured book rotation |
| Lab 07 | Doubly linked list | Browse books forward and backward |

## Compile and run on Windows

Open Command Prompt in this folder and run:

```bash
g++ main.cpp Library.cpp -o LibraryManagement.exe
LibraryManagement.exe
```

If you use VS Code, open this folder and run the same commands in its terminal.

## Important notes

- `main.cpp` contains the `main()` function and menu.
- `structures.h` contains all node structures.
- `Library.h` contains the `Library` class declaration.
- `Library.cpp` contains the class member-function definitions.
- All files are connected through header files.
- The program starts with three sample students and four sample books.
- Positions in insert/remove-at operations are zero-based (the first position is 0).
- Smaller priority values mean higher priority: 1 = High, 2 = Medium, 3 = Low.
- Book/student data is currently stored in memory and resets when the program closes. File saving can be added as a future feature.

## GitHub upload

Create a new GitHub repository named `Library-Management-System`, then upload these project files and commit them.
