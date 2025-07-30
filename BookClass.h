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

        //displaying all books method 
    static void displayAllBooks(const vector<Book>& bookList) {
    if (bookList.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "\033[1;32m";
    cout << setw(30) << "|| Book ID ||"
         << setw(30) << "||  Title ||"
         << setw(30) << "|| Author ||" << endl;
    cout << "\033[0m";

    for (const auto& book : bookList) {
        cout << setw(30) << book.getID()
             << setw(30) << book.getTitle()
             << setw(30) << book.getAuthor() << endl;
    }
}

//searchoing for all the books
 static void searchbook(const vector<Book>& books,string &keyword){
    bool found=false;
      cout << "\033[1;32m";
    cout << setw(30) << "|| Book ID ||"
         << setw(30) << "||  Title ||"
         << setw(30) << "|| Author ||" << endl;
    cout << "\033[0m";

for (const auto& book : books) {
        if (book.getTitle().find(keyword) != string::npos ||
            book.getAuthor().find(keyword) != string::npos ||
            to_string(book.getID()).find(keyword) != string::npos) {
                
           cout << setw(30) << book.getID()
                 << setw(30) << book.getTitle()
                 << setw(30) << book.getAuthor() << endl;

            found = true;
        }
        
    }
    if (!found) {
        cout << "No books found matching: " << keyword << endl;
    }
 }

};




#endif