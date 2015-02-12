
CC=g++
CFLAGS=-std=c++0x -Wall -lboost_system

all:	clean test

#test: server.cpp
	#$(CC) server.cpp -o server $(CFLAGS)


Session.o: Session.cpp Session.h
	$(CC) -Wall -c Session.cpp

Server.o: Server.cpp Server.h
	$(CC) -Wall -c Server.cpp

main.o: main.cpp
	$(CC) -Wall -c main.cpp



test: Server.o Session.o main.o
	$(CC) Server.o Session.o main.o -o server $(CFLAGS)



clean:
	rm -rf server *.o
