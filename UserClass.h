#ifndef     USERCLASS_H
#define  USERCLASS_H
#include <string>
#include "BookClass.h"
using namespace std;
#include "sql/sqlite3.h"
extern sqlite3*db;

class User{
  private:
  int ID;
  int borrowed_books;
  int dues;
  string UserName;
 public:
 User(int id, string name):ID(id),borrowed_books(0),UserName(name){};
//getters for User
int getID() const{
  return ID;
}
string getName() const{
  return UserName;
}



//setters for User
void setID(int id){
this->ID=id;
}


/*******************************DataBase methods*********************/ 
//insert method
static bool insertName(sqlite3*db,string &name,string &Password){
 string sql="INSERT INTO Users(Username,Password) VALUES(?,?);";
 sqlite3_stmt *stmt;
 //Prepare the sql query for compilation and storing it into the compilation statement stmt
 if (sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)!=SQLITE_OK){
     cerr<<"Couldnt insert your name in(User)"<<sqlite3_errmsg(db)<<endl;
     return false;
 }
//Binding the first placeholders in the query to the corresponding input being pass;
 if (sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_TRANSIENT )!=SQLITE_OK){
  cerr<<"We couldn't bind the your input"<<sqlite3_errmsg(db)<<endl;
   sqlite3_finalize(stmt);
  return false; 

 };
 //Binding the second placeholders in the query to the corresponding input being pass;
 if (sqlite3_bind_text(stmt,2,Password.c_str(),-1,SQLITE_TRANSIENT )!=SQLITE_OK){
  cerr<<"We couldn't bind the your input"<<sqlite3_errmsg(db)<<endl;
   sqlite3_finalize(stmt);
  return false; 

 };
//executing the compiled code from stmt
if (sqlite3_step(stmt)!=SQLITE_DONE){
  cerr<<"Compilation Errors"<<sqlite3_errmsg(db)<<endl;
   sqlite3_finalize(stmt);
return false;

}
  sqlite3_finalize(stmt);
return true;
};//end of insert method


//Return book method
static bool returnBook() {
    int bookId;
    cout << "Enter the Book ID you want to return: ";
    cin >> bookId;

    sqlite3_stmt* stmt;

    // Step 1: Check if the book is currently borrowed
    string sqlCheckBorrowed = "SELECT BorrowId FROM Borrow WHERE BookId = ? AND ReturnDate IS NULL;";
    if (sqlite3_prepare_v2(db, sqlCheckBorrowed.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing check: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, bookId);

    int borrowId = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        borrowId = sqlite3_column_int(stmt, 0);
    } else {
        cout << "\033[1;31mThis book is not currently borrowed!\033[0m" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);


    string returnDate=Book::getTodayDate();
   

    // Step 3: Update the Borrow table to set the return date
    string sqlUpdate = "UPDATE Borrow SET ReturnDate = ? WHERE BorrowId = ?;";
    if (sqlite3_prepare_v2(db, sqlUpdate.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing update: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, returnDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, borrowId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error updating return date: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    cout << "\033[1;32mBook returned successfully on " << returnDate << "!\033[0m" << endl;
    return true;
}



};





#endif








/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
