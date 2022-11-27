#pragma once
#include <string>
#include "json.hpp"
using namespace std;

class Book {
private:
    string isbn;
    string title;
    string author;
    string publisher;
    int year;
    int num_of_available_books;
    int num_of_borrowed_books;

public:
    Book();
    Book(const Book& book);
    Book(json::JSON obj);

    string get_isbn() const;
    string get_title() const;
    string get_author() const;
    string get_publisher() const;
    int get_year() const;
    int get_num_of_available_books() const;
    int get_num_of_borrowed_books() const;
    json::JSON get_json() const;

    void set_isbn(string _isbn);
    void set_title(string _title);
    void set_author(string _author);
    void set_publisher(string _publisher);
    void set_year(int _year);
    void set_num_of_available_books(int _num_of_available_books);
    void set_num_of_borrowed_books(int _num_of_borrowed_books);

    void add_book_stock(int amount);
    bool remove_available_book_stock(int amount);
    bool borrow_book(int ampunt);
    bool return_book(int amount);
};