#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Knn.h"
#include <vector>
#include <sstream>
#include <thread>
#include "DefaultIO.h"

using namespace std;

void validateArguments(int argc, char **argv){
    try{
        //if the number of arguments is not 2
        if (argc != 2){
            throw exception();
        }  
        //if the port number is not in the valid range      
        if (!(stoi(argv[1]) >= 1024 && stoi(argv[1]) <= 65535)) {
            throw exception();
        }
    }
    catch (const std::exception& e){
        cout << "invalid arguments- please check and try again" << endl;
        exit(1);
    }
}

void changeAlgoSettings(SocketIO* dio, Knn* knnObj){
    
    string firstParameters = "The current KNN parameter are: K = " + to_string(knnObj->k) + ", distance metric = " + knnObj->distanceFuncName;
    
    //write the initial string to the client
    dio->write(firstParameters);

    //recieve the k and metric to change
    string data = dio->read();
    
    if (data[0] == '$'){
        return;
    }
    //if the k and metric is valid
    else{
        //split k and metric using space
        stringstream ss(data);
        string token;
        getline(ss, token, ' ');
        int kNum = stoi(token);
        getline(ss, token, ' ');
        string metric = token;

        //set the knn object of the specific client to be the k and metric he entered
        knnObj->setDistanceFunction(metric);
        knnObj->setK(kNum);
        return;
    }
}

void uploadCSV(DefaultIO* dio, Knn* knnObj){

    string uploadComplete = "Upload complete.";
    string fileContent;
    
    //read the contect of the file
    char temp;
    while(1){
        temp=0;
        char temp = dio->readChar();
        if (temp == '$'){
            break;
        }
        fileContent += temp;
    }

    //split the file contect for each vector and put it in the dataVector inside the knn
        vector< vector<string> > dataVector;
        Distance d;
        std::string line;
        std::istringstream iss(fileContent);
        vector <string> temparary;
        vector <string> result;
        while (std::getline(iss, line, '\n')) {
            result.clear();
            result.push_back("0");
            temparary = d.convertStringToStringVector(line);
            result.push_back(temparary[temparary.size() -1]);
            temparary.pop_back();
            int size = temparary.size();
        
            for (int i=0; i<size; i++) {
                result.push_back(temparary[i]);
            }

            //insert the vector from the knn dataVector in this order: distance, name, value1, value2,...
            dataVector.push_back(result);
        }
        //set the dataVector of the knn to be the dataVector we just created
        knnObj->setDataVector(dataVector); 
 
        //send client Upload complete.
        dio->write(uploadComplete);

    //read test file
    string unClassifiesContent;
    temp =0;
    temp = dio->readChar();
    if (temp == '%'){
        return;
    }
    unClassifiesContent += temp;
    while(1){
        temp=0;
        temp = dio->readChar();
        if (temp == '%'){
            break;
        }
        unClassifiesContent += temp;
    }

    //set the unclassified contect inside the knn object of the client 
    knnObj->unClassifiedContect = unClassifiesContent;

    //sending the client upload complete
    dio->write(uploadComplete);
}

void classifyingData(DefaultIO* dio ,Knn* knnObj){

    //check if there is a data to classify
    int size = knnObj->getDataVector().size();
    if (size = 0 || knnObj->unClassifiedContect.size() == 0){
        string dataEmpty = "please upload data";
        dio->write(dataEmpty);
        return;
    }

    //files are valid

    //loop that iterate thorugh all the vectors in unclassifedBIGstring
    //for each vector calculate the knn algo, and put the answers in knn.classifiedAnswers[i]
    //after each iteration each vector in datavector will be 0 in index 0.
    knnObj->classifiedAnswersShorten.clear();
    std::string line;
    std::istringstream iss(knnObj->unClassifiedContect);
    int dvSize;
    
    while (std::getline(iss, line, '\n')) {
       //clean the distances in dataVector from previous iterations
        dvSize = knnObj->getDataVector().size();
       for (int i=0; i<dvSize; i++){
        knnObj->dataVector[i][0] = "0";
       }  
       //set the userVector to calcute his result in knn 
       knnObj->setUserVector(line);
       string answer = knnObj->knnCalculate();

       //add the answer to the asnwers array inside the knn object
       knnObj->classifiedAnswersShorten.push_back(answer);
    }

    //send the client the classifying is completed
    string dataComplete = "classifying data complete";
    dio->write(dataComplete);
}

