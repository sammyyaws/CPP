#ifndef LIBRARIANCLASS_H
#define LIBRARIANCLASS_H

#include <vector>
#include <string>
#include "BookClass.h"

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

  // Method to add a book
    void addBook(int bookID, const string& title, const string& author) {
        Book newBook(bookID, title, author,false);  
        books.push_back(newBook);
    }

}; 
#endif