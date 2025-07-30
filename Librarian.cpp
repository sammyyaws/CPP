#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "LibrarianClass.h"
#include "BookClass.h"
using namespace std;
//array to store the libarian data
extern vector<Book> books; //declaration to use the global vector from the main
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
 cout << setw(20) << "1. Add Book"
       << setw(20) << "2. View Book"
         << setw(20) << "3. Search Book"
         << setw(30) << "4. View Issued Books"
         << setw(20) << "5. Logout" << endl;
cin >>menuInput;
cin.ignore();
//working with the input with switch

switch (menuInput){
//instance of book addition
  case 1: {
   int bookID;
   string title, author;
  cout << "Enter Book ID: " << endl;
cin >> bookID;
cin.ignore();  // removes any newline created
cout << "Enter Book Title: " << endl;
getline(cin, title);  // getline is used to read the entire line
cout << "Enter Author Name: " << endl;
getline(cin, author); 

   l.addBook(bookID, title, author);
   cout << " Book added successfully!\n";
   
   goto start;
   
   }
    //option 2
    case 2:{
   Book::displayAllBooks(books);
   goto start;
    }
    case 3:{
      string  keyword;
  cout<<"Please Enter the title or author to find the  ";
 getline(cin,keyword);

 Book::searchbook(books,keyword);
    }

}
   foundlib=true;
     break;
  }}
  return foundlib;
}