void returnResultsToPrint(DefaultIO* dio ,Knn* knnObj){

    //check if there is a data to show his results
    int size = knnObj->getDataVector().size();
    if (size = 0 || knnObj->unClassifiedContect.size() == 0){
        string dataEmpty = "please upload data";
        dio->write(dataEmpty);
        return;
    }
    else if(knnObj->classifiedAnswersShorten.size() == 0){
        string notClassified = "please classify the data";
        dio->write(notClassified);
        return;
    }

    //if reached here there are answer to show
    string answer;
    string finalA;
        for(int i=0; i< knnObj->classifiedAnswersShorten.size(); i++){
            stringstream out;
            out << i+1;
            answer = (out.str() + " " + knnObj->classifiedAnswersShorten[i] + "\n");
            finalA = finalA + answer;
            }
        //write the answers to the client
        dio->write(finalA);
}

void returnResultsToFile(DefaultIO* dio ,Knn* knnObj){

    //check if there is a data to show his results
    int size = knnObj->getDataVector().size();
    if (size = 0 || knnObj->unClassifiedContect.size() == 0){
        string indicator = "$";
        dio->write(indicator);
        string dataEmpty = "please upload data";
        dio->write(dataEmpty);
        return;
    }
    else if(knnObj->classifiedAnswersShorten.size() == 0){
        string indicator = "$";
        dio->write(indicator);
        string notClassified = "please classify the data";
        dio->write(notClassified);
        return;
    }

    //if reached here there are answer to show
    string indicatorCorrect = "&";
    dio->write(indicatorCorrect);
    string answer;
    string finalA;
        for(int i=0; i< knnObj->classifiedAnswersShorten.size(); i++){
            stringstream out;
            out << i+1;
            answer = (out.str() + " " + knnObj->classifiedAnswersShorten[i] + "\n");
            finalA = finalA + answer;
            }
        //write the answers to the client
        dio->write(finalA);
}




void ReleaseClient(SocketIO* dio ,Knn* knnObj){
    //close the client socket, the designated thread of the client will be closed automatically
    close(dio->clientID);
    return;
}

void handleClient(int client_sock) {
    //create a knn object for the specific client
    Knn knnObj(5," ","AUC");    

    //create a socketIO object to read & write from client
    SocketIO dio = SocketIO(client_sock);

        //chatting using TCP with the new client    
        while (1) {
            
            //read the option the user chose
            char temp = 0;
            string data;
            temp = dio.readChar();
            if (temp == '1'){
               uploadCSV(&dio, &knnObj);
            }
            else if (temp == '2'){
               changeAlgoSettings(&dio, &knnObj);
              
            }
            else if (temp == '3'){
               classifyingData(&dio, &knnObj);
            }
            else if (temp == '4'){
               returnResultsToPrint(&dio, &knnObj); 
            }
            else if (temp == '5'){
               returnResultsToFile(&dio, &knnObj); 
            }
            else {
                ReleaseClient(&dio, &knnObj);
               break;
            }
        }
    return;
}

int main(int argc, char **argv) {

    validateArguments(argc, argv);
    //setting the port of the server as the first argumet entered in command line.
    const int server_port = stoi (argv[1]);

    //creating a socket and check if the creation was successfull
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);


    //binding the server to listen to the port given
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }

    //enable at most 5 clients waiting to be accepted 
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }

    //creating struct for the clients which will be accepted in the future
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);

    while(1){
        //accepting a new client and attach him the a designated client sock
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);

        if (client_sock < 0) {
            perror("error accepting client");
            }
        //create new theread for client and sent it to func handle client
        std::thread t(handleClient, client_sock);
        t.detach();
        }
    }
