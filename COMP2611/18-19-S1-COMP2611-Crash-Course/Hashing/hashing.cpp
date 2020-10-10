#include <iostream>
#include <fstream>
using namespace std;


#define SIZE 12
#define EMPTY 0
#define DELETED -1


void initArray(int A[]){
    for(int i = 1; i <= SIZE; i++)
        A[i] = EMPTY;
}


void printArray(int A[]){
    for(int i = 1; i <= SIZE; i++)
        cout << A[i] << "\t";
    cout << endl;
    for(int i = 1; i <= SIZE; i++)
        cout << i << "\t";
    cout << endl;
}


// hash function
int H(int key){
    return key%SIZE + 1;
}


void searchAndInsert_v1(int A[], int key){
    // get initial hash location
    // while location is not empty and not key
        // keep hashing
    // if empty
        // then insert key into location
    // else
        // found so do nothing
}


void searchAndInsert_v2(int A[], int key){

}




int main(){

    int A[SIZE+1]; // hash table
    initArray(A);

    // getting data from text file
    ifstream fin("data.txt");
    int num;
    fin >> num;
    while(!fin.eof()){
        cout << num << "\t";
        fin >> num;
    }
    fin.close();




}
