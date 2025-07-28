#ifndef LIBRARIANCLASS_H
#define LIBRARIANCLASS_H

#include <vector>
#include <string>
#include "BookClass.h"

//libarian class
class Librarian{
private:
int ID;
vector<Book>& books;
public:
Librarian(int id,vector<Book>& bookList):ID(id),books(bookList)  {}

 // Method to add a book
    void addBook(int bookID, const string& title, const string& author) {
        Book newBook(bookID, title, author);  // assuming issued_status is false by default
        books.push_back(newBook);
    }

};


#endif