CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system  -lstdc++ -pthread



all: StompBookClubClient


StompBookClubClient: bin/BookClubClient.o bin/Book.o  bin/Client.o  bin/MessageEncoderDecoder.o bin/KeyBoardReader.o  bin/connectionHandler.o 

	@echo 'Building target: StompBookClubClient'
	@echo 'Invoking: C++ Linker'
	$(CC) -o bin/StompBookClubClient bin/Book.o  bin/Client.o  bin/MessageEncoderDecoder.o bin/KeyBoardReader.o bin/connectionHandler.o bin/BookClubClient.o $(LDFLAGS) 
	@echo 'Finished building target: StompBookClubClient'
	@echo ' '

	

bin/BookClubClient.o: src/BookClubClient.cpp
	g++ $(CFLAGS) -o bin/BookClubClient.o src/BookClubClient.cpp

bin/connectionHandler.o: src/connectionHandler.cpp
	g++ $(CFLAGS) -o bin/connectionHandler.o src/connectionHandler.cpp

bin/Book.o: src/Book.cpp
	g++ $(CFLAGS) -o bin/Book.o src/Book.cpp

bin/Client.o: src/Client.cpp
	g++ $(CFLAGS) -o bin/Client.o src/Client.cpp

bin/MessageEncoderDecoder.o: src/MessageEncoderDecoder.cpp
	g++ $(CFLAGS) -o bin/MessageEncoderDecoder.o src/MessageEncoderDecoder.cpp

bin/KeyBoardReader.o: src/KeyBoardReader.cpp
	g++ $(CFLAGS) -o bin/KeyBoardReader.o src/KeyBoardReader.cpp

	
.PHONY: clean
clean:
	rm -f bin/*
