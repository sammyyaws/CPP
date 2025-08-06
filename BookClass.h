/**this file contains the class for the book */
#ifndef BOOKCLASS_H
#define BOOKCLASS_H
#include <iostream>
#include <iomanip>

#include <string>
#include "sql/sqlite3.h"


using namespace std;
extern sqlite3 *db;

//contains the book class
class Book{
private:
int ID;
string title;
string author;
bool issued_status;

public:
Book(int id,string title,string author,bool status=false):ID(id),title(title),author(author),issued_status(status){};

  // Getters
    int getID() const {
         return ID; }

    string getTitle() const { 
        return title; }

    string getAuthor() const { 
        return author; }
    bool isIssued() const {
         return issued_status; }
         
   // Setters
    void setTitle(const string newTitle) { 
        title = newTitle; }
    void setAuthor(const string newAuthor) {
         author = newAuthor; }
         //function to set the issued status of the book
    void setIssuedStatus(bool status) { 
        issued_status = status; }

/*  *********************   sql Database methods ********************* */
    
    // Function to display all the books
static bool displayAllBooks() {
    string sql = "SELECT * FROM Book";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Database preparation Error: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    //  trying to get the first row and checking if there are any roles
    int stepResult = sqlite3_step(stmt);
    if (stepResult != SQLITE_ROW) {
      cout<<"\033[1;31m";
        cout << "Librarian has not added any book!\n" << endl; cout<<"\033[1;0m";
        sqlite3_finalize(stmt);
        return false;
    }

    // Print table headers
    int width=30;
    cout << "\033[1;32m";
    cout << left;
    cout << setw(width) << "|| Book ID ||"
         << setw(width) << "||  Title ||"
         << setw(width) << "||  Author ||"
         << setw(width) << "|| Issued status ||" << endl;
    cout << "\033[0m";

    // Display the first row
    do {
        int id = sqlite3_column_int(stmt, 0);
        int issued = sqlite3_column_int(stmt, 3);

        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // fix here: should be column 2

        cout << setw(width) << id
             << setw(width) << title
             << setw(width) << author
             << setw(width) << (!issued ? "Available" : "Not available") << endl;

    } while (sqlite3_step(stmt) == SQLITE_ROW);  

    sqlite3_finalize(stmt);
    return true;
}

   
    


/************************ *searching for a the books******************/
 static bool searchbook(const string &keyword){

 bool found=false;
 string sql="SELECT *FROM Book where Title LIKE ? OR Author LIKE ? OR BookId LIKE ? ";
sqlite3_stmt*stmt;

if (sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)==SQLITE_OK){
    string searchPattern="%"+keyword+"%";

sqlite3_bind_text(stmt,1,searchPattern.c_str(),-1,SQLITE_TRANSIENT);
sqlite3_bind_text(stmt,2,searchPattern.c_str(),-1,SQLITE_TRANSIENT);
sqlite3_bind_text(stmt,3,searchPattern.c_str(),-1,SQLITE_TRANSIENT);

///////////////SHOW ALL THE SEARCH RESULT
        cout << "\033[1;36m";
    cout << setw(30) << "SEARCH RESULT:>>"<< endl;
    cout << "\033[0m";
    //DISPALY TABLE HEADS
cout << "\033[1;32m";
    cout << setw(30) << "|| Book ID ||"
         << setw(30) << "||  Title ||"
          << setw(30) << "||  Author ||"
         << setw(30) << "|| Issued Status ||" << endl;
    cout << "\033[0m";

while(sqlite3_step(stmt)==SQLITE_ROW){
    found=true;
     int id=sqlite3_column_int(stmt,0);
        string title=reinterpret_cast<const char*>(sqlite3_column_text(stmt,1));
      
         string author=reinterpret_cast<const char*>(sqlite3_column_text(stmt,2));
        int issued=sqlite3_column_int(stmt,3);
        

    
        cout << setw(30) << id
         << setw(30) << title
         << setw(30) << author
         << setw(30) << (!issued? "Available":"Not available" )<< endl;

}
sqlite3_finalize(stmt);

}else {cerr<<"Preparatiion Error"<<sqlite3_errmsg(db);
  return false;
}
 
if (!found) {
    cout<<"\003[1;31m";
        cout << "No books found matching: "<<"\003[1;31m" << keyword << endl;
        return false;
    }

