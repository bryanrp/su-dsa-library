#include <conio.h>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <list>
#include <regex>
#include <vector>
#include "include/book_manager.h"
#include "include/user_manager.h"
#include "src/book_manager.cpp"
#include "src/user_manager.cpp"
using namespace std;

const string book_file_path = "books.json";
const string user_file_path = "users.json";
BookManager book_manager;
UserManager user_manager(user_file_path);
list<string> history;

int read_input_integer(int min, int max) {
    string input;
    int result;
    while (true) {
        cin >> input;
        try {
            result = stoi(input);
            if (result < min || result > max) {
                cout << "Input not in range [" << min << ',' << max << "]. Please input a number: ";
            }
            else {
                break;
            }
        }
        catch (...) {
            cout << "Input must be an integer. Please input a number: ";
        }
    }
    return result;
}

string read_input_line() {
    string str;
    while (true) {
        getline(cin, str);
        if (!str.empty()) {
            break;
        }
    }
    return str;
}

Book read_input_book() {
    Book book;

    cout << "Input ISBN: ";
    book.set_isbn(read_input_line());

    cout << "Input title: ";
    book.set_title(read_input_line());

    cout << "Input author: ";
    book.set_author(read_input_line());

    cout << "Input publisher: ";
    book.set_publisher(read_input_line());

    cout << "Input year: ";
    book.set_year(read_input_integer(-9999, 2023));

    cout << "Input number of available books: ";
    book.set_num_of_available_books(read_input_integer(0, INT_MAX));

    cout << "Input number of borrowed books: ";
    book.set_num_of_borrowed_books(read_input_integer(0, INT_MAX));

    return book;
}

string cut_string(string str, int max_length) {
    assert(max_length >= 3);
    if (str.size() <= max_length) {
        return str;
    }
    else {
        return str.substr(0, max_length - 3) + "...";
    }
}

void display_book(const Book& book) {
    cout << "Book information:\n";
    cout << "\tISBN                : " << book.get_isbn() << '\n';
    cout << "\tTitle               : " << book.get_title() << '\n';
    cout << "\tAuthor              : " << book.get_author() << '\n';
    cout << "\tPublisher           : " << book.get_publisher() << '\n';
    cout << "\tYear                : " << book.get_year() << '\n';
    cout << "\t# of available books: " << book.get_num_of_available_books() << '\n';
    cout << "\t# of borrowed books : " << book.get_num_of_borrowed_books() << '\n';
}

void display_multiple_books(const vector<Book>& books, int books_per_page = 10) {
    if (books.empty()) {
        cout << "No such book is found.\n";
    }
    else {
        int max_page = (books.size() + books_per_page - 1) / books_per_page;
        int page = 0;
        do {
            system("cls");
            cout << setw(12) << "ISBN"
                << setw(33) << "Title"
                << setw(23) << "Author"
                << setw(23) << "Publisher"
                << setw(8) << "Year"
                << setw(12) << "#available"
                << setw(12) << "#borrowed"
                << '\n';

            int num_of_displayed_books = 0;
            for (int i = page * books_per_page, j = 0; i+j < books.size() && j < books_per_page; j++) {
                string cut_title = cut_string(books[i+j].get_title(), 30);
                string cut_author = cut_string(books[i+j].get_author(), 20);
                string cut_publisher = cut_string(books[i+j].get_publisher(), 20);
                cout << setw(12) << books[i+j].get_isbn()
                     << setw(33) << cut_title
                     << setw(23) << cut_author
                     << setw(23) << cut_publisher
                     << setw(8) << books[i+j].get_year()
                     << setw(12) << books[i+j].get_num_of_available_books()
                     << setw(12) << books[i+j].get_num_of_borrowed_books()
                     << '\n';
                num_of_displayed_books++;
            }
            cout << "Showing " << num_of_displayed_books << " out of " << books.size() << " books. ";
            cout << "Page " << page+1 << " out of " << max_page << ".\n";
            
            cout << "Go to page (input 0 to stop moving between pages): ";
            page = read_input_integer(0, max_page);
            page--;
        } while (page != -1);
    }
}

