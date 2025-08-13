///make sure you read the README.md

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

//array to  store librarian data
 vector<Librarian> Librarians ;


/*********************************Main Function ************************************************* */

int main (){
  //checking for the database to start
if (!initDatabase(&db)) {
    cerr << "Failed to initialize the database. Exiting..." << endl;
    return 1;
}

   


   //start of excution
start:

 cout <<"\033[3;35m";  
cout<<"Login as a :"<<endl;
cout <<setw(20)<<"1:USER"<<setw(20)<<"2:LIBRIAN \n"<<endl;
  cout <<"\033[0m"; 
cin>>login_as;

//getting
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
    Librarians.push_back(Librarian(10101, "Mr. Mensah", books));
    Librarians.push_back(Librarian(10202, "Ms. Afua", books));
    Librarians.push_back(Librarian(10303, "Dr. Kofi", books));
    
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
















/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
