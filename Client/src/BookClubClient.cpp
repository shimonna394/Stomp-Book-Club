#include <algorithm>
#include <mutex>
#include "../include/BookClubClient.h"

BookClubClient::BookClubClient(string clientName): name(clientName), inventory(),subId(),joinId(),exitId(),numSubId(1), disConnectId(0),wishList(),isConnected(true),_mutex(),noBook("","-100","") {}


BookClubClient::~BookClubClient() {
 clear();
}

vector<Book> & BookClubClient::getInventory() {
    return inventory;
}

string BookClubClient::getClientName() {
    return name;
}

void BookClubClient::clear() {
    inventory.clear();
    wishList.clear();
}

bool BookClubClient::addToInventory(Book &book) {
    lock_guard <mutex> lock(_mutex);
    {
        vector<Book >::iterator it;
        for (it = inventory.begin(); it != inventory.end(); it++) {
            if (it.operator*().getBookName() == book.getBookName()&&it.operator*().getGenre()==book.getGenre()) {
                it.operator*().addToInInventory();
                return false;
            }
        }
            inventory.push_back(book);
            return true;
    }
}

Book & BookClubClient::hasBook(string name, string genre) {
    bool isThere=false;
    size_t i;
    for(i=0;(i<inventory.size())&(!isThere);i=i+1){
       if((inventory[i].getBookName()==name)&&(inventory[i].getBookStatus()== true)&(inventory[i].getGenre()==genre)){
           isThere=true;
           return inventory[i];
       }
    }
    return noBook;
}

void BookClubClient::removeFromInventory(Book &book) {
    book.removeFromInInventory();
    }

int BookClubClient::getSubId(string topic) {
    map<string,int >::iterator itr;
    int ans=-1;
    for(itr=subId.begin();itr!=subId.end();++itr){
        if(itr.operator*().first==topic)
            ans=itr.operator*().second;
    }
    return ans;
}

void BookClubClient::setSubId(string topic, bool isAdd) {
    if (isAdd) {
        subId.insert(pair<string, int>(topic, numSubId));
        numSubId++;
    } else {
        map<string, int>::iterator itr;
        itr=subId.find(topic);
        if(itr!=subId.end())
            subId.erase(itr);
    }
}

    bool BookClubClient::isSubscribed(string topic) {
        map<string, int>::iterator itr;
        bool isSubscribed = false;
        for (itr = subId.begin(); itr != subId.end(); ++itr) {
            if (itr.operator*().first == topic)
                isSubscribed = true;
        }
        return isSubscribed;
    }

int BookClubClient::getDisConnectId() {
    return disConnectId;
}

void BookClubClient::setDisConnectId(int id) {
    disConnectId=id;
}

bool BookClubClient::removeFromWishList(string bookName) {
    vector<Book>::iterator it;
    for(it=wishList.begin();it!=wishList.end();it++){
        if((it.operator*().getBookName()==bookName)&(it.operator*().getInInventory())){
            it.operator*().removeFromInInventory();
        return true;
        }
    }
    return false;
}

void BookClubClient::addToWishList(Book &book) {
    vector<Book >::iterator it;
    bool hadAdded=false;
    for (it = wishList.begin(); it != wishList.end(); it++) {
        if (it.operator*().getBookName() == book.getBookName()) {
            it.operator*().addToInInventory();
            hadAdded=true;
        }
    }
    if(!hadAdded)
        wishList.push_back(book);
}

void BookClubClient::setIsConnected(bool toConnect) {
    isConnected=toConnect;
}

bool BookClubClient::getIsConnected() {
    return isConnected;
}

void BookClubClient::setJoinedId(bool toAdd, string topic, int id) {
    if(toAdd){
        joinId.insert(pair<int , string>(id,topic));
    }
    else {
        map<int,string>::iterator itr;
        itr=joinId.find(id);
        if(itr!=joinId.end())
            joinId.erase(itr);
    }
}

string BookClubClient::findJoinedId(int id) {
   map<int,string>::iterator itr;
   itr=joinId.find(id);
   if(itr!=joinId.end()){
       return itr.operator*().second;
   }
    return "";
}

void BookClubClient::setExitId(bool toAdd, string topic, int id) {
    map<int,string>::iterator itr;
    if(toAdd){
        exitId.insert(pair<int , string>(id,topic));
    }
    else {
        itr = exitId.find(id);
        if (itr != exitId.end()) {
            exitId.erase(itr);
        }
    }
}

string BookClubClient::findExitId(int id) {
    map<int,string>::iterator itr;
    itr=exitId.find(id);
    if(itr!=exitId.end()){
        return itr.operator*().second;
    }
    return "";
}


