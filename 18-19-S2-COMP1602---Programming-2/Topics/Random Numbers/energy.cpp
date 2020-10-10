#include <iostream>
#include <cstdlib>
using namespace std;


#define NUMLETTERS 5


int collect(){

    srand(time(0)); // seeds the random number generator
    
    // make array to store counts of each letter
    // letterCount[0] stores the count for E (we need 2 E's)
    // letterCount[1] stores the count for N
    // letterCount[2] stores the count for R
    // letterCount[3] stores the count for G
    // letterCount[4] stores the count for Y
    int letterCount[NUMLETTERS] = {0}; 

    bool allFound = false; // boolean variable to check if all letters have been found 
    while(!allFound){

        int letter = rand()%100 + 1; // generate a random number between 1 and 100

        if(letter <= 23) letterCount[1]++;                  // check for letter N
        else if(letter <= (23+26)) letterCount[2]++;        // check for letter R
        else if(letter <= (23+26+16)) letterCount[3]++;     // check for letter G
        else if(letter <= (23+26+16+8)) letterCount[4]++;   // check for letter Y
        else letterCount[0]++;                              // check for E, remember we need 2 E's

        allFound = letterCount[0] > 1 && letterCount[1] > 0 && letterCount[2] > 0 && letterCount[3] > 0 && letterCount[4] > 0;
    }

    // sum all the counts
    int sumCounts = 0;
    for(int i = 0; i < NUMLETTERS; i++){
        sumCounts += letterCount[i];
    }

    return sumCounts;

}


int main(){

    // 20 simualtions
    int sum = 0;
    for(int i = 0; i < 20; i++){
        sum += collect();
    }
    cout <<  "Average = " << sum/20.0 << endl;

    return 0;

}