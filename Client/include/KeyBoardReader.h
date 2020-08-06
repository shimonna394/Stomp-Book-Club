//
// Created by shimonna@wincs.cs.bgu.ac.il on 13/01/2020.
//

#ifndef ASSIGNMENT3_KEYBOARDREADER_H
#define ASSIGNMENT3_KEYBOARDREADER_H

#include <future>
#include "MessageEncoderDecoder.h"
#include "connectionHandler.h"

using  namespace std;
class KeyBoardReader{
public:
    KeyBoardReader(MessageEncoderDecoder *encdec, ConnectionHandler &handler);
    KeyBoardReader(const KeyBoardReader &other);
    KeyBoardReader &operator=(const KeyBoardReader &s);
    ~KeyBoardReader();
    void run();
    void clear();

private:
    MessageEncoderDecoder *encdec;
    ConnectionHandler &handler;
    BookClubClient* client;
};
#endif //ASSIGNMENT3_KEYBOARDREADER_H
