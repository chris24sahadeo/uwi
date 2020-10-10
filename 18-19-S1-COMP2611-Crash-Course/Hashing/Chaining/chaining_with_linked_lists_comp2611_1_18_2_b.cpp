#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


#define n 4
#define DATAFILE "data.txt"
#define MAX_KEYS 10
#define KEY_UPPER_LIMIT 10
#define KEY_LOWER_LIMIT 1


struct Node{
    int key, count;
    Node *next;
};


void makeDataset(){
    ofstream fout(DATAFILE);
    srand(time(0));
    for(int i = 1; i <= MAX_KEYS; i++){
        fout << rand()%(KEY_UPPER_LIMIT-KEY_LOWER_LIMIT+1) + KEY_LOWER_LIMIT << endl;
    }
    fout.close();
}


void initHashTable(Node *hashTable[]){
    for(int i = 1; i <= n; i++){
        hashTable[i] = NULL;
    }
}


Node *makeNode(int key){
    Node *newNode = new Node;
    newNode->key = key;
    newNode->count = 0;
    newNode->next = NULL;
    return newNode;
}


// prints as (value,count)
void printNode(Node *node){
    cout << " -> (" << node->key << "," << node->count << ")";
}


void printLinkedList(Node *top){
    Node *curr = top;
    while(curr != NULL){
        printNode(curr);
        curr = curr->next;
    }
    cout << " -> NULL" << endl;
}


void printHashTable(Node *hashTable[]){
    cout << "*** HASH TABLE ***" << endl;
    for(int i = 1; i <= n; i++){
        cout << i;
        printLinkedList(hashTable[i]);
    }
    cout << endl;
}


int H(int key){
    int loc = key%n+1;
    cout << "KEY:" << key << ",\tHASHED TO: " << key << " % " << n << " + 1\t= " << loc << endl;
    return loc;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
void searchAndInsert(Node *hashTable[], int key){

    int loc = H(key);                               // initial hash

    if(hashTable[loc] == NULL){                     // if the location is totally free
        hashTable[loc] = makeNode(key);                 // put key in that location
        return;
    }

    Node *curr = hashTable[loc];
    Node *parent = curr;
    while(curr != NULL && curr->key != key){        // else location is not free so search linked list for key
        parent = curr;
        curr=curr->next;
    }

    if(curr == NULL){                               // if key not found then insert key at end of linked list
        parent->next = makeNode(key);
    }

    else{                                           // else key was found
        curr->count++;                                  // so increment the count
        if(curr->count == 10){                          // if the count reaches 10
            curr->count = 0;                                // reset count to zero and move key to head of list
            if(parent == curr){                             // if there is only one item in the list then
                return;                                         // do nothing because key is already at the head
            }

            parent->next = curr->next;                  // else key is not at the head so delete key from wherever it is
            curr->next = hashTable[loc];                // and move it to the head
            hashTable[loc] = curr;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////



int main(){

    // makeDataset();

    Node *hashTable[n+1];   // ignore index zero
    initHashTable(hashTable);
    // printHashTable(hashTable);

    ifstream fin(DATAFILE);
    int key;
    fin >> key;
    while(!fin.eof()){
        // cout << key << endl;
        searchAndInsert(hashTable, key);
        fin >> key;
    }
    fin.close();

    printHashTable(hashTable);

    return 0;
}
