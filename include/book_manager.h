#pragma once
#include <vector>
#include "bplustree.h"
#include "book.h"
using namespace std;

class BookManager {
private:
    BPlusTree<int, Book> data;
public:
    BookManager();
    BookManager(const string& file_location);
    void load_data(const string& file_location);
    void save_data(const string& file_location);

    int get_num_of_books();

    // returns a copy of the book
    vector<Book> get_all_books() const;
    Book get_book_by_serial(int serial) const;

    bool create_book(const Book& book);
    bool update_book(int old_serial, const Book& book);
    bool delete_book(int serial);

    bool add_book_stock(int serial, int amount);
    bool remove_book_stock(int serial, int amount);
    bool borrow_book(int serial, int amount);
    bool return_book(int serial, int amount);
};