# Project 1 — Kütüphane Yönetim Sistemi (Library Management System)

A full-featured **console-based Library Management System** written in C.  
The system manages books, authors, students, and borrow/return operations — all persisted to CSV files.

---

## 📁 Project Structure

```
project1/
├── main.c              # Main source file (2139 lines)
├── Kitaplar.csv        # Books database
├── KitapOrnekleri.csv  # Book copies database
├── KitapYazar.csv      # Book–Author relation table
├── KitapOdunc.csv      # Borrow/return transaction log
├── Ogrenciler.csv      # Students database
├── Yazarlar.csv        # Authors database
└── build/              # Compiled binaries (auto-generated, do not edit)
```

---

## 🧩 Data Structures

| Struct | Purpose |
|---|---|
| `YAZAR` | Singly-linked list of authors |
| `OGRENCI` | Doubly-linked list of students (with score/penalty) |
| `KITAP` | Singly-linked list of books |
| `KITAPORNEK` | Singly-linked list of physical book copies per book |
| `KITAPYAZAR` | Book–Author mapping (relation table) |
| `KITAPISLEM` | Borrow/return transaction log |

---

## ⚙️ Features

### 👤 Student Operations
- Add / Delete / Update student records
- Display student list
- List students with unreturned books
- List penalized students (negative score)
- Borrow a book / Return a book

### 📚 Book Operations
- Add / Delete / Update book records
- Display book list (bubble-sorted by title)
- List books currently on shelf (`RAFTA`)
- List books returned late (overdue)

### ✍️ Author Operations
- Add / Delete / Update author records
- Display author list

### 🔗 Book–Author Operations
- Link a book to an author

---

## 🗃️ CSV File Formats

| File | Format |
|---|---|
| `Kitaplar.csv` | `BookTitle, ISBN, CopyCount` |
| `Ogrenciler.csv` | `StudentID, FirstName, LastName, Score` |
| `Yazarlar.csv` | `FirstName, LastName, AuthorID` |
| `KitapYazar.csv` | `ISBN, AuthorID` |
| `KitapOdunc.csv` | `CopyID, StudentID, OperationType(0=Borrow/1=Return), Date` |
| `KitapOrnekleri.csv` | `CopyID, Status(RAFTA/ODUNC)` |

---

## 🔨 How to Build & Run

```bash
# Compile
gcc main.c -o build/library -lm

# Run (must be executed from project1/ directory so CSV files are found)
cd project1
./build/library
```

> ⚠️ The program reads/writes CSV files from the **current working directory**. Always run from inside `project1/`.

---

## 💡 Key Algorithms

- **Bubble Sort** on linked list for alphabetical book listing
- **Date arithmetic** to compute overdue days (`calculate_days_difference`)
- **Dynamic copy status tracking**: book copy statuses (`RAFTA`/`ODUNC`) are reconstructed from the transaction log on every startup
- **Penalty system**: students accumulate negative points for late returns

---

## 🗓️ Author

**Student ID:** 23011056  
**Course:** Yapısal Programlama (Structural Programming)
