#include "../include/Book.h"
#include <vector>
using  namespace std;

/*************************************************public*******************************************************/
Book::Book(string owner, string bookName, string genre): currentOwner(owner), bookName(bookName), prevOwner(""), inInventory(true), genre(genre) {}

Book::~Book() {
}

string Book::getBookName() {
    return bookName;
}

string Book::getBookOwner() {
    return currentOwner;
}
void Book::setPrevOwners(string prevOwner) {
   this->prevOwner=prevOwner;
}
void Book::setCurrentOwner(string newOwner) {
    currentOwner=newOwner;
}
string Book::getGenre() {
    return this->genre;
}

/***************************************************private****************************************************/
bool Book::getInInventory() {
    return inInventory ;
}

void Book::removeFromInInventory() {
    inInventory=false;
}

void Book::addToInInventory() {
    inInventory=true;
}

string & Book::getPrevOwner() {
    return prevOwner;
}

bool Book::getBookStatus() {
    return inInventory;
}









