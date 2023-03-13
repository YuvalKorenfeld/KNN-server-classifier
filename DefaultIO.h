#include <sstream>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <limits>
#include <fstream>
#include <thread>

using namespace std;

// abstract class used to define ways to interact with users
class DefaultIO {
public:

    // read a string from user
    virtual string read()=0;

    virtual char readChar() = 0;

    // write a string to the user
    virtual void write(string text)=0;

    int clientID;
};

//chat with user using standard input and output
class StandardIO: public DefaultIO {

    //read from terminal
    string read() override {
        string input;
        cin >> input;
        return input;
    }

    //write to terminal
    void write(string text) override {
        cout << text;
    }

    //read char from terminal
    char readChar() override {
        char input;
        cin >> input;
        return input; 
    }
};


//chat with server and user using sockets
class SocketIO: public DefaultIO {
    
public:
    // constructor
    SocketIO(int id){
        this->clientID = id;
    };

    // read a string using socket
    string read() override {
        char buffer[409600]{};
        int read_bytes = recv(this->clientID, buffer, sizeof(buffer), 0);
        std::string str(buffer);
        return str;
    }

    // read a char using socket
    char readChar(){
        char temp = 0;
        recv(this->clientID, &temp, sizeof(char), 0);
        return temp;
    }

    // write a string using socket
    void write(string text) override {
        send(this->clientID, text.c_str(), text.length(), 0);
    }
};
