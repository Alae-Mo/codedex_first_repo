# Binary Search Tree – C (TP)

This repository contains a **C program done in C data structures' class as a TP (practical work)**.  
The goal is to manipulate a **binary search tree (BST)** using dynamic memory and recursion.

The program is menu-based and runs in the terminal.

---

## What this program does

The program lets you:

- Create a binary search tree
- Display the tree:
  - In increasing order
  - In decreasing order
- Count:
  - Number of nodes
  - Number of leaves
- Display leaves in increasing order
- Calculate the depth of the tree
- Search for a value
- Delete a value from the tree
- Save the tree into a file
- Recreate the tree from a file

---

## How it works

- Each node contains:
  - an integer value
  - a left child
  - a right child
- Insertion follows **binary search tree rules**
- Most operations are done using **recursion**
- The tree can be saved and loaded using a text file (`tree.txt`)
- Everything is controlled through a simple menu

---

## Files

- `myTrees.c` → main source code
- `tree.txt` → file used to store the tree values

---

## How to compile and run

Compile:

```bash
gcc myTrees.c -o bst
```

Run:

```bash
./bst
```

Then choose actions using the menu.

---

## Notes

- This project was made for learning purposes (TP)
- Focus is on logic, recursion, and pointers
- No advanced optimizations
