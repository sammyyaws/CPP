#ifndef     USERCLASS_H
#define  USERCLASS_H
#include <string>
using namespace std;



class User{
  private:
  int ID;
  int issued_books;
  int dues;
  string UserName;
 public:
 User(int id, string name):ID(id),issued_books(),dues(),UserName(name){};
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

};





#endif