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
#include "DefaultIO.h"

using namespace std;

class Command{

public:
    //the description of the command
    string description;

    //abstract method to implement by the successors
    virtual void execute() = 0;

    //the communication type used to interact in the code.
    DefaultIO* dio;

    //constructor
    Command(DefaultIO* dio) {
        this->dio = dio;
    };

};

class UploadDataFile : public Command {
public:
    //constructor
    UploadDataFile(DefaultIO* dio) : Command(dio) {
        this->description = "upload an unclassified csv data file";
    };

    //execute the upload command
    void execute() override {
        cout << "Please upload your local train CSV file." <<endl;

        //get the path from the user to the file
        string userStringInput;
        getline(cin, userStringInput);

        //if the path doesn't exist
        std::ifstream file(userStringInput);
        if (!(file.good())){
           cout << "invalid input" << endl;
           return;
        }

        //send to server 1 option
        string option = "1";

        //sending to the server the data from the user
        this->dio->write(option);

        //if reached here, file is valid

        //send the contect of the file row by row to the server
        string row;
        ifstream MyReadFile(userStringInput);
        //read each row (vector) from the file
        while (getline (MyReadFile, row)) { 
            row += "\n";
            this->dio->write(row);
        }

        //close the file
        MyReadFile.close();

        //send $ to mark end of file
        string doNothing = "$";
        this->dio->write(doNothing);

        //recv from server upload complete
        string data = this->dio->read();
        
        //prints answer
        cout << data << endl;

        //for the second file - the test file
        cout << "Please upload your local test CSV file." <<endl;

        //get the path to the file
        string userStringInput2;
        getline(cin, userStringInput2);

        //if the file doesn't exist
        std::ifstream file2(userStringInput2);
        if (!(file2.good())){
           cout << "invalid input" << endl;
           string doNothing2 = "%";    
           this->dio->write(doNothing2);
           return;
        }

        //if reached here, file is valid

        //send the contect of the file row by row to the server
        string row2;
        ifstream MyReadFile2(userStringInput2);
        while (getline (MyReadFile2, row2)) { 
            row2 += "\n";
            this->dio->write(row2);
        }
        //close the file
        MyReadFile2.close();

        //send $ to mark end of file
        string doNothing2 = "%";
        this->dio->write(doNothing2);

        //recv from server upload complete
        string data2 = this->dio->read();

        //prints answer
        cout << data2 << endl;
    }
};

class AlgoSetting : public Command {
public:
    //costructor
    AlgoSetting(DefaultIO* dio) : Command(dio) {
        this->description = "algorithm settings";
    };

    //implement the execution of the second option
    void execute() override {
        //send to server 2 option
        string option = "2";

    //sending to the server the data from the user
    this->dio->write(option);

    //server handles and send answer
    string data = this->dio->read();

    //prints answer
    cout << data << endl;

    //get the input k and metric from user
    string userStringInput;
    getline(cin, userStringInput);
        //if the user did not input enter
        if (!((userStringInput.empty()) || userStringInput == "\n")){
            
            stringstream ss(userStringInput.c_str());
            string token;
            getline(ss, token, ' ');
            int kNum;
            //check if the user entered a valid int for k
            try{
                kNum = stoi(token);
            }
            //if the k is not vaild
            catch (const std::exception& e){
                getline(ss, token, ' ');
                string metric = token;
                //test the input for metric
                if (metric != "AUC" && metric != "MAN" && metric != "CHB" && metric != "CAN" && metric != "MIN"){
                    cout << "invalid value for metric" <<endl;
                }

                cout << "invalid value for K" << endl;
                string doNothing = "$";
                this->dio->write(doNothing);
                return;
            }
                
            getline(ss, token, ' ');
            string metric = token;
                
            //run tests on metric
            if (metric != "AUC" && metric != "MAN" && metric != "CHB" && metric != "CAN" && metric != "MIN"){
                cout << "invalid value for metric" <<endl;
                //if the k is negative
                if(kNum <=0){
                    cout <<"invalid value for K"<< endl;
                }
                string doNothing = "$";
                this->dio->write(doNothing);
                return;
                    
            }
            //run tests on k
            if (kNum <= 0){
                cout << "invalid value for K" <<endl;
                string doNothing = "$";
                this->dio->write(doNothing);
                return;
            }
            //send the server the new k and metric
            this->dio->write(userStringInput);
            return;
    }
    //the user inputed only enter
    else{
        string doNothing = "$";
        this->dio->write(doNothing);
        return;
    }
} 
};

class ClassifyData : public Command {
public:
    //contructor
    ClassifyData(DefaultIO* dio) : Command(dio) {
        this->description = "classify data";
    };

    //execution for the third option
    void execute() override {
    //send to server 3 option
    string option = "3";

    //sending to the server the data from the user
    this->dio->write(option);

    //server handles and send answer
    string data = this->dio->read();

    //prints answer
    cout << data << endl;
    }
};

class DisplayResults : public Command {
public:
    //constructor
    DisplayResults(DefaultIO* dio) : Command(dio) {
        this->description = "display results";
    };

    //execution for the forth option
    void execute() override {
        //send to server 4 option
        string option = "4";

        //sending to the server the data from the user
        this->dio->write(option);

        //server handles and send answer
        string data = this->dio->read();

        //prints answer
        if( data != "please upload data" && data != "please classify the data"){
            cout << data;
            cout << "Done." << endl;
        }
        else{
            cout << data << endl;
        }
    } 
};

class DownloadResults : public Command {
public:
    //constructor
    DownloadResults(DefaultIO* dio) : Command(dio) {
        this->description = "download results";
    };

    //method to write to a file the user asked for
    void writeToFile(string pathToFile){
    std::ofstream file(pathToFile);
        //if the path does not exist
        if (!file.is_open()) {
            std::cout << "invalid input" << std::endl;
            return;
        }
    //write to file the content
    string data = this->dio->read();
    file << data;
    file.close();
    }

    //execution of the fifth option
    void execute() override {        
        //send to server 5 option
        string option = "5";

        //sending to the server the data from the user
        this->dio->write(option);

        //server handles and send answer
        char indicator = this->dio->readChar();

        if (indicator == '$'){
            string data = this->dio->read();
            //check that the data is uploaded and classified

            string error1 = "please classify the data";
            string error2 = "please upload data";

            if (error1.compare(data) == 0) {
                cout << data << endl;
                return;
            }
            if (error2.compare(data) == 0) {
                cout << data << endl;
                return;
            }
        }
        
        //if reached here data is uploaded and classified
        std::string path;
        std::getline(std::cin, path);

        //if the file is not valid
        std::ofstream file(path);
        if (!file.is_open()) {
            std::cout << "invalid input" << std::endl;
            //do we need to send something to server to stop from sending the file data--------------------------
            return;
        }
        file.close();

        //open a thread that write the contect to the file while the main program continue immediately
        std::thread t(&DownloadResults::writeToFile, std::ref(*this), path);
        t.detach();
    }

};

class ExitCommand : public Command {
public:
    //constructor
    ExitCommand(SocketIO* dio) : Command(dio) {
        this->description = "exit";
    };

    //execution of the exit option
    void execute() override {        
        //send to server 8 option
        string option = "8";

        //sending to the server the data from the user
        this->dio->write(option);

        //close the socket of the client
        close(this->dio->clientID);

        //exit program
        exit(1);
    }
};

