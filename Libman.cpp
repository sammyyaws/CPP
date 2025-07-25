#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Logo.h"
 using namespace std;

 //variable declaration
 int login_as;
 int register_as;
 int LoginUserID;
 int NewUserID;
 string NewUserName;
 



//book class for all book objects
class Book{

 private:
  Book(int ID,string title,string author){

    };


};

 /******************* user class **********************************/
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


//libarian class
class Librian{

};

/*********************************Main Function ************************************************* */

int main (){
    //including the intro part
   showLogo();

   //start of excution


 cout <<"\033[3;35m";  
cout<<"Login as a :"<<endl;
cout <<setw(20)<<"1:USER"<<setw(20)<<"2:LIBRIAN \n"<<endl;
  cout <<"\033[0m"; 
cin>>login_as;

//getting access to the user Interface
vector<User>  users={User(1,"sammy")};
if (login_as==1){
cout<<"\033[1;33m";
cout<<"Welcome Please enter your user ID to login"<<endl;
cout<<"\033[1;0m";

/// Taking User Input
cin>>LoginUserID;

//LoginID validation
bool found=false;
 for (const User& u:users){
  if (u.getID()==LoginUserID){
    cout<<"Welcome, You have succesfully logged  in";
   found=true;
  }
  if (!found){
    cout<<"You are not a registered member of this library \n"<<endl;
   
    }
   break;
  }

// Getting  User registeration
cout <<"\033[3;35m";  
    cout<<"Register as a :"<<endl;
    cout <<setw(20)<<"1:USER"<<setw(20)<<"2:LIBARIAN \n"<<endl;
    cout <<"\033[0m"; 
    cin>>register_as;
    //check the type of account to create
    if (register_as==1){
    //get new user Id
    cout<<"Enter an ID number You want \n"<<endl;
cin>>NewUserID;
    //get new user name
    cout<<"Enter a user name You want \n"<<endl;
cin>>NewUserName;

User newUser(NewUserID,NewUserName);
users.push_back(newUser);
cout<<"My User Name is :"<<newUser.getName()<<endl;
cout<<"I cant give you this ID:"<<newUser.getID()<<endl;
}
else if(register_as==2){
  cout<<"Wait to register as a Libarian"<<endl;
}
}
///////end of user interface




//getting access to the Libarian Interface
else if (login_as==2){

}
else {
    cout<<"Check your input, choose 1 or 2"<<endl;
}





    return 0;
}