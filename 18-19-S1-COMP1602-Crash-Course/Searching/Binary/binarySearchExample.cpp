#include <iostream>
using namespace std;


#define SIZE 8


void printArray(int A[], int n){
    for(int i = 0; i < n; i++){
        cout << A[i] << "\t";
    }
    cout << endl;
}


int binarySearch(int A[], int n, int key){
    int f = 0;
    int l = n-1;
    while(f <= l){
        int m = (f+l)/2;
        if(key < A[m])
            l = m-1;
        else if(key == A[m])
            return m;
        else
            f = m+1;
    }
    return -1;
}


int main(){

    int A[SIZE] = {5, 10, 15, 20, 25, 30, 35, 40};
    int key = 40;

    cout << binarySearch(A, SIZE, 10) << endl;
    cout << binarySearch(A, SIZE, 40) << endl;
    cout << binarySearch(A, SIZE, 36) << endl;

}
