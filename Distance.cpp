#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <cmath>
#include "Distance.h"
using namespace std;

/****************************
* Method Name:isSumInteger
* Input: double d
* Output: bool
* Method Operation: the method checks if the givven value is int.
                      if the given value is int - returns true, otherwise - return false.
 ****************************/
bool Distance::isSumInteger(double d){
    double intpart;
    if(modf(d, &intpart) == 0.0){
        return true;
    }
    return false;
}

/****************************
* Method Name:printDistance
* Input: double d
* Output: no Output
* Method Operation: printing the given value to the screen - in specific format.
 ****************************/
void Distance::printDistance(double d) {
    if(isSumInteger(d)) {
    cout << d << ".0" << endl;
  }
  else {
    cout << d << endl;
    }  
}

/****************************
* Method Name:calculateDistance
* Input: vector<double> vector1, vector<double> vector2, void (*distanceFunc)(vector<double>, vector<double>)
* Output: no Output
* Method Operation: this Method gets two vectors and calculates the distance between them, 
                      using the specific distance function given as a parameter.
 ****************************/
void calculateDistance(vector<double> vector1, vector<double> vector2, void (*distanceFunc)(vector<double>, vector<double>)){
    return distanceFunc(vector1, vector2);
}


/****************************
* Method Name:euclideanDistance
* Input: vector<double> vector1, vector<double> vector2
* Output: no Output
* Method Operation: calculates the euclidean distance between two given vectors
 ****************************/
double Distance::euclideanDistance(vector<double> vector1, vector<double> vector2) {
    vector<double> vector3;
    for (int i = 0; i < vector1.size(); i++) {
        vector3.push_back(vector1[i] - vector2[i]);
    }

    double distance = 0;
    for (int i = 0; i < vector1.size(); i++) {
        distance = distance + pow(vector3[i], 2);
    }

    distance = sqrt(distance);
    return distance;
}

/****************************
* Method Name:manhattenDistance
* Input: vector<double> vector1, vector<double> vector2
* Output: no Output
* Method Operation: calculates the manhatten distance between two given vectors
 ****************************/
double Distance::manhattenDistance(vector<double> vector1, vector<double> vector2) {
  double sum = 0;
  for (int i=0; i < vector1.size(); i++) {
    sum += (abs(vector1[i] - vector2[i]));
  }
  return sum;
}


/****************************
* Method Name:chebyshevDistance
* Input: vector<double> vector1, vector<double> vector2
* Output: no Output
* Method Operation: calculates the chebyshev distance between two given vectors
 ****************************/
double Distance::chebyshevDistance(vector<double> vector1, vector<double> vector2) {
    vector<double> vector3;
    for (int i = 0; i < vector1.size(); i++) {
        vector3.push_back(abs(vector1[i] - vector2[i]));
    }
    double max = vector3[0];
    for (int i = 0; i < vector1.size(); i++) {
        if (vector3[i] > max) {
            max = vector3[i];
        }
    }
    return max;
}

/****************************
* Method Name:canberraDistance
* Input: vector<double> vector1, vector<double> vector2
* Output: no Output
* Method Operation: calculates the canberra distance between two given vectors,
 ****************************/
double Distance::canberraDistance(vector<double> vector1, vector<double> vector2) {
  double sum = 0;
  for (int i=0; i < vector1.size(); i++) {
    double numerator = (abs(vector1[i] - vector2[i]));
    if (vector1[i] == 0 && vector2[i] == 0) {
      continue;
    }
    double denominator = abs(vector1[i]) + abs(vector2[i]);
    sum += (numerator / denominator);
  }
  return sum;
}

/****************************
* Method Name:minkowskiDistance
* Input: vector<double> vector1, vector<double> vector2
* Output: no Output
* Method Operation: calculates the minkowski distance between two given vectors,
                      prints the distance to the screen using the printDistance function.
 ****************************/
double Distance::minkowskiDistance(vector<double> vector1, vector<double> vector2) {
    double sum = 0;
    double p = 2;
    for (int i = 0; i < vector1.size(); i++) {
        sum = sum + pow(abs(vector1[i] - vector2[i]), p);
    }
    sum = pow(sum, (1.0 / p));
    return sum;
}

/****************************
* Method Name:convertStringToStringVector
* Input: string vectorString
* Output: vector<string>
* Method Operation: creates a vector from the given string.
                      the given string format contains spaces between the numbers.
 ****************************/
vector<string> Distance::convertStringToStringVector(string vectorString){
    vector<string> answer;
    istringstream stream(vectorString);
    string token;
    while (getline (stream, token, ',')) {  
        answer.push_back(token);
    }
    return answer;
}

/****************************
* Method Name:convertStringToDoubleVectorUser
* Input: string vectorString
* Output: vector<double>
* Method Operation: creates a vector from the given string.
                      the given string format contains spaces between the numbers.
 ****************************/
vector<double> Distance::convertStringToDoubleVectorUser(string vectorString){
    vector<double> v1;
    istringstream stream(vectorString);
    string token;
    while (getline (stream, token, ',')) {  
        try{
            v1.push_back(stod(token));
        }
        catch(const std::exception& e)
        {   
            
            //cout<<"your vector is not valid"<<endl;
            //exit(1);
            vector<double> vEmpty;
            return vEmpty;
        }
        
    }
    return v1;
}

/****************************
* Method Name:eqalizeTwoVectors
* Input: vector<double>& vector1, vector<double>& vector2
* Output: no Output
* Method Operation: padding the short vector with zeros until both vectors has the same size.
 ****************************/
void Distance::eqalizeTwoVectors(vector<double>& vector1, vector<double>& vector2){
    int delta=vector1.size()-vector2.size();
    if (vector1.size()>vector2.size()){
        for(int i=0;i<delta;i++){
            vector2.push_back(0);
        }
        return;
    }
    delta=vector2.size()-vector1.size();
        for(int i=0;i<delta;i++){
            vector1.push_back(0);
        }
        return;
}

/****************************
* Method Name:stringIsValid
* Input: string s
* Output: True / False
* Method Operation: the function return true if the string contain only digits, dot, or spaces.
 ****************************/
bool Distance::stringIsValid(string s){
    if (s.empty()){
        return false;
    }

  return s.find_first_not_of("0123456789.- ") == string::npos;
}