void display_user(User user) {
    cout << "User information:\n";
    cout << "\tUsername         : " << user.get_name() << '\n';
    cout << "\tPassword         : " << user.get_password() << '\n';
    cout << "\tPhone number     : " << user.get_phone() << '\n';
    list<string> borrowed_books = user.get_borrowed_books();
    if (borrowed_books.empty()) {
        cout << "No books borrowed\n";
    }
    else {
        cout << "\tCurrently borrows: ";
        for (list<string>::iterator it = borrowed_books.begin(); it != borrowed_books.end(); it++) {
            if (it != borrowed_books.begin()) cout << ", ";
            cout << *it;
        }
        cout << '\n';
    }
}

void display_multiple_users(const vector<User>& users, int users_per_page = 10) {
    if (users.empty()) {
        cout << "No user.\n";
    }
    else {
        int max_page = (users.size() + users_per_page - 1) / users_per_page;
        int page = 0;
        do {
            system("cls");
            cout << setw(23) << "Name"
                << setw(15) << "Password"
                << setw(15) << "Phone"
                << setw(20) << "# of borrowed books"
                << '\n';

            int num_of_displayed_users = 0;
            for (int i = page * users_per_page, j = 0; i+j < users.size() && j < users_per_page; j++) {
                string cut_name = cut_string(users[i+j].get_name(), 20);
                string cut_password = cut_string(users[i+j].get_password(), 12);
                string cut_phone = cut_string(users[i+j].get_phone(), 12);
                cout << setw(23) << cut_name
                     << setw(15) << cut_password
                     << setw(15) << cut_phone
                     << setw(20) << users[i+j].get_borrowed_books().size()
                     << '\n';
                num_of_displayed_users++;
            }
            cout << "Showing " << num_of_displayed_users << " out of " << users.size() << " users. ";
            cout << "Page " << page+1 << " out of " << max_page << ".\n";
            
            cout << "Go to page (input 0 to stop moving between pages): ";
            page = read_input_integer(0, max_page);
            page--;
        } while (page != -1);
    }
}

