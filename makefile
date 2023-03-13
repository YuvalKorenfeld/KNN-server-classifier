CC=g++
CFLAGS=-std=c++11 -c

all: server.out client.out

server.out: server.o Knn.o Distance.o 
	$(CC) server.o Knn.o Distance.o -pthread -o server.out

client.out: client.o Knn.o Distance.o CLI.o
	$(CC) client.o Knn.o Distance.o CLI.o -pthread -o client.out

server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp

client.o: client.cpp
	$(CC) $(CFLAGS) client.cpp

Knn.o: Knn.cpp
	$(CC) $(CFLAGS) Knn.cpp

Distance.o: Distance.cpp
	$(CC) $(CFLAGS) Distance.cpp

CLI.o: CLI.cpp
	$(CC) $(CFLAGS) CLI.cpp

clean:
	rm -rf *.o
