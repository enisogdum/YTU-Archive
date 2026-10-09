# 1-2 Yapısal Programlama — Structural Programming

Course repository for **Structural Programming (Yapısal Programlama)**.  
All code is written in **C** and covers topics from basic control flow to multi-threaded programming.

---

## 📂 1-2 Documents & Resources

This repository contains documents and lecture notes from the 1st year, 2nd semester of Computer Engineering.

### 📘 Structural Programming (Yapısal Programlama)
- 📝 [Download lecture notes](https://drive.google.com/file/d/16ZB3k5zcPUCiIMu_g03waRz31FsT8maN/view?usp=drive_link)
- 📎 [Additional resources](https://drive.google.com/drive/folders/1IqbIgrmrWCerfSS48_3em_DvrKRChct0?usp=drive_link)

---

## 📁 Repository Structure

```
1-2YapısalProgramlama/
├── grades_letter/     # Course grades breakdown & official transcript PDF
├── projects/          # Term projects
│   └── project1/      # Library Management System (C, ~2100 lines)
├── homeworks/         # Homework assignments
│   ├── homework1/     # University Registration System
│   └── homework2/     # (Assignment PDF only)
├── labs/              # Lab exercises (two academic years)
│   ├── 2025/          # Lab sessions from 2025
│   │   ├── lab1/      # 2×N matrix intersection & value sum
│   │   ├── lab2/      # Dynamic memory: box volume packing
│   │   ├── lab3/      # Linked list: gym member management
│   │   └── lab4/      # Linked list: cargo tracking system
│   └── 2026/          # Lab sessions from 2026
│       ├── lab 1/     # NxN local maximum finder (pointer arithmetic)
│       ├── lab 2/     # Dynamic array: internship candidate selection
│       ├── lab 3/     # Linked list + function pointers: tech-fair participants
│       └── lab 4/     # Linked list + binary file I/O: music streaming
└── samples/           # In-class lecture examples & practice exercises (weeks 1–11)
```

---

## 🗂️ Section Overviews

### 🏗️ Projects

| Project | Description | Lines |
|---|---|---|
| [project1](./projects/project1/) | Library Management System — books, authors, students, borrow/return with CSV persistence | ~2100 |

### 📝 Homeworks

| Homework | Description |
|---|---|
| [homework1](./homeworks/homework1/) | University Registration System — dynamic student & course management (C) |
| [homework2](./homeworks/homework2/) | Assignment PDF (solution not submitted) |

### 🔬 Labs — 2025

| Lab | Topic | Key Concepts |
|---|---|---|
| [lab1](./labs/2025/lab1/) | Matrix intersection value sum | 2D arrays, pointer arithmetic |
| [lab2](./labs/2025/lab2/) | Box packing volume calculator | Dynamic memory (`calloc/realloc`), 2D matrix |
| [lab3](./labs/2025/lab3/) | Gym member & service management | Linked list, dynamic strings |
| [lab4](./labs/2025/lab4/) | Cargo tracking & reporting | Linked list, file I/O, sorting |

### 🔬 Labs — 2026

| Lab | Topic | Key Concepts |
|---|---|---|
| [lab 1](./labs/2026/lab%201/) | NxN local maximum finder | Pointer arithmetic, dynamic 2D array |
| [lab 2](./labs/2026/lab%202/) | Internship candidate selection | Dynamic array, `realloc`, structs |
| [lab 3](./labs/2026/lab%203/) | Tech-fair participant management | Linked list, function pointers, recursion |
| [lab 4](./labs/2026/lab%204/) | Music streaming system | Linked list, binary file I/O (`.dat`) |

### 📖 Lecture Code (hit_code)

| Week | Topics Covered |
|---|---|
| Week 1 | Precedence/associativity, `enum`, `switch`, `continue`, float, increment, null, do-while |
| Week 2 | Pointer arithmetic, null pointer, pointer-to-pointer, array access via pointers, bit operations |
| Week 3 | Functions (call by value/ref), array functions, matrix functions, bubble sort on strings |
| Week 4 | Transposition, dynamic arrays, 2D dynamic matrix, memory layout |
| Week 5 | Pointers on arrays, scope & duration, `stringDynamic`, matrix stepping |
| Week 6 | Structures, self-referencing structs, early linked list |
| Week 7 | Recursion (factorial, power, Fibonacci), union, bit fields, connected components |
| Week 8 | Struct copying, linked list (add/sort), function-pointer-based object sort |
| Week 9 | File open/close, line/char/formatted I/O, random access |
| Week 10 | Function pointers & arrays, file random access |
| Week 11 | Command-line arguments, `getopt`, macros (`#define`, `__LINE__`), threads (intro, mutex, matrix fill & multiplication) |

---

## 🔨 Building Any C File

```bash
# Generic one-file build
gcc <source.c> -o <output> -lm

# Example: build the project
cd projects/project1
gcc main.c -o build/library
./build/library

# Example: build a lab
cd labs/2026/lab\ 1
gcc kod.c -o kod
./kod

# For threaded code (week 11)
gcc threadIntroPart3.c -o thread -lpthread
```

---

## 📚 Topics by Week (Curriculum Map)

```
Week 1  →  Basics & Control Flow
Week 2  →  Pointers
Week 3  →  Functions & Arrays
Week 4  →  Dynamic Memory Allocation
Week 5  →  Advanced Pointers & Scope
Week 6  →  Structures & Linked Lists
Week 7  →  Recursion, Union, Bit Fields
Week 8  →  Advanced Linked Lists
Week 9  →  File I/O
Week 10 →  Function Pointers
Week 11 →  Macros, Command-Line, Multi-threading
```

---

