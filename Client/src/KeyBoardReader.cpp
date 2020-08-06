#include "../include/KeyBoardReader.h"

KeyBoardReader::KeyBoardReader(MessageEncoderDecoder *encdec, ConnectionHandler &handler) : encdec(encdec), handler(handler), client(encdec->getClient()) {}

KeyBoardReader::~KeyBoardReader() {
    clear();
}
void KeyBoardReader::clear() {
    delete(encdec);
}
void KeyBoardReader::run() {
    bool run=true;
    while (client->getIsConnected()& run) {
        cout<<"enter input"<<endl;
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        string toSend=encdec->encode(line);
        if(line=="logout")
            run= false;
        if((client->getIsConnected())&(toSend!="")) {
            if (!handler.sendLine(toSend)) {
                cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
        }

    }
}

KeyBoardReader::KeyBoardReader(const KeyBoardReader &other):encdec(other.encdec),handler(other.handler),client(encdec->getClient()) {}

KeyBoardReader &KeyBoardReader::operator=(const KeyBoardReader &s) {
    {
        if (this != &s) {
            clear();
            encdec=s.encdec;
            client=s.client;
        }
        return *this;
    }

}
