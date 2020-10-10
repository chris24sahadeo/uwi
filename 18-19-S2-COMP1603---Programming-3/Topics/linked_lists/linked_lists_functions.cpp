// G4G: https://www.geeksforgeeks.org/data-structures/linked-list/#singlyLinkedList

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;


// Struct Definition
struct Node{
    int data;
    Node *next;
};


// QUESTIONS TO ASK
    // Empty
    // first
    // middle||last 
    // Does not exist


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ FUNCTIONS
// printList
    // accepts the top pointer to the head of the list 
    // traverses the list and prints the data in the nodes 
void printList(Node *top){
    cout << "top -> ";
    Node *curr = top;
    while(curr!=NULL) {
        cout<<curr->data<<" -> ";
        curr = curr->next;
    }
    cout<<"NULL"<<endl;
}

// makeNode
    // accepts data
    // makes a new Node struct 
    // stores data in the struct 
    // sets next field to NULL 
    // returns the address (pointer to) the newNode
Node *createNode(int data){
    Node *newNode=(Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


// insertAtHead (4 step process)
    // accept some data (int, string, etc) and top
    // make newNode 
    // STEP 1: making a newNode with a pointer to the newNode
    // STEP 2.a: put data in the node
    // STEP 2.b: make newNode->next point to NULL    
    // STEP 3: make newNode->next point to whatever top is pointing to    
    // STEP 4: make top point to newNode
    // IMPORTANT!!! -> return top pointer (BECAUSE TOP ALWAYS CHANGES!!!)
Node *insertAtHead(int data, Node *top){
    Node *newNode = createNode(data);
    newNode->next = top;
    top = newNode;
    return top;

}

// insertAtTail (6 step process)
    // accepts data and puts it in a newNode
    // CASE 1: List is intially empty  -> insertAtHead
    // CASE 2: List is not empty       -> traverse until the end and insert at the end
    // IMPORTANT!!! -> return top pointer (BECAUSE TOP ALWAYS CHANGES!!!)


// insertInOrder


// search


// deleteKey
    // accepts key
    // CASE 1: At head
    // CASE 2: Not at head -> search and keep prev
        // if not present
Node *deleteKey(int key, Node *top){

    Node *curr = top, *prev = NULL; // initializing, curr always points to top, and prev always chases after curr

    // search for key
    // this loop stops when either:
        // case 0: key not found or
        // case 1/2: key is found
    while(curr != NULL && curr->data != key){
        prev = curr;            // previous chases curr
        curr = curr->next;      // curr advances to the next node
    }

    // case 0: key not found => curr == NULL check
    if(curr == NULL)
        return top;

    // case 1: key is in the first node => prev == NULL check
    if(prev == NULL)
        top = curr->next; // makes the list "skip" the key node
    
    // case 2: key is not the first node
    else
        prev->next = curr->next;
    
    free(curr); // actually deleting the box that was made using malloc to store the key
    return top; // always return top

}


// deleteNth


// length
    // traverse the list with curr pointer 
    // and keep a count 
    // return count

int length(Node *top){
    Node *curr = top;
    int count = 0;
    while(curr!=NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

// getNth
    // returns address of nth node


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int main(){

    // make empty linked list
    Node *top = NULL;
    printList(top);

    // add 10 to head (top)
    top = insertAtHead(10, top); // for linked lists, when adding to head, ALWAYS REASSIGN THE RETURNED VALUE TO TOP
    printList(top);

    // add 15 to head (top)
    top = insertAtHead(15, top); // for linked lists, when adding to head, ALWAYS REASSIGN THE RETURNED VALUE TO TOP
    printList(top);
    
    // add 20 to head (top)
    top = insertAtHead(20, top); // for linked lists, when adding to head, ALWAYS REASSIGN THE RETURNED VALUE TO TOP
    printList(top);

    // list length
    int n = length(top);
    cout<<"Length of list : "<<n<<endl;

    // delete 15, (case 2)
    top = deleteKey(15, top);
    printList(top);

    // delete 20, (case 1)
    top = deleteKey(20, top);
    printList(top);

    // delete something that doesn't exist
    top = deleteKey(30, top);
    printList(top);

    // delete 10, (case 1)
    top = deleteKey(10, top);
    printList(top);

    

    return 0;
}