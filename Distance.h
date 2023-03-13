#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;


class Distance{

private:
    /****************************
    * Method Name:isSumInteger
    * Input: double d
    * Output: bool
    * Method Operation: the method checks if the givven value is int.
                      if the given value is int - returns true, otherwise - return false.
    ****************************/
    bool isSumInteger(double d);

    /****************************
    * Method Name:printDistance
    * Input: double d
    * Output: no Output
    * Method Operation: printing the given value to the screen - in specific format.
    ****************************/
    void printDistance(double d);
    
    /****************************
    * Method Name:stringIsValid
    * Input: string s
    * Output: True / False
    * Method Operation: the function return true if the string contain only digits, dot, or spaces.
    ****************************/
    bool stringIsValid(string s);
public:
    /****************************
    * Method Name:eqalizeTwoVectors
    * Input: vector<double>& vector1, vector<double>& vector2
    * Output: no Output
    * Method Operation: padding the short vector with zeros until both vectors has the same size.
    ****************************/
    void eqalizeTwoVectors(vector<double>& vector1, vector<double>& vector2);
    
    /****************************
    * Method Name:calculateDistance
    * Input: vector<double> vector1, vector<double> vector2, void (*distanceFunc)(vector<double>, vector<double>)
    * Output: no Output
    * Method Operation: this Method gets two vectors and calculates the distance between them, 
                      using the specific distance function given as a parameter.
    ****************************/
    void calculateDistance(vector<double> vector1, vector<double> vector2, void (*distanceFunc)(vector<double>, vector<double>));
    
    /****************************
    * Method Name:manhattenDistance
    * Input: vector<double> vector1, vector<double> vector2
    * Output: no Output
    * Method Operation: calculates the manhatten distance between two given vectors
    ****************************/
    double manhattenDistance(vector<double> vector1, vector<double> vector2);

    /****************************
    * Method Name:euclideanDistance
    * Input: vector<double> vector1, vector<double> vector2
    * Output: no Output
    * Method Operation: calculates the euclidean distance between two given vectors
    ****************************/
    double euclideanDistance(vector<double> vector1, vector<double> vector2);

    /****************************
    * Method Name:minkowskiDistance
    * Input: vector<double> vector1, vector<double> vector2
    * Output: no Output
    * Method Operation: calculates the minkowski distance between two given vectors,
                      prints the distance to the screen using the printDistance function.
    ****************************/
    double minkowskiDistance(vector<double> vector1, vector<double> vector2);

    /****************************
    * Method Name:chebyshevDistance
    * Input: vector<double> vector1, vector<double> vector2
    * Output: no Output
    * Method Operation: calculates the chebyshev distance between two given vectors
    ****************************/
    double chebyshevDistance(vector<double> vector1, vector<double> vector2);

    /****************************
    * Method Name:canberraDistance
    * Input: vector<double> vector1, vector<double> vector2
    * Output: no Output
    * Method Operation: calculates the canberra distance between two given vectors,
    ****************************/
    double canberraDistance(vector<double> vector1, vector<double> vector2);
    
    /****************************
    * Method Name:convertStringToStringVector
    * Input: string vectorString
    * Output: vector<string>
    * Method Operation: creates a vector from the given string.
                      the given string format contains spaces between the numbers.
    ****************************/
    vector<string> convertStringToStringVector(string vectorString);
    /****************************
    * Method Name:convertStringToDoubleVectorUser
    * Input: string vectorString
    * Output: vector<double>
    * Method Operation: creates a vector from the given string.
                      the given string format contains spaces between the numbers.
    ****************************/
    vector<double> convertStringToDoubleVectorUser(string vectorString);
};
