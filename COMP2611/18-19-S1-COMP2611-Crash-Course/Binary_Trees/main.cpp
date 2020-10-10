#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "constants.h"
#include "NodeTypes.h"
#include "BinaryTree.h"
#include "BinarySearchTree.h"


int main(){

    BTNode *BST = NULL;                     // make empty BST

    BST = insert(BST, "H");                 // insert 8 and set BST root

    insert(BST, "C");                       // notice that we do not set the BST root anymore
    insert(BST, "J");                      // you may ask yourself...
    insert(BST, "A");                       // ...self,
    insert(BST, "N");                      // why are we not setting the BST root anymore?
    insert(BST, "F");                       // ANSWER:
    insert(BST, "M");                      // because we always insert at a leaf node!!!
    insert(BST, "D");
    insert(BST, "G");

    inOrderRecursive(BST);
    cout << endl;

    insert(BST, "E");

    inOrderRecursive(BST);
    cout << endl;

    // bool x = "10" > "1";
    // cout << x << endl;

                                            // deletions
    BST = deleteNode(BST, "C");
    inOrderRecursive(BST);
    cout << endl;

    



    return 0;
}
