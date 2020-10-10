#include <iostream>
using namespace std;


#define NUM_ELEMENTS 7


void printArray(int A[], int n){
    for(int i = 0; i < n; i++){
        cout << A[i] << "\t";
    }
    cout << endl;
}


int getSmallestLocation(int A[], int start, int n){
    int smallestLoc = start;
    for(int j = start+1; j < n; j++){
        if(A[j] < A[smallestLoc]){
            smallestLoc = j;
        }
    }
    return smallestLoc;
}


void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}


void selectionSort(int A[], int n){
    for(int i = 0; i < n-1; i++){
        cout << "PASS #" << i+1 << ":\t";
        swap(A, i, getSmallestLocation(A, i, n));
        printArray(A, n);
    }
}


int main(){

    int A[NUM_ELEMENTS] = {57, 48, 79, 65, 15, 33, 52};

    cout << "INIT:    \t";
    printArray(A, NUM_ELEMENTS);

    selectionSort(A, NUM_ELEMENTS);

}
