#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Logo.h"
#include "User.h"
#include "UserClass.h"
#include "LibarianClass.h"
 using namespace std;

 //variable declaration
 int login_as;
int LoginUserID;
 
//book class for all book objects
class Book{

 private:
  Book(int ID,string title,string author){

    };


};

//array to store the user data
 vector<User>  users;

/*********************************Main Function ************************************************* */

int main (){
    //including the intro part
   showLogo();

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

}
else {
    cout<<"Check your input, choose 1 or 2"<<endl;
}





    return 0;
}