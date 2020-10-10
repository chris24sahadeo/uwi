#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// constants
#define MAX_NAME_LENGTH 20
#define FILENAME "input.txt"


// all data structure functions
#include "cstring_functions.h"
#include "LL.h"         // linked list functions
#include "BST.h"        // bst functions



int main(){

    // clear screen
    system("cls");


    // making the data Structures
    struct NameNode *namesOnALine = NULL;                       // pointer to linked list of names on a given line
    struct TeamNode *allTeamsLinkedList = NULL;                 // pointer to linked list of all teams


    // testing the file handling
    FILE *fin = fopen(FILENAME, "rb");
    if(fin == NULL){
        printf("Error opening file...\n\n");
        exit(1);
    }


    // gets a word from the file
    char word[MAX_NAME_LENGTH+1];
    int check = 0;


    // while we havent reached the end of the file
    while(check != 2){

        namesOnALine = NULL;                                        // clear the Linked list of names on a line
        check = getWord(word, &fin);                                // get the first name on a line

        // while we havent reached the end of a line
        while(check != 1 && check != 2){
            namesOnALine = insertAtHead(namesOnALine, word);        // add to the LL of names on a line
            check = getWord(word, &fin);
        }

        // add the LL of Names to the LL of Team BSTs
        allTeamsLinkedList = addToLinkedListOfTeams(allTeamsLinkedList, namesOnALine);

    }


    // close file
    fclose(fin);


    // PRETTY MAJOR ERROR
    // ERROR... THE FIRST TEAM IS ALWAYS EMPTY...DONT KNOW WHY
    allTeamsLinkedList = allTeamsLinkedList->next;


    // making the BST of team BSTs
    struct BSTTeamNode *allTeams = makeBSTOfTeams(allTeamsLinkedList);

    // final desired output
    printAllTeamsInAlphabeticalOrder(allTeams, 1);


    return 0;
}
