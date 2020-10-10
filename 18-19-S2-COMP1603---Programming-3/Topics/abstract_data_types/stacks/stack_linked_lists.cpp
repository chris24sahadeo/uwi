// G4G: https://www.geeksforgeeks.org/stack-data-structure/#intro

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;


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


int pop(Stack *s){  // think about the 3 cases

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



int main(){
    
    Stack *s = initStack(); // makes an empty stack

    push(s, 10);
    push(s, 20);
    push(s, 30);
    cout << peek(s) << endl;
    printList(s->top);

    int n = pop(s);
    cout << n << endl;

    cout << pop(s) << endl;
    cout << pop(s) << endl;
    cout << pop(s) << endl;

    printList(s->top);

    
    return 0;
}