#include <iostream>
#include <mutex>
#include "../include/MessageEncoderDecoder.h"
/* ------------------ constructors -------------------- */

// Constructor
MessageEncoderDecoder::MessageEncoderDecoder(BookClubClient* client) :  len(0),_mutex(),numReceipt(1),numOfLine(0),toDecode(), bytesVector(), decodedMessage(""),client(client) {}

// Destructor
MessageEncoderDecoder::~MessageEncoderDecoder() {
    clear();
}
MessageEncoderDecoder::MessageEncoderDecoder(const MessageEncoderDecoder &other):len(0),_mutex(),numReceipt(1),numOfLine(0),toDecode(), bytesVector(), decodedMessage(""),client((other.client)) {}

void MessageEncoderDecoder::clear() {
    bytesVector.clear();
    len=0;
    numReceipt=0;
    delete(client);
}

/****************************************************Encode**************************/
string MessageEncoderDecoder::encode(string message) {
    vector<string>input= subWordInput(message);

    string ans;
    if(input[0]=="login"){
        ans= processLogin(input);
    }
    else if(input[0]=="join"){
        ans= processJoin(input);
    }
    else if(input[0]=="add"){
        ans= processAdd(input);
    }
    else if(input[0]=="borrow"){
        ans= processBorrow(input, input[1]);

    }
    else if(input[0]=="return"){
        ans= processReturn(input, input[1]);
    }
    else if(input[0]=="status"){
        ans= processStatus(input);
    }
    else if(input[0]=="logout"){
        ans= processLogout(input);
    }
    else if(input[0]=="exit"){
        ans= processExit(input);
    }
    return ans;
}
string MessageEncoderDecoder::processLogin(vector<string> input) {
    string ans="CONNECT\naccept-version:1.2\nhost:stomp.cs.bgu.ac.il\nlogin:"+input[2]+"\npasscode:"+input[3]+"\n\n";
    client->setIsConnected(true);
    return ans;
}

string MessageEncoderDecoder::processJoin(vector<string> input) {
    string numRec=to_string(numReceipt);
    client->setJoinedId(true,input[1],numReceipt);
    numReceipt++;
    bool isJoined= false;
    if(client->isSubscribed(input[1]))
        isJoined=true;
    string ans="";
    if(!isJoined) {
        client->setSubId(input[1],true);
        string numSub=to_string(client->getSubId(input[1]));
        ans="SUBSCRIBE\ndestination:" + input[1] + "\nid:" + numSub + "\nreceipt:" + numRec + "\n\n";
    }
    return ans;
}

string MessageEncoderDecoder::processAdd(vector<string> input) {
    string bookName=input[2];
    for(size_t i=3;i<input.size();i++){
        bookName=bookName+" "+input[i];
    }
    string ans="SEND\ndestination:"+input[1]+"\n\n"+client->getClientName()+" has added the book "+bookName+ "\n";
    Book book( client->getClientName(),bookName,input[1]);
    client->addToInventory( book);
    return ans;
}

string MessageEncoderDecoder::processBorrow(vector<string> input, string des) {
    string ans="";
    string bookName=input[2];
    for(size_t i=3;i<input.size();i++){
        bookName=bookName+" "+input[i];
    }
    if(client->hasBook(bookName, des).getBookName() == "-100") {
        Book book("", bookName, input[1]);
        client->addToWishList( book);
        ans = "SEND\ndestination:" + input[1] + "\n\n" + client->getClientName() + " wish to borrow " + bookName + "\n";
    }
    return ans;
}

string MessageEncoderDecoder::processReturn(vector<string> input, string des) {
    string bookName=input[2];
    for(size_t i=3;i<input.size();i++){
        bookName=bookName+" "+input[i];
    }
    string ans="";
    if(client->hasBook(bookName, des).getBookName() != "-100" && client->hasBook(bookName,des).getPrevOwner() != ""){
        Book book= client->hasBook(bookName, des);
        client->hasBook(bookName, des).removeFromInInventory();
        string prevOwner=book.getPrevOwner();
        ans="SEND\ndestination:"+input[1]+"\n\n"+"Returning "+bookName+" to "+prevOwner+"\n";
    }
    return ans;
}

