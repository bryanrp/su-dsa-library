#include <conio.h>
#include <iomanip>
#include <iostream>
#include <list>
#include <regex>
#include <vector>
#include "include/book.h"
#include "include/book_manager.h"
#include "include/user_manager.h"
#include "src/book.cpp"
#include "src/book_manager.cpp"
#include "src/user_manager.cpp"
using namespace std;

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
    cout << "\tISBN:                 " << book.get_isbn() << '\n';
    cout << "\tTitle:                " << book.get_title() << '\n';
    cout << "\tAuthor:               " << book.get_author() << '\n';
    cout << "\tPublisher:            " << book.get_publisher() << '\n';
    cout << "\tYear:                 " << book.get_year() << '\n';
    cout << "\t# of available books: " << book.get_num_of_available_books() << '\n';
    cout << "\t# of borrowed books:  " << book.get_num_of_borrowed_books() << '\n';
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

// option_start is the user choice option starting number. this parameter is used to reduce code duplicate. (option_start-1) for back to menu
// set option = -1 if you want to output the user option navigation and ask user to input option
void update_book(BookManager& book_manager, int option_start, int option = -1) {
    if (option < 0) {
        cout << "Update book:\n";
        cout << option_start+0 << ". Add book stock\n";
        cout << option_start+1 << ". Modify book\n";
        cout << option_start+2 << ". Delete existing book\n";
        cout << option_start+3 << ". Remove book stock\n";
        cout << option_start+4 << ". Borrow book\n";
        cout << option_start+5 << ". Return book\n";
        cout << option_start-1 << ". Back to main menu.\n";
        cout << "Choose operation to do: ";
        option = read_input_integer(option_start-1, option_start+5);
    }
    if (option == 0) {
        return;
    }

    string isbn;
    while (true) {
        const string cancel_operation = "(-1 to cancel operation)";
        if (option == option_start) cout << "Input book ISBN to be added stock " + cancel_operation + ": ";
        else if (option == option_start+1) cout << "Input ISBN to be modified " + cancel_operation + ": ";
        else if (option == option_start+2) cout << "Input book ISBN to be deleted " + cancel_operation + ": ";
        else if (option == option_start+3) cout << "Input book ISBN to be removed stock " + cancel_operation + ": ";
        else if (option == option_start+4) cout << "Input book ISBN to be borrowed " + cancel_operation + ": ";
        else if (option == option_start+5) cout << "Input book ISBN to be returned " + cancel_operation + ": ";

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

    if (option == option_start) {
        cout << "Input the amount of book stocks to be added: ";
        int amount = read_input_integer(1, INT_MAX);
        if (book_manager.add_book_stock(isbn, amount)) {
            cout << "Successfully added book stocks.\n";
            display_book(book_manager.get_book_by_isbn(isbn));
            history.push_back("Added " + to_string(amount) + " book stocks to book with ISBN " + isbn + "\n");
        }
        else {
            cout << "Failed to add book stocks.\n";
        }
    }
    else if (option == option_start+1) {
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
    else if (option == option_start+2) {
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
    else if (option == option_start+3) {
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
    else if (option == option_start+4) {
        cout << "Input the amount of books to be borrowed: ";
        int amount = read_input_integer(1, INT_MAX);
        if (book_manager.borrow_book(isbn, amount)) {
            cout << "Borrow successful.\n";
            display_book(book_manager.get_book_by_isbn(isbn));
            history.push_back("Borrowed " + to_string(amount) + " books with ISBN " + isbn + "\n");
        }
        else {
            cout << "Borrow failed.\n";
        }
    }
    else if (option == option_start+5) {
        cout << "Input the amount of books to be returned: ";
        int amount = read_input_integer(1, INT_MAX);
        if (book_manager.return_book(isbn, amount)) {
            cout << "Return successful.\n";
            display_book(book_manager.get_book_by_isbn(isbn));
            history.push_back("Returned " + to_string(amount) + " books with ISBN " + isbn + "\n");
        }
        else {
            cout << "Return failed.\n";
        }
    }
}

void search_book(BookManager& book_manager, bool can_update = false) {
    system("cls");
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

    if (can_update) {
        cout << "Do you want to update a book? (y/n) ";
        string response = read_input_line();
        if (response == "y") {
            update_book(book_manager, 1);
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

void admin_main_menu(string file_location) {
    cout << "Loading data...\n";
    BookManager book_manager(file_location);

    while (true) {
        system("cls");
        cout << "Library Management System\n";
        cout << "Main Menu\n";
        cout << "1. Search book\n";
        cout << "2. Create new book\n";
        cout << "3. Add book stock\n";
        cout << "4. Modify book\n";
        cout << "5. Delete existing book\n";
        cout << "6. Remove book stock\n";
        cout << "7. Borrow book\n";
        cout << "8. Return book\n";
        cout << "9. Show history\n";
        cout << "0. Save and log out\n";

        cout << "Choose operation to do: ";
        int option = read_input_integer(0, 9);
        if (option == 0) {
            cout << "Do you want to save? (y/n) ";
            string response = read_input_line();
            if (response == "y") {
                cout << "Saving data...\n";
                book_manager.save_data(file_location);
            }
            return;
        }
        else if (option == 1) {
            search_book(book_manager, true);
        }
        else if (option == 2) {
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
        else if (3 <= option && option <= 8) {
            update_book(book_manager, 3, option);
        }
        else if (option == 9) {
            display_history();
        }

        cout << "Press any key to continue... ";
        getch();
    }
}

void guest_main_menu(string file_location) {
    cout << "Loading data...\n";
    BookManager book_manager(file_location);

    while (true) {
        search_book(book_manager, false);

        cout << "Do you want to search again? (y/n) ";
        string response = read_input_line();
        if (response != "y") {
            break;
        }
    }
}

int main() {
    const string file_location = "books.json";
    while (true) {
    	landingmenu:
        system("cls");
        cout << "Library Login Page\n";
        cout << "1. Login as admin\n";
        cout << "2. Search and borrow book as user\n";
        cout << "3. Register as a new user\n";
        cout << "4. Search book as guest\n";
        cout << "0. Quit\n";
        cout << "Choose operation to do: ";
        int option = read_input_integer(0, 2);

        if (option == 1) {
            cout << "Input username: ";
            string username = read_input_line();
            cout << "Input password: ";
            string password = read_input_line();

            if (username == "admin" && password == "admin") {
                admin_main_menu(file_location);
            }
            else {
                cout << "Wrong username and password!\n";
            }
        }
        else if (option == 2) {
        	cout << "Input username: ";
        	//func
        	cout << "Input password: ";
        	//func
        	if (user valid) {
        		//funct search borrow return
			}
			else {
				string response;
				cout << "Wrong or unknown username and password, would you like to register? y/n\n";
				cin  >> response;
				if (response=="y") {
					goto regist;
				}
				else if (response=="n") {
					goto landingmenu;
				}
			}
		}
		else if (option == 3) {
			string new_user, new_password, phone_num;
			cout << "Welcome to our Library\n";
			cout << "Enter username";
			cin >> new_user;
			if (username not taken) {
				//continue
			}
			else (username taken) {
				//go back to menu aja lah
			}
			cout << "Enter phone number:";
			cin >> phone_num;
			cout << "Enter password";
			cin >> new_password;
			//function for password requirement, lenght, character required
			if (password accepted) {
				cout << "Welcome, " << new_user << ". Enjoy your books.";
				cout << "Press any key to continue...";
				getch();
			}
			else (password not accepted) {
				cout << "Must be bla bla bla";
				//back to menu la
			}
		}
        else if (option == 4) {
            guest_main_menu(file_location);
        }

        cout << "Press any key to continue... \n";
        getch();
    }
}
