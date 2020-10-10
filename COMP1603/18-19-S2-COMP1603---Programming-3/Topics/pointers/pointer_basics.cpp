#include <iostream>
using namespace std;

int main(){

    // VARIABLES ON THE STACK (1MB max by default)
    int num = 24; // a normal varible on the stack
    cout << num << endl;

    cout << &num << endl;  // & gets the address of a variable


    int *numPointer;            // use 1: use the * when making the pointer variable
    numPointer = &num;          // DON'T use the star when writing ADDRESSES and reading ADDRESSES in the pointer 

    cout << numPointer << endl;

    cout << &numPointer << endl;  

    int **numPointerPointer = &numPointer; // a pointer to a pointer
    
    cout << numPointerPointer << endl;

    cout << *numPointer << endl; // use 2: use the * on a pointer when we want to see the VALUE in the variable that the pointer is pointing to
    cout << *numPointerPointer << endl << endl;


    // VARIABLES ON THE HEAP (huge!!!)
    cout << sizeof(int) << endl; // getting the size of a variable

    int *numPointer2 = (int *) malloc(sizeof(int));


    return 0;
}