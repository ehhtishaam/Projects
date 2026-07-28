# Online Library Management System (BST-based)

A console-based library management system in C++ that uses a **Binary Search Tree (BST)**, keyed on ISBN, to store, search, and manage book records efficiently.

Built as a DSA final-term project (3rd semester) to actually apply BST concepts — insertion, deletion with all three node-removal cases, and traversals — instead of just knowing them theoretically.

## Features

- **Insert** a book by ISBN, title, author, genre, and year, with duplicate-ISBN detection
- **Search by ISBN** — reports the number of comparisons made, showing BST search efficiency in action
- **Search by title** — case-insensitive in-order search across the tree
- **Delete** a book — full recursive deletion handling all three BST cases (leaf, one child, two children via in-order successor)
- **Traversals** — in-order (sorted by ISBN), pre-order, and post-order display
- **Tree height tracking** — shown live in the main menu
- **File persistence** — save/load the library to/from a pipe-delimited text file, with auto-load on startup and auto-save on exit

## Data structure

Each book is stored in a `Node` containing a `Book` struct (ISBN, title, author, genre, year) plus `left`/`right` child pointers. The tree is ordered by ISBN, giving O(log n) average-case insert, search, and delete on a reasonably balanced tree, and O(n) in the worst case (e.g. sorted insertion order).

## How to run

```bash
g++ -o library LibraryManagementSystem.cpp
./library
```

On startup the program auto-loads `library.txt` if present in the same directory (a sample file with 12 books is included). Data is auto-saved back to `library.txt` on exit, and can also be saved/loaded manually from the menu.

## Menu options

```
1. Insert a Book
2. Search by ISBN
3. Search by Title
4. Delete a Book
5. Display All Books (In-order / Sorted)
6. Display Pre-order Traversal
7. Display Post-order Traversal
8. Save Library to File
9. Load Library from File
0. Exit & Save
```

## Tech

- C++ (STL: `vector`, `fstream`, `sstream`, `algorithm`)
- No external dependencies