string MessageEncoderDecoder::processStatus(vector<string> input) {
    string ans="SEND\ndestination:"+input[1]+"\n\nbook status\n";
    return ans;
}

string MessageEncoderDecoder::processExit(vector<string> input) {
    string numRec=to_string(numReceipt);
    string numSub=to_string(client->getSubId(input[1]));
    client->setExitId(true,input[1],numReceipt);
    client->setSubId(input[1], false);
    numReceipt++;
    string ans="UNSUBSCRIBE\nid:"+numSub+"\nreceipt:"+numRec+"\n\n";
    return ans;
}

string MessageEncoderDecoder::processLogout(vector<string> input) {
    string numRec=to_string(numReceipt);
    client->setDisConnectId(numReceipt);
    numReceipt++;
    string ans="DISCONNECT\nreceipt:"+numRec+"\n\n";
    return ans;
}

/*************************************************Decode****************************************************/
string MessageEncoderDecoder::decode(string toDcode) {
this->toDecode=toDcode;
if(toDcode!="")
    return parseMessage();
else
    return "";
}


// returns a vector that holds the input word by word
vector<string> MessageEncoderDecoder::subLineInput(string msg) {
    vector<string> ans;
    while(msg.size()>0){
        int pos2=msg.find("\n");
        if(pos2!=-1){
            ans.push_back(msg.substr(0,pos2));
            msg = msg.substr(pos2+1, msg.size());
        }
        else if(msg.size()>0) {
            ans.push_back(msg);
            msg = "";
        }
    }

    return ans;
}

string MessageEncoderDecoder::parseMessage() {
    string ans="";
    vector<string> input = subLineInput(toDecode);
    if(input[0]=="MESSAGE") {
        ans=processMessage(input);
    }
    if(input[0]=="RECEIPT")
        ans=processReceipt(input);
    if(input[0]=="CONNECTED") {
        cout<<client->getClientName()+" login successful"<<endl;
        client->setIsConnected(true);
    }
    if(input[0]=="ERROR"){
        ans=toDecode;
        client->setIsConnected(false);
    }
    return ans;
}