    return true;
 }

 /************************ *add book method******************/

 static bool addbook(sqlite3*db,const string &title,const string &author,int Issued=0){
   string sql="INSERT INTO Book(Title,Author) VALUES(?,?)";
   sqlite3_stmt*stmt;

   if(sqlite3_prepare(db,sql.c_str(),-1,&stmt,nullptr)!=SQLITE_OK){
    cerr<<"Database preparation Error:"<<sqlite3_errmsg(db)<<endl;
    sqlite3_finalize(stmt);
    return false;
    
 }     

 ////the part which binds the data
  if (sqlite3_bind_text(stmt,1,title.c_str(),-1,SQLITE_TRANSIENT)!=SQLITE_OK){
    cerr<<"Data binding Error:"<<sqlite3_errmsg(db)<<endl;
    sqlite3_finalize(stmt);
    return false;
}

if (sqlite3_bind_text(stmt,2,author.c_str(),-1,SQLITE_TRANSIENT)!=SQLITE_OK){
    cerr<<"Data binding Error:"<<sqlite3_errmsg(db)<<endl;
    sqlite3_finalize(stmt);
    return false;
}


if (sqlite3_step(stmt)!=SQLITE_OK){
 cerr<<"Query Execution error"<<sqlite3_errmsg(db)<<endl; 
}


sqlite3_finalize(stmt);
return true;

}//end of addbook method





///borrow book method 


 
//function to get the date
static string getTodayDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    char dateStr[11];
    sprintf(dateStr, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);

    return string(dateStr);
}

static bool borrowBook() {
    string password;
    int bookId;

    cout << "Enter your password: ";
    cin >> password;

    // Step 1: Get UserId from password
    int userId = -1;
    sqlite3_stmt* stmt;
    string sqlGetUserId = "SELECT UserId FROM Users WHERE Password = ?;";
    if (sqlite3_prepare_v2(db, sqlGetUserId.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing user lookup: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, password.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (userId == -1) {
        cout << "\033[1;31mInvalid password. Cannot borrow book.\033[0m" << endl;
        return false;
    }

    // Step 2: Ask for Book ID
    cout << "Enter the Book ID you want to borrow: ";
    cin >> bookId;

    // Step 3: Check if book exists
    string sqlCheckBook = "SELECT 1 FROM Book WHERE BookId = ?;";
    if (sqlite3_prepare_v2(db, sqlCheckBook.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, bookId);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        cout << "\033[1;31mBook ID not found!\033[0m" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);

    // Step 4: Check if book is already borrowed
    string sqlCheckBorrowed = "SELECT 1 FROM Borrow WHERE BookId = ? AND ReturnDate IS NULL;";
    if (sqlite3_prepare_v2(db, sqlCheckBorrowed.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, bookId);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "\033[1;31mThis book is already borrowed!\033[0m" << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);

    // Step 5: Insert borrow record
    string borrowDate = getTodayDate();
    string sqlInsert = "INSERT INTO Borrow(UserId, BookId, BorrowedDate) VALUES(?, ?, ?);";
    if (sqlite3_prepare_v2(db, sqlInsert.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Error preparing insert: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, userId);
    sqlite3_bind_int(stmt, 2, bookId);
    sqlite3_bind_text(stmt, 3, borrowDate.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error inserting borrow record: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);

    cout << "\033[1;32mBook borrowed successfully on " << borrowDate << "!\033[0m" << endl;
    return true;
}



};

#endif




/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
