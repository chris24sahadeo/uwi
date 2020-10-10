// CHRISTOPHER SAHADEO
// 816000772
// LEVEL 2
// #include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


// struct Row{

// };


int main(){

    ifstream fin("input3.txt");
    ofstream fout("output.txt");

    int numRows;
    fin >> numRows;

    // cout << numRows << endl;

    char encrypted[10001];
    char decrypted[10001];
    fin >> encrypted;
    int numLetters = strlen(encrypted);
    // cout << numLetters;

    // cout << encrypted << endl;

    // Row rows[numRows+1];
    int firstRowIncrement, firstIncrement, lastRowIncrement, secondIncrement;
    firstIncrement = firstRowIncrement = lastRowIncrement = 2*(numRows-1);
    // int lastPos = -1;
    // int currPos = -1;
    int encryptedPosition = 0;
    int decryptedPosition;
    for(int rowNumber = 1; rowNumber <= numRows; rowNumber++){
        // encryptedPosition++;
        decryptedPosition = rowNumber-1;

        if(rowNumber == 1 || rowNumber == numRows){
            firstIncrement = secondIncrement = firstRowIncrement;
        }
        else{
            firstIncrement -= 2;
            secondIncrement = firstRowIncrement - firstIncrement;
        }

        int numAdded = 0;
        int increment;
        while(decryptedPosition < numLetters && encryptedPosition < numLetters){
            // cout << encryptedPosition << "\t" << decryptedPosition << endl;
            decrypted[decryptedPosition] = encrypted[encryptedPosition];
            
            if(numAdded%2 == 0){
                increment = firstIncrement;
            }
            else{
                increment = secondIncrement;
            }
            numAdded++;
            encryptedPosition++;
            decryptedPosition += increment;
        }

    }

    fout << decrypted << endl;

    fin.close();
    fout.close();

    return 0;
}