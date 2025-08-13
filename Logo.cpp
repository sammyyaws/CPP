#include "Logo.h"
#include <iostream>
#include <iomanip>
using namespace std;

void showLogo() {
    cout << "\033[1;31m"; 
    cout << setw(50) << "=>>>>>>>>>>>>>>>>>>>>========================================>>>=================>>>>>>>>>>>>>>>>>>>>\n" << endl;
    cout << "\033[0m"; 

    cout << "\033[1;32m";
    cout << setw(65) << "Welcome to LIBMAS Library\n" << endl;
    cout << "\033[0m"; 

    cout << "\033[1;31m"; 
    cout << setw(50) << "=>>>>>>>>>>>>>>>>>>>>========================================>>>=================>>>>>>>>>>>>>>>>>>>>\n" << endl;
    cout << "\033[0m"; 
}


/******************* All right reserved:Group 12 Project Lead By Adade Samuel Yawson ********************/
