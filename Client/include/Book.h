
#ifndef ASSIGNMENT3_BOOK_H
#define ASSIGNMENT3_BOOK_H
#include <vector>
#include <string>

using  namespace std;
class Book{
public:
    Book(string owner, string bookName, string genre);
    ~Book();
    string getBookName();
    string getBookOwner();
    void setPrevOwners(string prevOwner);
    string & getPrevOwner();
    void setCurrentOwner(string newOwner);
    bool getInInventory();
    bool getBookStatus();
    void removeFromInInventory();
    void addToInInventory();
    string getGenre();
private:
    string currentOwner;
    string bookName;
    string prevOwner;
    bool inInventory;
    string genre;
    void clear();


};
#endif //ASSIGNMENT3_BOOK_H