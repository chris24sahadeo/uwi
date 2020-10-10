#include <iostream>
using namespace std;


#define NUM_ELEMENTS 7


void printArray(int A[], int n){
    for(int i = 0; i < n; i++){
        cout << A[i] << "\t";
    }
    cout << endl;
}


void insertInPlace(int A[], int n, int key){
    int j = n-1;
    while(j >= 0 && key < A[j]){
        A[j+1] = A[j];
        j--;
    }
    A[j+1] = key;
}


void insertionSort(int A[], int n){
    for(int i = 1; i < n; i++){
        cout << "PASS #" << i << ":\t";
        insertInPlace(A, i, A[i]);
        printArray(A, n);
    }
}


int main(){

    int A[NUM_ELEMENTS] = {57, 48, 79, 65, 15, 33, 52};

    cout << "INIT:    \t";
    printArray(A, NUM_ELEMENTS);

    insertionSort(A, NUM_ELEMENTS);

}
