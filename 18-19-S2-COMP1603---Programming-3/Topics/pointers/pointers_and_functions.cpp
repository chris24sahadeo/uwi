#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;


void doSomething1(int num){
    num = num + 10;
}

int doSomething2(int num){
    num = num + 10;
    return num;
}

void doSomething3(int A[], int n){
    for(int i = 0; i < n; i++)
        A[i] = A[i] + 10;
}

void doSomething4(int *num){
    *num = *num + 10;
}

void printArray(int A[], int n){
     for(int i = 0; i < n; i++)
        cout << A[i] << '\t';
    cout << endl;
}

int main(){

    int num = 30;
    cout << num << endl;
    doSomething1(num);
    cout << num << endl;  // void functions cannot change the value of variables

    doSomething2(num);
    cout << num << endl; // still does not change, because we didnt store the returned value back into num

    num = doSomething2(num);
    cout << num << endl; // this will change, because we stored the returned value back into num


    
    // functions WILL CHANGE THE VALUE STORED IN THE VARIABLE THE POINTER POINTS TO

    // with arrays: functions WILL CHANGE THE VALUE STORED IN THE VARIABLE THE POINTER POINTS TO
    // because: 'A' is a pointer to the first location in the array
    int A[10] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
    printArray(A, 10);
    doSomething3(A, 10);
    printArray(A, 10);

    // with pointers passed to functions: functions WILL CHANGE THE VALUE STORED IN THE VARIABLE THE POINTER POINTS TO
    // EVEN IF IT IS A VOID FUNCTION!!!
    int *numPointer = (int *) malloc(sizeof(int));
    *numPointer = 30;
    cout << *numPointer << endl;
    doSomething4(numPointer);
    cout << *numPointer << endl;



    return 0;
}