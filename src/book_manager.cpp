#pragma once
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
	
}

void BookManager::save_data(const string& file_location) 
{
    
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
