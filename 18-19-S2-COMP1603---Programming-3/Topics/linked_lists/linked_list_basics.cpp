// G4G: https://www.geeksforgeeks.org/data-structures/linked-list/#singlyLinkedList

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;


// struct definition (blueprint)
struct Node{
    int data;
    Node *next;
};



int main(){

    // making an Empty List
    Node *top = NULL;


    // ADDING 10 TO THE HEAD OF THE LIST
    Node *newNode = (Node*) malloc(sizeof(Node));   // STEP 1: making a newNode with a pointer to the newNode
    newNode->data = 10;                             // STEP 2.a: put data in the node
    newNode->next=NULL;                             // STEP 2.b: make newNode->next point to NULL    
    newNode->next = top;                            // STEP 3: make newNode->next point to whatever top is pointing to    
    top = newNode;                                  // STEP 4: make top point to newNode


    // ADDING 20 TO THE HEAD OF THE LIST
    Node *newNode2 = (Node*) malloc(sizeof(Node));
    newNode2->data = 20;
    newNode2->next = NULL;
    newNode2->next = top;
    top = newNode2;

    
    // ADDING 30 TO THE HEAD OF THE LIST
    Node *newNode3 = (Node*) malloc(sizeof(Node));
    newNode3->data=30;
    newNode3->next=NULL;
    newNode3->next=top;
    top=newNode3;


    // PRINTING THE LIST TO THE SCREEN
    Node *curr = top;                               // start at the first node (head of list)
    while(curr!=NULL){                              // while we have not reached the end of the list
        cout<<curr->data<<'\t';                         // output data
        curr=curr->next;                                // advance to next node
    }

    
    return 0;
}