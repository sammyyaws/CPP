///make sure you read the README.md

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits> // for numeric_limits
#include "LibrarianClass.h"
#include "BookClass.h"
using namespace std;

extern vector<Librarian> Librarians;


bool LoginLibrarian() {
    int menuInput;
    int LoginLibrarianID;
    bool foundlib = false;

    while (!foundlib) {
        cout << "\033[1;33m";
        cout << "Welcome! Please enter your Work ID to login" << endl;
        cout << "\033[1;0m";

        // Validate numeric input for ID
        if (!(cin >> LoginLibrarianID)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // restart loop
        }

        // Check for matching librarian
        for (Librarian &l : Librarians) {
            if (l.getID() == LoginLibrarianID) {
                cout << "WELCOME" << setw(30) << l.getName() << endl;
                foundlib = true;

                // Librarian menu loop
                bool loggedIn = true;
                while (loggedIn) {
                    int width = 25;
                    cout << "\033[1;34m";
                    cout << setw(width) << "1. Add Book"
                         << setw(width) << "2. View all Books"
                         << setw(width) << "3. Search Book"
                         << setw(width) << "4. Display all Users" << endl;
                    cout << setw(30) << "5. View Borrowed Books"
                         << setw(30) << "6. Delete Book"
                         << setw(30) << "7. Logout" << endl;
                    cout << "\033[1;0m";

                    // Validate menu input
                    if (!(cin >> menuInput)) {
                        cout << "Invalid choice. Please enter a number.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove leftover newline

                    switch (menuInput) {
                        case 1: {
                            string title, author;
                            cout << "Enter Book Title: ";
                            getline(cin, title);
                            cout << "Enter Author Name: ";
                            getline(cin, author);
                            Book::addbook(db, title, author);
                            cout << "Book added successfully!\n";
                            break;
                        }
                        case 2: {
                            Book::displayAllBooks();
                            break;
                        }
                        case 3: {
                            string keyword;
                            do {
                                cout << "Enter Book Title or Author details: ";
                                getline(cin, keyword);
                            } while (keyword.empty());
                            Book::searchbook(keyword);
                            break;
                        }
                        case 4: {
                            Librarian::displayAllUsers();
                            break;
                        }
                        case 5: {
                            Librarian::displayBorrowedBooks();
                            break;
                        }
                        case 6: {
                            Librarian::deleteBookById();
                            break;
                        }
                        case 7: {
                            cout << "Logging out...\n";
                            loggedIn = false;
                            break;
                        }
                        default: {
                            cout << "Invalid choice. Please try again.\n";
                            break;
                        }
                    }
                }
                break; // exit for loop after successful login
            }
        }

        if (!foundlib) {
            cout << "Wrong Work ID. Please try again.\n";
        }
    }
    return foundlib;
}

/******************* All rights reserved: Group 12 Project Lead By Adade Samuel Yawson ********************/
