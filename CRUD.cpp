#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    int year;
};

vector<Book> library;

void createBook(string title, string author, string genre, int year) {
    Book newBook = {title, author, genre, year};
    library.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

void readBooks() {
    if (library.empty()) {
        cout << "No books available in the library." << endl;
        return;
    }
    for (size_t i = 0; i < library.size(); ++i) {
        cout << i + 1 << ". '" << library[i].title << "' by " << library[i].author 
             << " (" << library[i].genre << ", " << library[i].year << ")" << endl;
    }
}

void updateBook(int index, string title = "", string author = "", string genre = "", int year = 0) {
    if (index >= 0 && index < library.size()) {
        if (!title.empty()) library[index].title = title;
        if (!author.empty()) library[index].author = author;
        if (!genre.empty()) library[index].genre = genre;
        if (year != 0) library[index].year = year;
        cout << "Book updated successfully!" << endl;
    } else {
        cout << "Invalid book index!" << endl;
    }
}

void deleteBook(int index) {
    if (index >= 0 && index < library.size()) {
        library.erase(library.begin() + index);
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "Invalid book index!" << endl;
    }
}

int main() {
    int choice, index, year;
    string title, author, genre;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a new book\n";
        cout << "2. View all books\n";
        cout << "3. Update a book\n";
        cout << "4. Delete a book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                cout << "Enter title: ";
                cin.ignore(); 
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter genre: ";
                getline(cin, genre);
                cout << "Enter year of publication: ";
                cin >> year;
                createBook(title, author, genre, year);
                break;

            case 2: 
                readBooks();
                break;

            case 3: 
                cout << "Enter the index of the book to update: ";
                cin >> index;
                cout << "Enter new title (leave blank to keep unchanged): ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter new author (leave blank to keep unchanged): ";
                getline(cin, author);
                cout << "Enter new genre (leave blank to keep unchanged): ";
                getline(cin, genre);
                cout << "Enter new year (enter 0 to keep unchanged): ";
                cin >> year;
                updateBook(index - 1, title, author, genre, year);
                break;

            case 4: 
                cout << "Enter the index of the book to delete: ";
                cin >> index;
                deleteBook(index - 1);
                break;

            case 5:
                cout << "Exiting Your Library." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
