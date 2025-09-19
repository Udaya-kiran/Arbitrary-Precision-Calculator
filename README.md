# Arbitrary Precision Calculator

A C-based calculator capable of performing arithmetic operations on **arbitrarily large integers** using doubly linked lists. Works like `bc` in Linux, handling numbers far beyond standard C types.

---

## 🚀 Features

- **Arithmetic Operations:** `+`, `-`, `x`, `/`  
- **Arbitrary Precision:** Supports numbers of any length  
- **Sign Support:** Handles positive and negative numbers correctly  
- **Interactive Mode:** Continue calculations without restarting  
- **Linked List Implementation:** Uses `Dlist` for storing digits  

---

## 💻 Usage

### Compile

```bash
gcc main.c apc.c -o apc
