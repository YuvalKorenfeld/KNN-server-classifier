#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cmath>
#include <fstream>
#include "Distance.h"
#include <string.h>
#include <map>
using namespace std;

class Knn {
  

  bool notValidInput;
  
  //the vector the user entered
  vector<double> userVector;


  //Distance class object to calculate different distances
  Distance d;


  //the path to the file to read from
  string pathToDataFile;

  /****************************
  * Method Name:fileReading
  * Input: no input
  * Output: no output
  * Method Operation: reading from the file "pathToDataFile" - that is a knn member.
                    each row is an vector. all the data from the file is stored in dataVector in this way:
                    (first parameter: distance from user vector(at the begining sets to 0), second parameter: the name of the vector value,
                    rest of the parameters:the vector numbers data).
  ****************************/
  void fileReading();

  /****************************
  * Method Name:bubbleSortData
  * Input: no input
  * Output: no output
  * Method Operation: the data vector is a vector contains many vectors fron type string. 
                    we will sort the data vector (i.e all of his vectors) by their first value- the distance from the user vector.
                    importent note: the value stored as a string so for comparing we using "stod" function.
                    we will get increasing order.
  ****************************/
  void bubbleSortData();

  /****************************
  * Method Name:distanceUpdater
  * Input: nothing
  * Output: nothing
  * Method Operation: the method updates the distances for the string vector accordingly to the distance function- from the user vector.
  ****************************/
  void distanceUpdater();

  /****************************
  * Method Name:swapVectors
  * Input: int x, int y
  * Output: no output
  * Method Operation: the method will get two indexes from data vector and will switch the two vectors -
                    as part of the bubblesort algorithm.
  ****************************/
  void swapVectors(int x, int y);

  /****************************
  * Method Name:printToScreen
  * Input: string
  * Output: nothing
  * Method Operation: the method recieves the result vector name and prints it to the screen.
  ****************************/ 
  void printToScreen(string maxString);

 public:

  
  //vector which holds all the vectors from the file
  vector< vector<string> > dataVector;

  vector <string> classifiedAnswersShorten;

  string unClassifiedContect;

  //the name of the distance function that used to culculade the distance
  string distanceFuncName;

   //member to hold the number of closest neighbors from the user
  int k;
  /****************************
  * Method Name:Knn - constuctor
  * Input: int k, string pathToDataFile, string distanceFuncName
  * Output: no output
  * Method Operation: constuctor for the knn object.
  ****************************/
  Knn(int k, string pathToDataFile, string distanceFuncName);
  /****************************
  * Method Name:knnCalculate
  * Input: nothing
  * Output: string
  * Method Operation: the method calls functions to read from the file, update the distances based on the distance func
                    ,and sort the data. then uses a map to store for each key (which is the name of the vector) how many vectors
                    are there of its type withing the k closest values. 
  ****************************/
  string knnCalculate();
  
  /****************************
  * Method Name:setDistanceFunction
  * Input: string
  * Output: nothing
  * Method Operation: the method sets the member distanceFuncName to be the parameter given.
  ****************************/
  void setDistanceFunction(string distanceFuncName);
  /****************************
  * Method Name:getDataVector
  * Input: nothing
  * Output: vector< vector<string> > 
  * Method Operation: the method return the vector which contains vector strings
                    (each vector in the data vector is a row vector from the file + the distance from user vector in the beginning).
  ****************************/
  vector< vector<string> > getDataVector();
  /****************************
  * Method Name:setUserVector
  * Input: string
  * Output: nothing
  * Method Operation: the method sets the member userVector to be the parameter given.
 ****************************/
  void setUserVector(string userVector);
  /****************************
  * Method Name:clearDataVector
  * Input: nothing
  * Output: nothing
  * Method Operation: the method clears the dataVector which contains all the vectors from the file.
  ****************************/
  void clearDataVector();

/****************************
* Method Name:setPathToDataFile
* Input: string pathToDataFile
* Output: nothing
* Method Operation: the method assigm the member pathToDataFile the parameter given
 ****************************/
  void setPathToDataFile(string pathToDataFile);
  
/****************************
* Method Name:setK
* Input: int k
* Output: nothing
* Method Operation: setter for the k value in the knn obj
 ****************************/
  void setK(int k);

  void setDataVector(vector< vector<string> >  dataVector);


};

