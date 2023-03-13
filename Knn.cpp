# include "Knn.h"
# include <iostream>
#include <string.h>
#include <map>
using namespace std;
/****************************
* Method Name:Knn - constuctor
* Input: int k, string pathToDataFile, string distanceFuncName
* Output: no output
* Method Operation: constuctor for the knn object.
 ****************************/
Knn:: Knn(int k, string pathToDataFile, string distanceFuncName){
  this->k = k;
  this->distanceFuncName= distanceFuncName;
  this->pathToDataFile = pathToDataFile;
  //this bool value represent that the input is not valid - in several different cases (false- input is valid , true - input not valid)
  this->notValidInput= false;
}
/****************************
* Method Name:fileReading
* Input: no input
* Output: no output
* Method Operation: reading from the file "pathToDataFile" - that is a knn member.
                    each row is an vector. all the data from the file is stored in dataVector in this way:
                    (first parameter: distance from user vector(at the begining sets to 0), second parameter: the name of the vector value,
                    rest of the parameters:the vector numbers data).
 ****************************/
void Knn:: fileReading() { 

string myText;
ifstream MyReadFile(pathToDataFile);
int rowCount=0;
//read each row (vector) from the file
while (getline (MyReadFile, myText)) { 
rowCount++;
istringstream streamFirst(myText);
vector <string> temparary;
vector <string> result;
//setting the distance to 0 as string from the user vector as default

    result.push_back("0");
    temparary = d.convertStringToStringVector(myText);
    result.push_back(temparary[temparary.size() -1]);
    temparary.pop_back();
    int size = temparary.size();
    
    for (int i=0; i<size; i++) {
        result.push_back(temparary[i]);
    
    }

    //insert the vector from the file in this order: distance, name, value1, value2,...
    dataVector.push_back(result);
}

//closing the file
MyReadFile.close();
if (k <= 0){
    //cout << "you entered k=0 - please run the program with bigger k parameter"<< endl;
    //exit(1);
    this->notValidInput = true;
}
else if (rowCount == 0){
    //cout <<"File not found- Please check you path to the file" << endl;
    //exit(1);
    this->notValidInput = true;
}
else if(rowCount < k){
    //cout<<"you entered k number which is bigger than the number of all rows in the file -run the program with smaller k parameter"<<endl;
    //exit(1);
    this->notValidInput = true;
}
}
/****************************
* Method Name:bubbleSortData
* Input: no input
* Output: no output
* Method Operation: the data vector is a vector contains many vectors fron type string. 
                    we will sort the data vector (i.e all of his vectors) by their first value- the distance from the user vector.
                    importent note: the value stored as a string so for comparing we using "stod" function.
                    we will get increasing order.
 ****************************/
void Knn:: bubbleSortData(){
    int i, j;
    int size=this->dataVector.size();
    for (i = 0; i < size-1 ; i++){
        for (j = 0; j < size-1-i ; j++){
            double left=stod(dataVector[j][0]);
            double right=stod(dataVector[j+1][0]);
            if (left > right){
                swapVectors(j, j+1); //swap vectors
            }
        }
    }

}
/****************************
* Method Name:swapVectors
* Input: int x, int y
* Output: no output
* Method Operation: the method will get two indexes from data vector and will switch the two vectors -
                    as part of the bubblesort algorithm.
 ****************************/
void Knn::swapVectors(int x, int y){
    vector<string> temporary = this->dataVector[x];
    dataVector[x] = dataVector[y];
    dataVector[y] = temporary;
}


/****************************
* Method Name:distanceUpdater
* Input: nothing
* Output: nothing
* Method Operation: the method updates the distances for the string vector accordingly to the distance function- from the user vector.
 ****************************/