void update_book() {
    cout << "Update book:\n";
    cout << "1. Add book stock\n";
    cout << "2. Modify book\n";
    cout << "3. Delete existing book\n";
    cout << "4. Remove book stock\n";
    cout << "5. Create new book\n";
    cout << "0. Back to main menu.\n";
    cout << "Choose operation to do: ";
    int option = read_input_integer(0, 5);

    if (option == 0) {
        return;
    }

    string isbn;
    while (option != 5) {
        const string cancel_operation = "(-1 to cancel operation)";
        if (option == 1) cout << "Input book ISBN to be added stock " + cancel_operation + ": ";
        else if (option == 2) cout << "Input ISBN to be modified " + cancel_operation + ": ";
        else if (option == 3) cout << "Input book ISBN to be deleted " + cancel_operation + ": ";
        else if (option == 4) cout << "Input book ISBN to be removed stock " + cancel_operation + ": ";

        isbn = read_input_line();
        if (isbn == "-1") {
            return;
        }
        else {
            Book book = book_manager.get_book_by_isbn(isbn);
            if (book.get_isbn() == "") {
                cout << "No such book is found.\n";
            }
            else {
                display_book(book);
                break;
            }
        }
    }

    if (option == 1) {
        cout << "Input the amount of book stocks to be added: ";
        int amount = read_input_integer(0, INT_MAX);
        if (book_manager.add_book_stock(isbn, amount)) {
            cout << "Successfully added book stocks.\n";
            display_book(book_manager.get_book_by_isbn(isbn));
            history.push_back("Added " + to_string(amount) + " book stocks to book with ISBN " + isbn + "\n");
        }
        else {
            cout << "Failed to add book stocks.\n";
        }
    }
    else if (option == 2) {
        cout << "Fill these values to modify the old book's data.\n";
        Book new_book = read_input_book();

        if (book_manager.update_book(isbn, new_book)) {
            cout << "Successfully modified book.\n";
            display_book(book_manager.get_book_by_isbn(new_book.get_isbn()));
            history.push_back("Updated book with old ISBN " + isbn + " to new ISBN " + new_book.get_isbn() + "\n");
        }
        else {
            cout << "Failed to modify book.\n";
        }
    }
    else if (option == 3) {
        cout << "Are you sure to delete book? (y/n) ";
        string response = read_input_line();
        if (response == "y") {
            if (book_manager.delete_book(isbn)) {
                cout << "Delete successful.\n";
                history.push_back("Deleted book with ISBN " + isbn + "\n");
            }
            else {
                cout << "Delete failed.\n";
            }
        }
    }
    else if (option == 4) {
        cout << "Input the amount of book stocks to be removed: ";
        int amount = read_input_integer(1, INT_MAX);
        if (book_manager.remove_book_stock(isbn, amount)) {
            cout << "Successfully removed book stocks.\n";
            display_book(book_manager.get_book_by_isbn(isbn));
            history.push_back("Removed " + to_string(amount) + " book stocks to book with ISBN " + isbn + "\n");
        }
        else {
            cout << "Failed to remove book stocks.\n";
        }
    }
    else if (option == 5) {
        cout << "Fill these values for the new book.\n";
        Book book = read_input_book();
        if (book_manager.create_book(book)) {
            cout << "Created a new book.\n";
            display_book(book_manager.get_book_by_isbn(book.get_isbn()));
            history.push_back("Created new book with ISBN " + book.get_isbn() + " - " + book.get_title() + "\n");
        }
        else {
            cout << "Failed to create a new book. Make sure that the ISBN must be unique.\n";
        }
    }
}

void search_book() {
    cout << "Search book\n";
    cout << "1. Show all books\n";
    cout << "2. Search book by ISBN\n";
    cout << "3. Search books by title\n";
    cout << "4. Search books by author\n";
    cout << "5. Search books by publisher\n";
    cout << "0. Go back\n";
    cout << "Choose operation to do: ";
    int option = read_input_integer(0, 5);

    if (option == 1) {
        display_multiple_books(book_manager.get_all_books());
    }
    else if (option == 2) {
        cout << "Input ISBN: ";
        string isbn = read_input_line();
        Book book = book_manager.get_book_by_isbn(isbn);
        if (!book.get_isbn().empty()) {
            display_book(book);
        }
        else {
            cout << "No such book is found.\n";
            return;
        }
    }
    else if (3 <= option && option <= 5) {
        vector<Book> books = book_manager.get_all_books();

        if (option == 3) {
            cout << "Input title: ";
            string title = read_input_line();
            const regex title_regex(".*" + title + ".*");

            vector<Book> result;
            for (int i = 0; i < books.size(); i++) {
                if (regex_match(books[i].get_title(), title_regex)) {
                    result.push_back(books[i]);
                }
            }
            display_multiple_books(result);
        }
        else if (option == 4) {
            cout << "Input author's name: ";
            string author = read_input_line();
            const regex author_regex(".*" + author + ".*");

            vector<Book> result;
            for (int i = 0; i < books.size(); i++) {
                if (regex_match(books[i].get_author(), author_regex)) {
                    result.push_back(books[i]);
                }
            }
            display_multiple_books(result);
        }
        else if (option == 5) {
            cout << "Input publisher: ";
            string publisher = read_input_line();
            const regex publisher_regex(".*" + publisher + ".*");

            vector<Book> result;
            for (int i = 0; i < books.size(); i++) {
                if (regex_match(books[i].get_publisher(), publisher_regex)) {
                    result.push_back(books[i]);
                }
            }
            display_multiple_books(result);
        }
    }
}

