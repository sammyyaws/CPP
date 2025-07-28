/**this file contains the class for the book */
#ifndef BOOKCLASS_H
#define BOOKCLASS_H
#include <string>


using namespace std;
//contains the book class
class Book{
private:
int ID;
string title;
string author;
bool issued_status;

public:
Book(int id,string title,string author,bool status=false):ID(id),title(title),author(author),issued_status(status){};

  // Getters
    int getID() const {
         return ID; }

    string getTitle() const { 
        return title; }

    string getAuthor() const { 
        return author; }
    bool isIssued() const {
         return issued_status; }
         
   // Setters
    void setTitle(const string newTitle) { 
        title = newTitle; }
    void setAuthor(const string newAuthor) {
         author = newAuthor; }
         //function to set the issued status of the book
    void setIssuedStatus(bool status) { 
        issued_status = status; }


};




#endif