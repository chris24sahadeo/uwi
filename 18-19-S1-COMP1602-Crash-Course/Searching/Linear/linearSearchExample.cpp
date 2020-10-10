#include <iostream>
using namespace std;


#define SIZE 8


void printArray(int A[], int n){
    for(int i = 0; i < n; i++){
        cout << A[i] << "\t";
    }
    cout << endl;
}


int linearSearchUnsorted(int A[], int n){
    int i = 0;
    while(i < n && A[i] != key)
        i++;
    if(A[i] == key)
        return i;
    return -1;
}


int linearSearchSorted(int A[], int n, int key){
    int i = 0;
    while(i < n && A[i] < key)
        i++;
    if(A[i] == key)
        return i;
    return -1;
}


int main(){

    int A[SIZE] = {5, 10, 15, 20, 25, 30, 35, 40};
    int key = 40;

    cout << linearSearchSorted(A, SIZE, 10) << endl;
    cout << linearSearchSorted(A, SIZE, 40) << endl;
    cout << linearSearchSorted(A, SIZE, 36) << endl;

}
