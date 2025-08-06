#ifndef LIBRARIANCLASS_H
#define LIBRARIANCLASS_H

#include <vector>
#include <string>
#include "BookClass.h"
#include "sql/sqlite3.h"
//libarian class
class Librarian{
private:
int ID;
string librarianName;
vector<Book>& books;
public:

Librarian(int id,string name,vector<Book>& bookList):ID(id),books(bookList),librarianName(name)  {}



    //getters
    int getID() const{
        return ID;
    }
 string getName()const{
    return librarianName;
 }

    // Function to display all the Users
static bool displayAllUsers() {
   string sql = "SELECT * FROM Users";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Database preparation Error: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_ROW) {
        cout << "\033[1;31m";
        cout << "No one has registered in your library!\n\n";
        cout << "\033[0m";
        sqlite3_finalize(stmt);
        return false;
    }

    const int colWidth = 25;

    // Headers
    cout << "\033[1;32m";
    cout << setw(colWidth) << "User ID"
         << setw(colWidth) << "Username"
         << setw(colWidth) << "Borrowed Status" << endl;
    cout << "\033[0m";

    // Rows
    do {
        int id = sqlite3_column_int(stmt, 0);
        string Username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int Borrowed = sqlite3_column_int(stmt, 3);

        cout << setw(colWidth) << id
             << setw(colWidth) << Username
             << setw(colWidth) << (Borrowed ? "Has borrowed" : "Has not borrowed") << endl;

    } while (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return true;


}

///display all borrowed books

static bool displayBorrowedBooks() {
    sqlite3_stmt* stmt;
    string sql = 
        "SELECT Borrow.BorrowId, Users.UserName, Book.Title, Borrow.BorrowedDate "
        "FROM Borrow "
        "JOIN Users ON Borrow.UserId = Users.UserId "
        "JOIN Book ON Borrow.BookId = Book.BookId "
        "WHERE Borrow.ReturnDate IS NULL;";

    // Prepare statement
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing borrowed books query: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    // Check if there are any results
    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_ROW) {
        cout << "\033[1;31mNo borrowed books found.\033[0m" << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    // Print table header
    cout << "\033[1;32m";
    cout << left << setw(10) << "BorrowID"
         << setw(20) << "Username"
         << setw(30) << "Book Title"
         << setw(15) << "Borrowed Date" << endl;
    cout << "\033[0m";

    // Loop through rows
    do {
        int borrowId = sqlite3_column_int(stmt, 0);
        string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string borrowedDate = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        cout << left << setw(10) << borrowId
             << setw(20) << username
             << setw(30) << title
             << setw(15) << borrowedDate << endl;

    } while (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);
    return true;
}



//delete a book by id 
static bool deleteBookById() {
    int bookId;
    cout << "Enter the Book ID you want to delete: ";
    cin >> bookId;

    sqlite3_stmt* stmt;

    // Step 1: Check if the book exists
    string sqlCheck = "SELECT 1 FROM Book WHERE BookId = ?;";
    if (sqlite3_prepare_v2(db, sqlCheck.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing check: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, bookId);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        cout << "\033[1;31mBook ID not found!\033[0m" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);

    // Step 2: Delete related borrow records
    string sqlDeleteBorrow = "DELETE FROM Borrow WHERE BookId = ?;";
    if (sqlite3_prepare_v2(db, sqlDeleteBorrow.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing delete from Borrow: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, bookId);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error deleting from Borrow: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);

    // Step 3: Delete the book itself
    string sqlDeleteBook = "DELETE FROM Book WHERE BookId = ?;";
    if (sqlite3_prepare_v2(db, sqlDeleteBook.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing delete: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, bookId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error deleting book: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << "\033[1;32mBook deleted successfully!\033[0m" << endl;
    return true;
}





}; 

#endif



/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
