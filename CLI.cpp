#include "CLI.h"

using namespace std;

// constructor - add to commands array member the command to the client
CLI::CLI(DefaultIO* dio) {
    this->commands.push_back(new UploadDataFile(dio));
    this->commands.push_back(new AlgoSetting(dio));
    this->commands.push_back(new ClassifyData(dio));
    this->commands.push_back(new DisplayResults(dio));
    this->commands.push_back(new DownloadResults(dio));
    this->commands.push_back(new ExitCommand((SocketIO*)dio));
}

// method to start the chat with the user
void CLI::start() {
    int userInput;
    string userStringInput;
    
    do {
        cout << "Welcome to the Knn Classifier Server. Please choose an option:" <<endl;
        
        int size = this->commands.size();

        // write every command to the user terminal
        for (int i = 0; i < size-1; ++i) {
            cout << (i +1);
            cout << "." + commands[i]->description << endl;
        }
            cout << (8);
            cout << "." + commands[5]->description << endl;

        // input the command option from the user
        getline(cin, userStringInput);

        //if the user didn't enter an int
        try{
        userInput = stoi(userStringInput);
        }
        //print invalid input to user
        catch (const std::exception& e){
            cout << "invalid input" << endl;
            continue;
        }
        
        //if the metric the user entered is not correct
        if(userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput != 5 && userInput!=8){
            cout << "invalid input" << endl;
            continue;
        }
        //if the user wants to exit
        if(userInput == 8){
            userInput=6;
        }

        //excecute the command the user wanted
        this->commands[userInput -1]->execute();

    } while (userInput != 8);
}