void search_user() {
    cout << "Search user\n";
    cout << "1. Show all users\n";
    cout << "2. Search by name\n";
    cout << "0. Go back\n";
    cout << "Choose operation to do: ";
    int option = read_input_integer(0, 2);
    if (option == 0) {
        return;
    }
    else if (option == 1) {
        display_multiple_users(user_manager.get_all_users());
    }
    else if (option == 2) {
        cout << "Input user name: (-1 to cancel) ";
        string name = read_input_line();
        if (name == "-1") {
            return;
        }
        else {
            display_user(user_manager.get_user_by_name(name));
        }
    }
}

void borrow_return_book(string name) {
    cout << "1. Borrow book\n";
    cout << "2. Return book\n";
    cout << "0. Cancel operation\n";
    cout << "Choose operation to do: ";
    int option = read_input_integer(0, 2);
    if (option == 0) {
        return;
    }
    else if (option == 1) {
        cout << "Input ISBN: ";
        string isbn = read_input_line();
        if (book_manager.borrow_book(isbn, 1)) {
            if (user_manager.borrow_book(name, isbn)) {
                cout << "Borrowed book with ISBN " << isbn << '\n';
                history.push_back(name + " borrowed a book with ISBN " + isbn + "\n");
            }
            else {
                assert(false);
            }
        }
        else {
            cout << "Failed to borrow book. Make sure that there are available books and you typed the correct ISBN.\n";
        }
    }
    else if (option == 2) {
        list<string> books = user_manager.get_user_by_name(name).get_borrowed_books();
        if (books.empty()) {
            cout << "No book borrowed\n";
        }
        else {
            int i = 0;
            for (string isbn : books) {
                cout << ++i << ". " << isbn << '\n';
            }
            cout << "Input which book to return (0 to cancel): ";
            int number = read_input_integer(0, books.size());
            if (number == 0) return;
            i = 0;
            for (list<string>::iterator it = books.begin(); it != books.end(); it++) {
                if (++i == number) {
                    assert(book_manager.return_book(*it, 1));
                    cout << "Returned book with ISBN " << *it << '\n';
                    history.push_back(name + " returned a book with ISBN " + *it + "\n");
                    assert(user_manager.return_book(name, *it));
                    break;
                }
            }
        }
    }
}

void display_history() {
    const int max_order_per_page = 10;
    int order = 0;
    auto it = history.end();
    while (true) {
        system("cls");
        cout << "History\n";
        cout << "Showing " << to_string(order + 1) << " to " << to_string(min(order + max_order_per_page, (int)history.size()))
             << " of the most recent operation, out of " << history.size() << " total.\n";

        int num_of_showed_entries = 0;
        for (int i = 0; i < max_order_per_page && it != history.begin(); i++) { // it != history.begin() to avoid out of bound
            cout << "- " << *(--it);
            num_of_showed_entries++; // keep track of how many history entry is being showed
        }
        for (int i = 0; i < num_of_showed_entries; i++) { // return iterator pointer back to order
            it++;
        }

        cout << "Page navigation\n";
        cout << "1. Go to next page\n";
        cout << "2. Go to previous page\n";
        cout << "0. Back to menu\n";
        int option = read_input_integer(0, 2);
        if (option == 1) {
            if (order + max_order_per_page < history.size()) { // check if still possible to go to next page
                order += max_order_per_page;
                for (int i = 0; i < max_order_per_page; i++) it--;
            }
        }
        else if (option == 2) { // check if still possible to go to previous page
            if (order >= max_order_per_page) {
                order -= max_order_per_page;
                for (int i = 0; i < max_order_per_page; i++) it++;
            }
        }
        else {
            break;
        }
    }
}

