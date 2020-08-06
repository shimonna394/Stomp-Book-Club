#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include "../include/connectionHandler.h"
#include "../include/BookClubClient.h"
#include "../include/MessageEncoderDecoder.h"
#include "../include/KeyBoardReader.h"
using  namespace std;
/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
vector<string> subWordreceived(string msg) {
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

int main (int argc, char *argv[]) {
    string firstWord;
    string connect;
    do {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        connect=line;
        firstWord=line.substr(0,line.find_first_of(' '));
        }while(firstWord.compare("login")!=0);
    vector<string> login=subWordreceived(connect);//returns login Client info
    std::string host =login[1].substr(0,login[1].find(":"));
    short port = stoi(login[1].substr(login[1].find(":")+1,login[1].size()));
    ConnectionHandler connectionHandler(host, port);//creating a connection with the server
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    BookClubClient* client=new BookClubClient(login[2]);
    MessageEncoderDecoder* encdec=new MessageEncoderDecoder(client);
    string toSend=encdec->encode(connect);
    if(!connectionHandler.sendLine(toSend))
        std::cout << "Disconnected. Exiting...\n" << std::endl;
    cout<<"send"<<endl;
    string received;
    if(connectionHandler.getLine(received)) {
        encdec->decode(received);
    }
    string cmd=received.substr(0,received.find("\n"));
    if(cmd=="ERROR") {
        cout<<received<<endl;
        client->setIsConnected(false);
    }
    if(client->getIsConnected()) {
        KeyBoardReader keyBoardReader(encdec,connectionHandler);
        thread KeyBoardReaderThread(&KeyBoardReader::run, &keyBoardReader);
        while(client->getIsConnected()){
           string received;
           string toSend;
            if(connectionHandler.getLine(received)) {
                toSend = encdec->decode(received);
            }
            cmd=toSend.substr(0,toSend.find("\n"));
            if(cmd=="ERROR"){
                cout<<toSend<<endl;
                client->setIsConnected(false);
            }
            else if((toSend!="")&(client->getIsConnected()))
                if(!connectionHandler.sendLine(toSend))
                    break;
        }
       KeyBoardReaderThread.join();
   }
    cout << "CLIENT GOING TO CLOSE" << endl;
    connectionHandler.close();
    return 0;

}

