#ifndef     USERCLASS_H
#define  USERCLASS_H
#include <string>
using namespace std;



class User{
  private:
  int ID;
  int borrowed_books;
  int dues;
  string UserName;
 public:
 User(int id, string name):ID(id),borrowed_books(),dues(),UserName(name){};
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

//Borrowed books method


};





#endif