void admin_main_menu() {
    while (true) {
        system("cls");
        cout << "Library Management System\n";
        cout << "Main Menu\n";
        cout << "1. Search book\n";
        cout << "2. Update book database\n";
        cout << "3. Search user\n";
        cout << "4. Show history\n";
        cout << "0. Log out\n";
        cout << "Choose operation to do: ";
        int option = read_input_integer(0, 4);
        
        if (option == 0) {
            cout << "Do you want to log out? (y/n) ";
            string response = read_input_line();
            if (response == "y") {
                return;
            }
            else {
                continue;
            }
        }
        else if (option == 1) {
            system("cls");
            search_book();

            cout << "Do you want to update a book? (y/n) ";
            string response = read_input_line();
            if (response == "y") {
                update_book();
            }
        }
        else if (option == 2) {
            system("cls");
            update_book();
        }
        else if (option == 3) {
            system("cls");
            search_user();
        }
        else if (option == 4) {
            display_history();
        }

        cout << "Press any key to continue... ";
        getch();
    }
}

void user_main_menu(string name) {
    while (true) {
        system("cls");
        cout << "Welcome " << name << "!\n";
        cout << "Main menu\n";
        cout << "1. Search book\n";
        cout << "2. Borrow or return book\n";
        cout << "3. View profile and borrowed books\n";
        cout << "0. Log out\n";
        cout << "Choose operation to do: ";
        int option = read_input_integer(0, 3);

        if (option == 0) {
            cout << "Do you want to log out? (y/n) ";
            string response = read_input_line();
            if (response == "y") {
                return;
            }
        }
        else if (option == 1) {
            system("cls");
            search_book();

            cout << "Do you want to borrow or return book? (y/n) ";
            string response = read_input_line();
            if (response == "y") {
                borrow_return_book(name);
            }
        }
        else if (option == 2) {
            system("cls");
            borrow_return_book(name);
        }
        else if (option == 3) {
            system("cls");
            display_user(user_manager.get_user_by_name(name));
        }

        cout << "Press any key to continue... ";
        getch();
    }
}

void guest_main_menu() {
    while (true) {
        system("cls");
        search_book();

        cout << "Do you want to search again? (y/n) ";
        string response = read_input_line();
        if (response != "y") {
            break;
        }
    }
}

int main() {
    cout << "Loading data...\n";
    book_manager = BookManager(book_file_path);

    while (true) {
        system("cls");
        cout << "Library Login Page\n";
        cout << "1. Login as admin\n";
        cout << "2. Search and borrow book as user\n";
        cout << "3. Register as a new user\n";
        cout << "4. Search book as guest\n";
        cout << "0. Quit\n";
        cout << "Choose operation to do: ";
        int option = read_input_integer(0, 4);

        if (option == 0) {
            break;
        }
        else if (option == 1) {
            cout << "Input username: ";
            string username = read_input_line();
            cout << "Input password: ";
            string password = read_input_line();

            if (username == "admin" && password == "admin") {
                admin_main_menu();
            }
            else {
                cout << "Wrong username and password!\n";
            }
        }
        else if (option == 2) {
        	cout << "Input username: ";
        	string username = read_input_line();
        	cout << "Input password: ";
        	string password = read_input_line();
            
        	if (user_manager.login_user(username, password)) {
        		user_main_menu(username);
			}
			else {
				cout << "Wrong or unknown username and password, would you like to register? (y/n)\n";
				string response = read_input_line();
				if (response == "y") {
					goto regist;
				}
			}
		}
		else if (option == 3) {
            regist:
			string new_user, new_password, phone_num;
			cout << "Welcome to our Library\n";
			cout << "Enter username: ";
			new_user = read_input_line();
			cout << "Enter phone number: ";
			phone_num = read_input_line();
			cout << "Enter password: ";
			new_password = read_input_line();
			// name and password available
			if (user_manager.register_user(new_user, new_password, phone_num)) {
				cout << "Welcome, " << new_user << ". Enjoy your books.";
			}
			else {
				cout << "Failed to register user\n";
			}
		}
        else if (option == 4) {
            guest_main_menu();
        }

        cout << "Press any key to continue... \n";
        getch();
    }

    cout << "Saving data...";
    book_manager.save_data(book_file_path);
    user_manager.save_data(user_file_path);
}