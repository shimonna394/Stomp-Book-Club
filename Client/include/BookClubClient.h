#ifndef ASSIGNMENT3_BOOKCLUBCLIENT_H
#define ASSIGNMENT3_BOOKCLUBCLIENT_H
#include <vector>
#include <string>
#include "Book.h"
#include <map>

using  namespace std;
class BookClubClient{
public:
    BookClubClient(string name);
    ~BookClubClient();
    vector<Book> & getInventory();
    bool addToInventory(Book &book);
    void removeFromInventory(Book &book);
    string getClientName();
    Book &hasBook(string name, string genre);
    int getSubId(string topic);
    void setSubId(string topic,bool isAdd);
    bool isSubscribed(string topic);
    void setDisConnectId(int id);
    int getDisConnectId();
    void addToWishList(Book &book);
    bool removeFromWishList(string bookName);//if the book is in the wish list returns true and removes it, else returns false
    bool getIsConnected();
    void setIsConnected(bool toConnect);
    void setJoinedId(bool toAdd,string topic,int id);
    string findJoinedId(int id);
    void setExitId(bool toAdd,string topic,int id);
    string findExitId(int id);

private:
    string name;
    vector<Book> inventory;
    map<string,int >subId;//holds the subId for each topic for this client
    map<int,string >joinId;
    map<int,string >exitId;
    int numSubId;
    int disConnectId;
    vector<Book> wishList;
    bool isConnected;
    void clear();
    mutex _mutex;
    Book noBook;
};
#endif //ASSIGNMENT3_BOOKCLUBCLIENT_H
