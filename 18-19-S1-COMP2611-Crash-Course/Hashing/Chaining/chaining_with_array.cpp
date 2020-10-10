#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


#define N 15    // size of the whole array (both the hash and chain tables)
int n = 5;      // size of hash table [1..n]
#define EMPTY_NUM -1
#define EMPTY_NEXT -1
#define SETW_SPACING_SMALL 10

int hashTableLeft = 1;
int hashTableRight = n;
int chainTableLeft = n+1;
int chainTableRight = N;
int nextFreeLoc = chainTableLeft;


struct Node{
    int num, next;
};


// hash table in A[1..n]
void initHashTable(Node hash[]){
    for(int i = 1; i <= n; i++){                // loop through hash table and set all to empty
        hash[i].num = EMPTY_NUM;
        hash[i].next = EMPTY_NEXT;
    }
}


// chain table in A[n+1..N]
void initChainTable(Node chain[]){
for(int i = n+1; i <= N; i++){                  // loop through the chain table
        chain[i].num = EMPTY_NEXT;                  // set the num field to empty
        chain[i].next = i+1;                        // set the next field to point to the next free location (this is how we init the free list)
    }
    chain[N].next = EMPTY_NEXT;
}


// prints an array from left to right indices
// used to print both the hash and chain tables
void print(Node A[], int left, int right, string tableName){
    cout << tableName << endl;
    cout << setw(SETW_SPACING_SMALL) << "INDEX" << setw(SETW_SPACING_SMALL) << "NUM" << setw(SETW_SPACING_SMALL) << "NEXT" << endl;
    for(int i = left; i <= right; i++)
        cout << setw(SETW_SPACING_SMALL) << i << setw(SETW_SPACING_SMALL) << A[i].num << setw(SETW_SPACING_SMALL) << A[i].next << endl;
    cout << endl;
}


int hashFunction(int key, int n){
    return key%n + 1;
}


////////////////////////////////////////////////////////////////////////////////
////// SEARCHES THE TABLE FOR KEY, IF FOUND DO NOTHING, ELSE INSERT ////////////
////////////////////////////////////////////////////////////////////////////////
void searchAndInsert(Node A[], int key){

    cout << "Search And Insert: " << key << endl;

    int loc = hashFunction(key, hashTableRight);            // initial hash

    if(A[loc].num == EMPTY_NUM){                            // if location is empty
        cout << key << " hashed to table " << loc << endl;
        A[loc].num = key;                                       // put key in loc
        A[loc].next = EMPTY_NEXT;                               // set the chain to NULL (Empty chain)
    }

    else{                                                   // else, loc is not key -> we need to go down the chain until we either find key or reach the end (in which case we insert at the end)
        int prev = EMPTY_NEXT;
        int curr = loc;
        while(curr != EMPTY_NEXT && A[curr].num != key){    // while we have not reached the end of the chain and we have not found key
            prev = curr;                                        // keep checking
            curr = A[curr].next;
        }

        if(curr != EMPTY_NEXT){                             // if the key is already in that chain
            cout << key << " found in table " << curr << endl;
            return;                                             // we are done
        }

        else{                                               // else, add key to the end of the chain in the next available spot in the chain table
            cout << key << " hashed to chain table " << nextFreeLoc << endl;
            int putHere = nextFreeLoc;
            nextFreeLoc = A[nextFreeLoc].next;                  // set the nextFreeLoc to point to the nextFreeLoc in the chain table;
            A[putHere].num = key;                               // put key in the next free location
            A[putHere].next = EMPTY_NEXT;                       // set the next field to -1 becuase we are at the end of the chain
            A[prev].next = putHere;                             // link the previous node to the current node
        }
    }

    print(A, hashTableLeft, hashTableRight, "HASH TABLE");
    print(A, chainTableLeft, chainTableRight, "CHAIN TABLE");
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


int main(){

    Node A[N+1]; // +1 because we need to ignore location 0
    //int n = 5; // the size of the actual hash table is 5, so [1..n] is the hash table, [n+1..N] is the overflow (chain) table

    // int hashTableLeft = 1;
    // int hashTableRight = n;
    // int chainTableLeft = n+1;
    // int chainTableRight = N;

    // inits
    initHashTable(A);
    initChainTable(A);
    print(A, hashTableLeft, hashTableRight, "HASH TABLE");
    print(A, chainTableLeft, chainTableRight, "CHAIN TABLE");

    // search and insert
    searchAndInsert(A, 10);
    searchAndInsert(A, 10);
    searchAndInsert(A, 5);
    searchAndInsert(A, 15);


    return 0;
}
