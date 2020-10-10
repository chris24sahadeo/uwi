// G4G: https://www.geeksforgeeks.org/queue-data-structure/

#include <iostream>
#include <cstdlib>
using namespace std;


struct Node{
    int data;
    Node *next;
};


struct Queue{
    Node *head;
    Node *tail;
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


Queue *initQueue(){
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}


bool isEmpty(Queue *q){
    return q->head == NULL;
}


Node *createNode(int n){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = n;
    newNode->next = NULL;
    return newNode;
}


void enqueue(Queue *q, int n){

    Node *newNode = createNode(n);

    if(isEmpty(q)){
        q->head = q->tail = newNode;
    }
    else{
        q->tail->next = newNode;
        q->tail = newNode;
    }

}


int peek(Queue *q){
    if(!isEmpty)
        return -1;
    
    return q->head->data;
}


int dequeue(Queue *q){
    return -1;
}


int main(){

    // make an empty queue
    Queue *q = initQueue();

    enqueue(q, 5);
    enqueue(q, 10);
    enqueue(q, 15);
    enqueue(q, 20);

    printList(q->head);
    cout << peek(q);



    return 0;
}