// TO ASK LECTURER:
// 1. Can we read the integers from the file into a CHARACTER ARRAY (Cstring), then put it in a linked list 
// 2. Can we make the digit field in the struct of data type INT
// 3. Can we use the linked list implementation of a STACK to solve the problem


#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#define MAX_DIGITS 50


struct Node{
    int data;
    Node *next;
};


struct Stack{
    Node *top;
};


// cheating, just to see what the stack looks like
void printList(Node *top){
    cout << "top -> ";
    Node *curr = top;
    while(curr!=NULL) {
        cout<<curr->data<<" -> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}


Stack *initStack(){
    Stack *s = (Stack *) malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}


void push(Stack *s, int data){
    Node *newNode = (Node*) malloc (sizeof(Node));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}


bool isEmpty(Stack *s){
    if(s->top == NULL)
        return true;
    else
        return false;
}


int pop(Stack *s){ 

    // case 0: if stack is empty
    if(isEmpty(s))
        return -1;

   Node *curr = s->top;
   s->top = curr->next;
   int n = curr->data;
   free(curr);
   return n;
}


int peek(Stack *s){
    // if empty
    if(isEmpty(s))
        return -1;

    return s->top->data;
}





// function accepts a single character array (max size 50 digits)
// and returns a stack with 1 digit per node with the least significant digit at the top of stack
Stack *cStringToStack(char num[]){

}


// function accepts 2 stacks
// and returns a new stack which holds the sum of the two stacks, 1 digit per node, with the least significant digit at the top of stack
Stack *addStacks(Stack *stackNum1, Stack *stackNum2){

}


int main(){

                                                            // open input file
    ifstream fin("input.txt");
    if(!fin){
        cout << "Error opening input file" << endl;
        exit(-1);
    }

                                                            // open output file
    ofstream fout("output.txt");
    if(!fout){
        cout << "Error opening output file" << endl;
        exit(-1);
    }

    char cStringNum1[MAX_DIGITS+1];                         // character array to store first number on a line
    char cStringNum2[MAX_DIGITS+1];                         // character array to store second number on a line
    
    fin >> cStringNum1:                                     // get first number from file
    while(//num1 is not -1){                                // while not end of file
        fin >> cStringNum2;                                     // get second number from file

        Stack *stackNum1 = ;                                    // put first number in stack 1
        Stack *stackNum2 = ;                                    // put second number in stack 2
        Stack *stackSum = ;                                     // put the sum of stack 1 and 2 here

                                                                // output (see assignment file to see what the output looks like)

        fin >> cStringNum1;                                     // get first number on the next line in the file
    }

    
                                                            // close files
    fin.close(); 
    fout.close();


    return 0;
}