#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// constants
#define MAX_CHAR_PER_WORD 16
#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"
#define FILE_SENTINEL "END"
#define INF 9999


// data structure .h includes
#include "cstring_functions.h"
#include "BST.h"
#include "queue.h"
#include "heap.h"
#include "Graph.h"


// main
int main(){

    // fine handling
    FILE *fin = fopen(INPUT_FILENAME, "r");
    if(fin == NULL){
        printf("Could not open %s\n\n", INPUT_FILENAME);
        exit(1);
    }

    FILE *fout = fopen(OUTPUT_FILENAME, "w");
    if(fout == NULL){
        printf("Could not make %s\n\n", OUTPUT_FILENAME);
        exit(2);
    }

    // reading file and making the BST
    struct BSTNode *BSTOfNodeNames = makeBSTOfNodeNames(&fin);

    // makes empty Graph and performs inorder traveral of BST and populates adj list with addresses of names from BST
    struct Graph *graphOfNames = initGraph(getNumBSTNodes(BSTOfNodeNames), BSTOfNodeNames);

    // reads the file and adds edges to the graph
    addEdgesFromFile(&fin, graphOfNames);

    // Part a - prints graphs with children and weights
    printGraphToFile(&fout, graphOfNames);

    // Part b - DFSs and BFSs
    char start[MAX_CHAR_PER_WORD+1];

    // first word
    fprintf(fout, "\n\n==================================Part (b)==================================\n");
    fscanf(fin, "%s", start);
    capitalize(start);
    DFS(&fout, graphOfNames, start);
    BFS(&fout, graphOfNames, start);

    // second word
    fscanf(fin, "%s", start);
    capitalize(start);
    DFS(&fout, graphOfNames, start);
    BFS(&fout, graphOfNames, start);

    // dijkstra's algorithm
    fprintf(fout, "\n\n%s", "==================================Part (c)==================================");
    fscanf(fin, "%s", start);
    while(strcmp(start, FILE_SENTINEL) != 0){

        capitalize(start);
        int startingLocation = binarySearch(graphOfNames, start);
        dijkstra(&fout, graphOfNames, startingLocation);
        fscanf(fin, "%s", start);

    }

    // close file
    fclose(fin);
    fclose(fout);

    printf("\nOutput sent to output.txt\n");

    return 0;

}
