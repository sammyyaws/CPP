#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "UserClass.h"
#include "sql/sqlite3.h"
#include "User.h"
#include "BookClass.h"
using namespace std;


extern sqlite3 *db;
/********** Function for checking if the Username and password exists in the database******/
bool UserExists(const string &NewUserName,const string *Password=nullptr) {

string sql="SELECT 1 FROM Users WHERE UserName=? ";
if(Password!=nullptr){
    sql+="AND Password=?";
}



sqlite3_stmt *stmt;
//preparing the compiled statement for the username
if (sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr)!=SQLITE_OK){
 cerr<<"Query preparation Error:"<<sqlite3_errmsg(db)<<endl;
 return false;
}
//bindng the the name to the placeholder
if (sqlite3_bind_text(stmt,1,NewUserName.c_str(),-1,SQLITE_TRANSIENT)!=SQLITE_OK){
    cerr<<"Binding Error:"<<sqlite3_errmsg(db)<<endl;
    sqlite3_finalize(stmt);
 return false;
}

//bindng the the password to the placeholder
if(Password!=nullptr)
{ if (sqlite3_bind_text(stmt,2,(*Password).c_str(),-1,SQLITE_TRANSIENT)!=SQLITE_OK){
    cerr<<"Binding Error:"<<sqlite3_errmsg(db)<<endl;
    sqlite3_finalize(stmt);
 return false;
}}
// checcking if  the name exist on any database row
bool nameExists=(sqlite3_step(stmt)==SQLITE_ROW);
sqlite3_finalize(stmt);
return nameExists;

}




/********** * Funtion for the  User interface login feature***********/
bool LoginUser(){
    string LoginUserName;
    string Password;
    bool found=false;
    int attempts=0;
    int max=2;

    while(attempts<max){
    cout<<"\033[1;33m";
cout<<"Welcome Please enter your username to login"<<endl;
cout<<"\033[1;0m";

/// Taking User name
cin>>LoginUserName;

//taking user password

  cout<<"\033[1;33m";
cout<<" Please enter your Password to login"<<endl;
cout<<"\033[1;0m";

/// Taking User Password
cin>>Password;


//Login in validating from the sql part
 if (UserExists(LoginUserName, &Password)) {
    int menuInput;
        cout << "\033[1;32m";
        cout << " Welcome "<<setw(20) << LoginUserName << "!\n"<<endl;
        cout << "\033[0m";
        start:
/// display the menu for the user
cout<<"\033[1:35m";
        cout << setw(20) << "1. View all Books"
         << setw(20) << "2. Search Book"
         << setw(30) << "3.  Borrow Book"
           << setw(30) << "4.  Return Book"
         << setw(20) << "5. Logout" << endl;
         cout<<"\033[1:0m";
    while(true){
             cin >>menuInput;
   
    cin.ignore();


       
 //consditional switch checks

    switch (menuInput){
//when user chooses to view all the books
  case 1: {
  bool display=Book::displayAllBooks();
  if (!display || display)goto start;

  
  }
    //when users chooses to search book
    case 2:{
  string keyword;
  while(true){
  cout << "Enter Book Title or Author details" << endl;
getline(cin, keyword); // getline is used to read the entire line
if (!keyword.empty())
break;
  }
bool searchresult=Book::searchbook(keyword);
 if (!searchresult){
    goto start;
  }
break;
  }
    case 3:{
bool getBook=Book::borrowBook();
  if (!getBook){
    goto start;
   break;
    }}
    case 4:{
      bool returnBook =User::returnBook();
      if (returnBook || !returnBook) goto start;
    }
    case 5:{
        cout<<"You have successfully logged out";
        return true;
    }
  default:{
    cout<<"You enter incorrect input"<<endl;
    break;
  }
}

    }//end of switch
   return true;
}
     else { attempts++;
        cout << "\033[1;31m";
        cerr << "Username or password is incorrect.\n";
        cout << "\033[0m";
        
        if(attempts<=max){
          cout<<"Please try again "<<setw(3)<<max-attempts<<setw(3)<<"  attempts left"<<endl;
        }
        else{
           cout << "\033[1;31m";
           cout<<"Maximum trials exceeded::EXITING!!!!"<<endl;
            cout << "\033[1;0m";
          return false;
        }
    }
  }
return false;
}







////****************************Register part*********************************////



//main registration function
void RegisterUser(){
   
 int register_as;
 //variables for registration data
string NewUserName;
string Password;
     cout<<"You are not a registered  as  a member of this library \n"<<endl;
   // Getting  User registeration
cout <<"\033[3;35m";  
    cout<<"Register as a :"<<endl;
    cout <<setw(20)<<"1:USER"<<setw(20)<<endl;
    cout <<"\033[0m"; 
    
    cin>>register_as;
   
    //Account to create
    if (register_as==1){
     //get new user name and password with while loop, only exists
     while (true){
cout<<"\033[1;35m";
    cout<<"Enter a username you want \n"<<endl;
cout<<"\033[1;0m";
cin>>NewUserName;
   cout<<"\033[1;35m";
  cout<<"Enter a Password You want \n"<<endl;
  cout<<"\033[1;0m";
cin>>Password;

//checking if there is existing Username or Password
 if (UserExists(NewUserName, &Password)) {
        cout << "\033[1;32m";
        cout << "Username already exists!! Please trying a different one " << NewUserName << "!\n";
        cout << "\033[0m";
        
    } 
else{
    if (User::insertName(db,NewUserName,Password)){
   cout<<"You have successfully created your account"<<endl;
   break;
      }
    else{
    cerr<<"Sorry You have to try differentusername and password";
        }
    }
    }
}
}




/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
