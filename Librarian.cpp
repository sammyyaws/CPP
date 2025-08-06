#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "LibrarianClass.h"
#include "BookClass.h"
using namespace std;
//array to store the libarian data

extern vector<Librarian> Librarians ;

bool LoginLibrarian(){
  //local variables
int menuInput;
    int LoginLibrarianID;
    bool foundlib=false;

 cout<<"\033[1;33m";
cout<<"Welcome Please enter your Work ID to login"<<endl;
cout<<"\033[1;0m";

/// Taking Librarian Input
cin>>LoginLibrarianID;

//LoginID validation
  
 for ( Librarian& l:Librarians){
     cout << "Checking librarian with ID: " << l.getID() << endl;
 if (l.getID()==LoginLibrarianID){
//librarian logged in interface
cout<<"WELCOME"<<setw(30)<<l.getName()<<endl;
cout <<left;
start:
int width=25;
cout<<"\033[1;34m";
 cout << setw(width) << "1.Add Book"
       << setw(width) << "2.View all Books"
         << setw(width) << "3.Search Book"
         << setw(width) << "4.Display all Users "<<endl;
       cout  <<setw(width)<<"5.view borrowed books"
          <<setw(width)<<"6.Delete Book"
         << setw(width) << "7. Logout" << endl;
         cout<<"\033[1;0m";
cin >>menuInput;
cin.ignore();
//working with the input with switch

switch (menuInput) {
    case 1: {
        string title, author;
        cout << "Enter Book Title: " << endl;
        getline(cin, title);
        cout << "Enter Author Name: " << endl;
        getline(cin, author);
        Book::addbook(db, title, author);
        cout << "Book added successfully!\n";
        goto start;
        
    }
    case 2: {
        bool display = Book::displayAllBooks();
        if (!display) goto start;
        break;
    }
    case 3: {
        string keyword;
        while (true) {
            cout << "Enter Book Title or Author details: ";
            getline(cin, keyword);
            if (!keyword.empty()) break;
        }
        bool searchresult = Book::searchbook(keyword);
        if (!searchresult) 
        goto start;
        break;
    }
    case 4: {
        Librarian::displayAllUsers();
        goto start; // return to menu after displaying
        break;
    }

    case 5: {
        bool getBorrowed=Librarian::displayBorrowedBooks();
        if(!getBorrowed) goto start;
        break;
    }
    case 6:{
        bool deletedBook=Librarian::deleteBookById();
        if (deletedBook) goto start;
    }
    case 7: {
        cout << "Logging out...\n";
        return true;
        break;
    }
    default: {
        cout << "Invalid choice. Please try again.\n";
        goto start;
    }
}
 
foundlib=true;
     break;
  }}
  return foundlib;
}









/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
