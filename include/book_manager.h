#pragma once
#include <vector>
#include "bplustree.h"
#include "book.h"
using namespace std;

class BookManager {
private:
    BPlusTree<string, Book> data;

public:
    BookManager();
    BookManager(const string& file_location);
    void load_data(const string& file_location);
    void save_data(const string& file_location);

    int get_num_of_books();

    // returns a copy of the book
    vector<Book> get_all_books() const;
    Book get_book_by_isbn(string isbn) const;

    bool create_book(const Book& book);
    bool delete_book(string isbn);
    bool update_book(string old_isbn, const Book& book);

    bool add_book_stock(string isbn, int amount);
    bool remove_book_stock(string isbn, int amount);
    bool borrow_book(string isbn, int amount);
    bool return_book(string isbn, int amount);
};