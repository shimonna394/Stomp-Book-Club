//
// Created by shimonna@wincs.cs.bgu.ac.il on 10/01/2020.
//

#ifndef ASSIGNMENT3_MESSAGEENCODERDECODER_H
#define ASSIGNMENT3_MESSAGEENCODERDECODER_H

#include <vector>
#include "BookClubClient.h"


using  namespace std;
class MessageEncoderDecoder {
public:
    MessageEncoderDecoder(BookClubClient* client);
    ~MessageEncoderDecoder();
    MessageEncoderDecoder(const MessageEncoderDecoder &other);
    string encode(string message);
    string decode(string byte);
    BookClubClient* getClient();
    MessageEncoderDecoder &operator=(const MessageEncoderDecoder &s);

private:
    int len;
    mutex _mutex;
    int numReceipt;
    int numOfLine;
    string toDecode;
    vector<char > bytesVector;
    string decodedMessage;
    BookClubClient* client;
    void clear();
    vector<string> subLineInput(string msg);
    string processLogin(vector<string> input);
    string processJoin(vector<string> input);
    string processAdd(vector<string> input);
    string processBorrow(vector<string> input, string des);
    string processReturn(vector<string> input, string des);
    string processStatus(vector<string> input);
    string processExit(vector<string> input);
    string processLogout(vector<string> input);
//    string sendBook(string des,Book* book);
    string parseMessage();
    string processMessage(vector<string> input);
    string processReceipt(vector<string>input);
    string processWish(vector<string>input,vector<string>frameBody,string des);
    void processTaking(vector<string> input, vector<string> frameBody, string des);
    void processReturning(vector<string> input, vector<string> frameBody, string des);
    string processHas(vector<string>input,vector<string>frameBody,string des);
    string processStatusReceived(vector<string>input,vector<string>frameBody,string des);
    void processAdded(vector<string>input,vector<string>frameBody);
    vector<string> subWordInput(string msg);
    void bookStatus(string input);


};
#endif //ASSIGNMENT3_MESSAGEENCODERDECODER_H
