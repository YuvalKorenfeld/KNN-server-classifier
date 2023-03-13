#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <limits>
#include "CLI.h"


using namespace std;

void validateArguments(int argc, char **argv){
    try{
        //if the number of arguments is not 3
        if (argc != 3){
            throw exception();
        }  
        //if the port number is not in the valid range      
        if (!(stoi(argv[2]) >= 1024 && stoi(argv[2]) <= 65535)) {
            throw exception();
        }
        //if the ip address of the server is not a valid ip
        string ip_address = argv[1];
        struct in_addr addr;
        int result = inet_pton(AF_INET, ip_address.c_str(), &addr);
        if(result != 1){
            throw exception();
        }
    }
    catch (const std::exception& e){
        cout << "invalid arguments- please check and try again" << endl;
        exit(1);
    }
}

int main(int argc, char **argv) {

validateArguments(argc, argv);
// getting the ip adress and the port number from the command line
const char* ip_address= argv[1];
const int port_no= stoi(argv[2]);

//creating new socket 
int sock= socket(AF_INET, SOCK_STREAM,0);

//checking if creation of the socket was successfull
if (sock<0){
    perror("error creating socket");
    }


struct sockaddr_in sin;
memset(&sin,0, sizeof(sin));
sin.sin_family= AF_INET;
sin.sin_addr.s_addr= inet_addr(ip_address);
sin.sin_port= htons(port_no);

//send request to connect to server socket
if (connect(sock,(struct sockaddr*) &sin, sizeof(sin)) <0) {
    perror("error connecting to server");
}

//start the chat with the server using CLI and in a socket-based communiation with SocketIO 
SocketIO* dio = new SocketIO(sock);
CLI c(dio);
c.start();

return 0;
}




