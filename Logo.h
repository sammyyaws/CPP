#ifndef LOGO_H
#define LOGO_H

#include <iostream>
#include <iomanip>
using namespace std;
void showLogo(){
  cout <<"\033[1;31m"; 
    cout <<setw(50)<<"=>>>>>>>>>>>>>>>>>>>>========================================>>>=================>>>>>>>>>>>>>>>>>>>>\n"<<endl;
     cout <<"\033[0m"; 
     //center text
    cout <<"\033[1;32m";
    cout << setw(65)<<"Welcome to LIBMAS Library  \n" << endl;
     cout <<"\033[0m"; 
     
     //end bars
     cout <<"\033[1;31m"; 
     cout <<setw(50)<<"=>>>>>>>>>>>>>>>>>>>>========================================>>>=================>>>>>>>>>>>>>>>>>>>>\n"<<endl;
    cout <<"\033[0m"; 

}





#endif