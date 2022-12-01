#pragma once
#include <fstream>
#include <sstream>
#include "../include/book_manager.h"
#include "bplustree.cpp"
#include "book.cpp"
using namespace std;

BookManager::BookManager() 
{
	data = BPlusTree<string, Book>();
}

BookManager::BookManager(const string& file_location) 
{
	data = BPlusTree<string, Book>();
	load_data(file_location);    
}

void BookManager::load_data(const string& file_location) 
{
	ifstream input(file_location);
    stringstream buffer;
    buffer << input.rdbuf();
    json::JSON obj = json::JSON::Load(buffer.str());

    for (int i = 0; i < obj.length(); i++) {
        create_book(Book(obj[i]));
    }
}

void BookManager::save_data(const string& file_location) 
{
    json::JSON obj = json::Array();
    vector<Book> books = get_all_books();
    for (int i = 0; i < books.size(); i++) {
        obj.append(books[i].get_json());
    }
    ofstream output(file_location);
    output << obj.dump();
}

int BookManager::get_num_of_books() 
{
    return data.get_size();
}

vector<Book> BookManager::get_all_books() const 
{
    vector<Book*> books_ori = data.get_all_values();
    vector<Book> books_copy;
    
    for (auto it : books_ori)
    {
    	books_copy.push_back(Book(*it));
	}
	return books_copy;
}

Book BookManager::get_book_by_isbn(string isbn) const 
{
    Book* book = data.get_value(isbn);
    if (book == nullptr)
    {
    	return Book();
	}
	else 
	{
		return Book(*book);
	}
}

bool BookManager::create_book(const Book& book) 
{
    if (data.is_exist(book.get_isbn()))
    {
    	return false;
	}
	else
	{
		data.insert(book.get_isbn(), book);
		return true;
	}
}

bool BookManager::update_book(string old_isbn, const Book& book) 
{
    if (!data.is_exist(old_isbn))
    {
    	return false;
	}
	if (old_isbn != book.get_isbn() && data.is_exist(book.get_isbn()))
	{
		return false;
	}
	
	if (!delete_book(old_isbn))
	{
		cout << "An Unexpected Error has Occured.\n";
		return false;
	}
	
	if (!create_book(book))
	{
		cout << "An Unexpected Error has Occured.\n";
		return false;
	}
	return true;
}

bool BookManager::delete_book(string isbn) 
{
    return data.remove(isbn);
}

bool BookManager::add_book_stock(string isbn, int amount) 
{
    if (data.is_exist(isbn))
    {
    	data.get_value(isbn)->add_book_stock(amount);
    	return true;
	}
	else
	{
		return false;
	}
}

bool BookManager::remove_book_stock(string isbn, int amount) 
{
    if (data.is_exist(isbn))
    {
    	data.get_value(isbn)->remove_available_book_stock(amount);
    	return true;
	}
	else
	{
		return false;
	}
}

bool BookManager::borrow_book(string isbn, int amount) 
{
    if (data.is_exist(isbn))
    {
    	data.get_value(isbn)->borrow_book(amount);
    	return true;
	}
	else
	{
		return false;
	}
}

bool BookManager::return_book(string isbn, int amount) 
{
    if (data.is_exist(isbn))
    {
    	data.get_value(isbn)->return_book(amount);
    	return true;
	}
	else
	{
		return false;
	}
}