void Knn::distanceUpdater(){
if(this->k > dataVector.size()){
    this->k = dataVector.size();
}
double newDistance;

//go throgh each vector in the data vector - each vector from the file
for(int i=0; i<dataVector.size(); i++){
    vector<string> temperaryVector = dataVector[i];
    vector<double> valuesVector;

    //put its values in a new vector which will hold only the values 
    for(int j=2; j < temperaryVector.size(); j++){
        try
        {
            valuesVector.push_back(stod(temperaryVector[j]));
        }
        catch(const std::exception& e) 
        {
            //cout<<"one of the vectors in the file is not valid"<<endl;
            //exit(1);
            this->notValidInput = true;
        }
    }

    d.eqalizeTwoVectors(userVector, valuesVector);


    if (this->distanceFuncName == "AUC"){
        newDistance= d.euclideanDistance(userVector, valuesVector);
    }
    else if (this->distanceFuncName == "MAN"){
        newDistance= d.manhattenDistance(userVector, valuesVector);
    }
    else if (this->distanceFuncName == "CHB"){
        newDistance= d.chebyshevDistance(userVector, valuesVector);
    }
    else if (this->distanceFuncName == "CAN"){
        newDistance= d.canberraDistance(userVector, valuesVector);
    }
    else if (this->distanceFuncName == "MIN"){
        newDistance= d.minkowskiDistance(userVector, valuesVector);
    }
    else{
        //cout << "The distance metric you entered does not exist- run the program with correct distance metric" << endl;
        //exit(1);
        this->notValidInput = true;
    }

    //set the first index for each original vector in data vector to be the new distance calculated
    dataVector[i][0] = to_string(newDistance); 
    }
}

/****************************
* Method Name:setDistanceFunction
* Input: string
* Output: nothing
* Method Operation: the method sets the member distanceFuncName to be the parameter given.
 ****************************/
void Knn:: setDistanceFunction(string distanceFuncName){
    this->distanceFuncName = distanceFuncName;

}

/****************************
* Method Name:getDataVector
* Input: nothing
* Output: vector< vector<string> > 
* Method Operation: the method return the vector which contains vector strings
                    (each vector in the data vector is a row vector from the file + the distance from user vector in the beginning).
 ****************************/
vector< vector<string> > Knn::getDataVector(){
    return this->dataVector;
}

/****************************
* Method Name:setUserVector
* Input: string
* Output: nothing
* Method Operation: the method sets the member userVector to be the parameter given.
 ****************************/
void Knn::setUserVector(string userVector){  
    this->userVector = d.convertStringToDoubleVectorUser(userVector);
    if(this->userVector.empty()){
        this->notValidInput = true;
    }
}

/****************************
* Method Name:printToScreen
* Input: string
* Output: nothing
* Method Operation: the method recieves the result vector name and prints it to the screen.
 ****************************/
void Knn::printToScreen(string maxString){
    cout << maxString << endl;
}

/****************************
* Method Name:knnCalculate
* Input: nothing
* Output: nothing
* Method Operation: the method calls functions to read from the file, update the distances based on the distance func
                    ,and sort the data. then uses a map to store for each key (which is the name of the vector) how many vectors
                    are there of its type withing the k closest values. 
 ****************************/
string Knn::knnCalculate(){

    //update the distance according to the distance function
    this->distanceUpdater();
    /*if(notValidInput){
        return "invalid input"; 
    }*/
    
    
    //sort the vectors based on the distance
    this->bubbleSortData();
    

    //create a map to store for each key(which is the name of the vector) how many vectors
    //are there of its type withing the k closest values
    map<string, int> freqForNames;
    for(int i=0; i<this->k; i++){
    freqForNames[dataVector[i][1]] ++;
  }

    //find out the maximum value element in the map
    int max = 0;
    int current = 0;
    string maxString;
    map<string, int>::iterator it;
    for (it = freqForNames.begin(); it != freqForNames.end(); it++){
    current = it->second; 
    if (current >max){
    max = current;
    maxString = it->first;
        }  
    }
    //print to screen the result name
    //printToScreen(maxString); 
    return maxString;
}

/****************************
* Method Name:clearDataVector
* Input: nothing
* Output: nothing
* Method Operation: the method clears the dataVector which contains all the vectors from the file.
 ****************************/
void Knn::clearDataVector(){
    int size = dataVector.size();
    for(int i=0; i<size; i++){
        dataVector.pop_back();
    }
}

/****************************
* Method Name:setPathToDataFile
* Input: string pathToDataFile
* Output: nothing
* Method Operation: the method assigm the member pathToDataFile the parameter given
 ****************************/
void Knn::setPathToDataFile(string pathToDataFile){
    this->pathToDataFile = pathToDataFile;
}

/****************************
* Method Name:setK
* Input: int k
* Output: nothing
* Method Operation: setter for the k value in the knn obj
 ****************************/
void Knn::setK(int k){
    this->k = k;
}


void Knn::setDataVector(vector< vector<string> >  dataVector){
    this->dataVector = dataVector;
}




