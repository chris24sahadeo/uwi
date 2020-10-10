#include <iostream>
#include <fstream>
using namespace std;

#include "constants.h"
#include "partition.h"


void printArray(int A[], int n){
    for(int i = 1; i <= n; i++){
        cout << A[i] << "\t";
    }
    cout << endl;
    for(int i = 1; i <= n; i++){
        cout << i << "\t";
    }
    cout << "\n\n";
}


void quickSort_partition_v1(int A[], int left, int right){
    if(left >= right) return;                               // BASE CASE: 0 or 1 element to sort
    int divisionPoint = partition_v1(A, left, right);       // ELSE: partition and find division point
    quickSort_partition_v1(A, left, divisionPoint-1);       // Recur to the left of division point
    quickSort_partition_v1(A, divisionPoint+1, right);      // Recur to the right of division point
}


void quickSort_partition_v2(int A[], int left, int right){
    if(left >= right) return;                               // BASE CASE: 0 or 1 element to sort
    int divisionPoint = partition_v2(A, left, right);       // ELSE: partition and find division point
    quickSort_partition_v2(A, left, divisionPoint-1);       // Recur to the left of division point
    quickSort_partition_v2(A, divisionPoint, right);        // Recur to the right of division point
}


int main(){

    int A[] = {0, 53, 12, 98, 63, 18, 32, 80, 46, 72, 21};
    int n = sizeof(A)/sizeof(int)-1;

    printArray(A, n);
    quickSort_partition_v1(A, 1, n);
    printArray(A, n);


    return 0;
}
