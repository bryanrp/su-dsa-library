#pragma once
#include <list>
#include <string>
#include "json.hpp"
using namespace std;

class Book {
private:
    int serial;
    string name;
    int num_of_available_books;
    int num_of_borrowed_books;

public:
    Book();
    Book(const Book& book);
    Book(int _serial, string _name, int _num_of_available_books, int _num_of_borrowed_books);
    Book(json::JSON obj);

    int get_serial() const;
    string get_name() const;
    int get_num_of_available_books() const;
    int get_num_of_borrowed_books() const;
    json::JSON get_json() const;

    void set_serial(int _serial);
    void set_name(string _name);
    void set_num_of_available_books(int _num_of_available_books);
    void set_num_of_borrowed_books(int _num_of_borrowed_books);

    void add_book_stock(int amount);
    bool remove_available_book_stock(int amount);
    bool borrow_book(int ampunt);
    bool return_book(int amount);
};