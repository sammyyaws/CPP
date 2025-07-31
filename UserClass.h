#ifndef     USERCLASS_H
#define  USERCLASS_H
#include <string>
using namespace std;
#include "sql/sqlite3.h"


class User{
  private:
  int ID;
  int borrowed_books;
  int dues;
  string UserName;
 public:
 User(int id, string name):ID(id),borrowed_books(0),dues(0),UserName(name){};
//getters for User
int getID() const{
  return ID;
}
string getName() const{
  return UserName;
}
int  getDues(){
  return dues;
}



//setters for User
void setID(int id){
this->ID=id;
}

void setUserDues(int due){
dues=due;
}
// DataBase methods
//insert method
static bool insertName(sqlite3*db,string name){
 string sql="INSERT INTO User(Username) VALUES(?);";
 sqlite3_stmt *stmt;
 //Prepare the sql query for compilation and storing it into the compilation statement stmt
 if (sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)!=SQLITE_OK){
     cerr<<"Couldnt insert your name in(User)"<<sqlite3_errmsg(db)<<endl;
     return false;
 }
//Binding the placeholders in the query to the corresponding input being pass;
 if (sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_TRANSIENT )!=SQLITE_OK){
  cerr<<"We couldn't bind the your input"<<sqlite3_errmsg(db)<<endl;
  return false; 

 };
//executing the compiled code from stmt
if (sqlite3_step(stmt)!=SQLITE_DONE){
  cerr<<"Compilation Errors"<<sqlite3_errmsg(db)<<endl;
return false;

}
  sqlite3_finalize(stmt);
return true;
};//end of insert method





};





#endif