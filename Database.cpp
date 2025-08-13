///make sure you read the README.md

#include <iostream>
#include "sql/sqlite3.h"
#include "Logo.h"
using namespace std;


bool initDatabase(sqlite3 **db){
      //creating the database
    int rc=sqlite3_open("Library.db",db);
 if(rc){
    cerr<<"Could not create database:"<<sqlite3_errmsg(*db)<<endl;}

      //including the intro part
   showLogo();
 
//Querry to create the Book table
const char *createBookTable="CREATE TABLE  IF NOT EXISTS Book("
"BookId INTEGER PRIMARY KEY AUTOINCREMENT,"
"Title TEXT NOT NULL,"
"Author TEXT NOT NULL,"
" Issued BOOLEAN DEFAULT 0);";

//Querry to create the User table
 
const char *createUserTable="CREATE TABLE IF NOT EXISTS Users("
"UserId INTEGER PRIMARY KEY AUTOINCREMENT,"
"UserName TEXT NOT NULL,"
"Password TEXT NOT NULL,"
"Borrowed BOOLEAN DEFAULT 0);";
//Querry to create the Borrowed table

const char *createBorrowTable="CREATE TABLE IF NOT EXISTS Borrow("
"BorrowId INTEGER PRIMARY KEY AUTOINCREMENT,"
"UserId INTEGER NOT NULL,"
"BookId INTEGER NOT NULL,"
"BorrowedDate TEXT NOT NULL,"
"ReturnDate TEXT,"
"FOREIGN KEY(UserId) REFERENCES User(UserId),"
"FOREIGN KEY(BookId) REFERENCES Book(BookId));";

char *errMessage=nullptr;
 rc=sqlite3_exec(*db,createBookTable,nullptr,nullptr,&errMessage);

 //executing the sqlite3 for BookTable

if (rc!=SQLITE_OK){
   cerr<<"Error creating table (Book)"<<errMessage;
   sqlite3_free(errMessage);
   return false;
}

//executing the sqlite3 for userTable
rc=sqlite3_exec(*db,createUserTable,nullptr,nullptr,&errMessage);
if(rc!=SQLITE_OK){
 
   cerr<<"Error creating table (Users)"<<errMessage;
   sqlite3_free(errMessage);
   return false;

}

//executing the sqlite3 for BorrowTable
rc=sqlite3_exec(*db,createBorrowTable,nullptr,nullptr,&errMessage);
if(rc!=  SQLITE_OK){
      cerr<<"Error creating table (Borrow)"<<errMessage;
   sqlite3_free(errMessage);
   return false;
}

return true;
}

























/******************* All right reserved:Project Lead By Adade Samuel Yawson ********************/