# su-dsa-library

## Overview

Manage a large entry of books and users for an average sized library. The system will be able to:
- Search books based on ISBN, title, author, and publisher (as a guest, user, and admin)
- Create new books, delete existing books, and modify an existing book given an ISBN (for admin)
- Add or remove book stocks given an ISBN (for admin)
- Register a new user and a user login system
- Allow user to borrow and return a book from the library 
- Show users information and their currently borrowed books (for admin)

Data structure, algorithm, and data used:
- B+Tree, for both books and users. Fast single operation (O(log N)), relatively fast to return all values (O(N)), compared to other BST.
- Linked list to store history and user's borrowed books.
- Data persistent using JSON. Used third party [SimpleJSON](github.com/nbsdx/SimpleJSON) library for C++ to JSON parser and vice versa.
- [Books data set](www.kaggle.com/datasets/saurabhbagchi/books-dataset) and [Mockaroo](www.mockaroo.com) for users data set.

## How to build and run

1. Compile the `main.cpp` program
2. Run the `main.exe`
