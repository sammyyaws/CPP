#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "UserClass.h"
using namespace std;


extern vector<User> users;

//Login Part
bool LoginUser(){
    int LoginUserID;
    bool found=false;
    cout<<"\033[1;33m";
cout<<"Welcome Please enter your user ID to login"<<endl;
cout<<"\033[1;0m";

/// Taking User Input
cin>>LoginUserID;

//LoginID validation

 for (const User& u:users){
  if (u.getID()==LoginUserID){
//user logged in interface

    cout<<"Welcome"<<setw(20)<<u.getName();
   found=true;
     break;
  }}
  return found;
}



//Register part

void RegisterUser(){
    int register_as;
int NewUserID;
string NewUserName;
     cout<<"You are not a registered member of this library \n"<<endl;
   // Getting  User registeration
cout <<"\033[3;35m";  
    cout<<"Register as a :"<<endl;
    cout <<setw(20)<<"1:USER"<<setw(20)<<endl;
    cout <<"\033[0m"; 
    cin>>register_as;
    //Account to create
    if (register_as==1){
    //get new user Id
    cout<<"Enter an ID number You want \n"<<endl;
cin>>NewUserID;
    //get new user name
    cout<<"Enter a user name You want \n"<<endl;
cin>>NewUserName;
//creating a new instance of user
User newUser(NewUserID,NewUserName);
users.push_back(newUser);
cout<<"You have successfully created your account"<<endl;

}
}

