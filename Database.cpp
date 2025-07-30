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
 

char *createBookTable="CREATE TABLE  IF NOT EXISTS Book("
"bookId INTEGER PRIMARY KEY AUTOINCREMENT,"
"Title TEXT NOT NULL,"
"Author TEXT NOT NULL,"
" Borrow BOOLEAN DEFAULT 0);";

 
char *createUserTable="CREATE TABLE IF NOT EXISTS User("
"UserId INTEGER PRIMARY KEY AUTOINCREMENT,"
"UserName TEXT NOT NULL,"
"Borrowed BOOLEAN DEFAULT 0);";

char *errMessage=nullptr;
 rc=sqlite3_exec(*db,createBookTable,nullptr,nullptr,&errMessage);

if (rc!=SQLITE_OK){
   cerr<<"Error creating table (Book)"<<errMessage;
   sqlite3_free(errMessage);
   return false;
}

//executing the sqlite3
rc=sqlite3_exec(*db,createUserTable,nullptr,nullptr,&errMessage);
if(rc!=SQLITE_OK){
 
   cerr<<"Error creating table (User)"<<errMessage;
   sqlite3_free(errMessage);
   return false;

}

return true;
}