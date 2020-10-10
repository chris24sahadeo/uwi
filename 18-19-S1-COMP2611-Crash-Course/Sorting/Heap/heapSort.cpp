#include <iostream>
using namespace std;

#define SIZE 12
#include "../../Binary_Trees/heap.h"


void heapSort(int A[], int n){
    for(int i = n; i >= 2; i--){
        swap(A, 1, i);
        siftDown(A[1], A, i-1, 1);
    }
}


int main(){

    int A[SIZE+1] = {SIZE, 37, 25, 43, 65, 48, 84, 73, 18, 79, 56, 69, 32};

    levelOrderTraversal(A, SIZE);
    heapify(A, SIZE);
    levelOrderTraversal(A, SIZE);
    heapSort(A, SIZE);
    levelOrderTraversal(A, SIZE);


    return 0;
}