string MessageEncoderDecoder::processMessage(vector<string> input) {
    vector<string> frameBody = subWordInput(input[5]);
    string ans = "";
    string des = input[3].substr(input[3].find_first_of(':')+1);
        if (frameBody.size() > 1 && frameBody[1] == "wish") {
            ans = processWish(input, frameBody, des);
        } else if (frameBody[0] == "Taking") {
            processTaking(input, frameBody,  des);
        } else if (frameBody[0] == "Returning") {
            processReturning(input, frameBody, des);
        } else if (frameBody.size() > 1 && frameBody[1] == "status") {
            ans = processStatusReceived(input, frameBody, des);
        } else if (frameBody.size() > 2 &&
                (frameBody[1] == "has") & (frameBody[2] == "added")) {
            processAdded(input, frameBody);
        } else if (frameBody.size() > 1 && frameBody[1] == "has") {
            ans = processHas(input, frameBody, des);
        } else if (int (input[5].find(':')) != -1) {
            bookStatus(input[5]);
        }
    if (ans != "")
        return ans + "";
    return ans;
    }

    string MessageEncoderDecoder::processReceipt(vector<string> input) {
        int pos = input[1].find(":");
        int post2 = input[1].find("\n");
        string id = input[1].substr(pos + 1, post2);
        int recId = stoi(id);
        if (recId == client->getDisConnectId()) {
            client->setIsConnected(false);
            return "DISCONNECT";
        }
        else{
            string topic=client->findJoinedId(recId);
            if(topic!=""){
                cout<<client->getClientName()+" joined club "+topic<<endl;
                client->setJoinedId(false,topic,recId);
                return "";
            }
        }
        string topic=client->findExitId(recId);
        if(topic!=""){
            cout<<client->getClientName()+" exited club "+topic<<endl;
            client->setExitId(false,topic,recId);
        }
        return "";
    }

    string MessageEncoderDecoder::processWish(vector<string> input, vector<string> frameBody, string des) {
        string ans="";
        string bookName = frameBody[4];
        for (size_t i = 5; i < frameBody.size(); i++) {
            bookName = bookName + " " + frameBody[i];
        }
        Book b= client->hasBook(bookName, des);
        if(b.getBookName()!= "" && b.getBookName()==bookName) {
            ans = "SEND\ndestination:" + des + "\n\n" + client->getClientName() + " has " + bookName+"\n";
        }
        cout<<input[5]<<endl;
        return ans;
    }

    void MessageEncoderDecoder::processTaking(vector<string> input, vector<string> frameBody, string des) {
        string bookName = frameBody[1];
        size_t pos = 2;
        while (pos < frameBody.size() && frameBody[pos] != "from") {
            bookName = bookName + " " + frameBody[pos];
            pos++;
        }
        string clientName = frameBody[pos + 1];
        if (clientName == client->getClientName()) {
            client->hasBook(bookName, des).removeFromInInventory();
        }
    }

    void MessageEncoderDecoder::processReturning(vector<string> input, vector<string> frameBody, string des) {
        string bookName = frameBody[1];
        size_t pos = 2;
        while (pos < frameBody.size() && frameBody[pos] != "to") {
            bookName = bookName + " " + frameBody[pos];
            pos++;
        }
        string clientName = frameBody[pos + 1];
        if (clientName == client->getClientName()) {
            Book book("",bookName,des);
            client->addToInventory( book);
            cout << input[5] << endl;
        }
    }

    string MessageEncoderDecoder::processHas(vector<string> input, vector<string> frameBody, string des) {
        string bookName = frameBody[2];
        string ans = "";
        for (size_t i = 3; i < frameBody.size(); i++)
            bookName = bookName + " " + frameBody[i];
        if (client->removeFromWishList(bookName)) {
            ans = "SEND\ndestination:" + des + "\n\nTaking " + bookName + " from " + frameBody[0]+"\n";
            Book book= Book(client->getClientName(),bookName,des);
            book.setPrevOwners(frameBody[0]);
            client->addToInventory(book);
        }
        cout << input[5] << endl;
        return ans;
    }

    string MessageEncoderDecoder::processStatusReceived(vector<string> input, vector<string> frameBody, string des) {
        cout << "book status" << endl;
        string ans = "SEND\ndestination:" + des + "\n\n" + client->getClientName() + ":";
        for (size_t i = 0; i < client->getInventory().size(); i++) {
            if (client->getInventory()[i].getBookStatus()&&client->getInventory()[i].getGenre()==des) {
                ans = ans + client->getInventory()[i].getBookName()+",";
            }
        }
        if(ans.at(ans.size()-1)!=':')
            ans=ans.substr(0,ans.size()-1);
        return ans+'\n';
    }

BookClubClient* MessageEncoderDecoder::getClient() {
    return client;
}

vector<string> MessageEncoderDecoder::subWordInput(string msg) {
    vector<string> ans;
    while(msg.size()>0){
        int pos=msg.find(" ");
        if (pos != -1) {
            ans.push_back(msg.substr(0, pos));
            msg = msg.substr(pos + 1, msg.size());
        } else {
            ans.push_back(msg);
            return ans;
        }
    }
    return ans;
}

void MessageEncoderDecoder::processAdded(vector<string> input, vector<string> frameBody) {
    cout<<input[5]<<endl;
}
void MessageEncoderDecoder::bookStatus(string input) {
    cout << input << endl;
}

MessageEncoderDecoder &MessageEncoderDecoder::operator=(const MessageEncoderDecoder &s) {
    if (this != &s) {
        clear();
        client = s.client;
    }
    return *this;
}








