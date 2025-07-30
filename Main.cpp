#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Logo.h"
#include "User.h"
#include "UserClass.h"
#include "BookClass.h"
#include "LibrarianClass.h"
#include "Librarian.h"
#include "sql/sqlite3.h"
#include "Database.h"
 using namespace std;


 //setting up the sqlite database
sqlite3*db;



 //variable declaration
 int login_as;
int LoginUserID;
 

//array to store teh BOOKS
vector<Book> books;

//array to store the user data
 vector<User>  users;
//array to  store librarian data
 vector<Librarian> Librarians ;


/*********************************Main Function ************************************************* */

int main (){
  

   


   //start of excution
start:

 cout <<"\033[3;35m";  
cout<<"Login as a :"<<endl;
cout <<setw(20)<<"1:USER"<<setw(20)<<"2:LIBRIAN \n"<<endl;
  cout <<"\033[0m"; 
cin>>login_as;

//getting access to the user Interface

if (login_as==1){
bool found=LoginUser();
  
 if(!found){
   RegisterUser();
   goto start;
    }
 
}
///////end of user interface


//getting access to the Libarian Interface
else if (login_as==2){

    // Add some librarian details manually before login
    Librarians.push_back(Librarian(101, "Mr. Mensah", books));
    Librarians.push_back(Librarian(102, "Ms. Afua", books));
    Librarians.push_back(Librarian(103, "Dr. Kofi", books));
    
bool foundlib =LoginLibrarian();
 if(!foundlib){
  cout<<"You are not allowed to work as a librarian"<<endl;
   goto start;
    }
}
else {
    cout<<"Check your input, choose 1 or 2"<<endl;
}





    return 0;
}