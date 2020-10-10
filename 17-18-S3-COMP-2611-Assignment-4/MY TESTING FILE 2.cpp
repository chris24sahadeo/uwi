asm	else	new	this
auto	enum	operator	throw
bool	explicit	private	true
break	export	protected	try
case	extern	public	typedef
catch	false	register	typeid
char	float	reinterpret_cast	typename
class	for	return	union
const	friend	short	unsigned
const_cast	goto	signed	using
continue	if	sizeof	virtual
default	inline	static	void
delete	int	static_cast	volatile
do	long	struct	wchar_t
double	mutable	switch	while
dynamic_cast	namespace	template
cin cout string 
NULL
ENDOFLIST

/*
    816000772
    CHRISTOPHER SAHADEO
    17-18 S1 COMP2611 A2
    "THESAURUS"

    100% WORKING!!!...I THINK :)

    NOTES:
        1. The words.in file MUST have a space/tab/new line at the end else a runtime error WILL occur.
        2.

    ~ chris24
*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <climits>
#include <sstream>
#include <stdlib.h>
using namespace std;
#define MAX_SIZE 999999
#define SPACE 21
#define SENTINEL 24


// STRUCTURE DECLARATION FOR ADJACENCY LIST NODE
struct AdjListNode{
    int data;
    bool visited;
    AdjListNode *next;
};


// STRUCTURE DECLARATION FOR ADJACENCY LIST
struct AdjList{
    AdjListNode *head;
    bool visited = false;
};


// STRUCTURE DECLARATION FOR GRAPH [array of AdjList]
struct Graph{
    int V;                  // # of nodes in graph
    AdjList *arr;
};


// CREATES, POPULATES AND RETURNS A NEW ADJLISTNODE
AdjListNode *newAdjListNode(int data){
    AdjListNode *newNode = new AdjListNode;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


// CREATES GRAPH
Graph *newAdjListGraph(int V){
    Graph *newGraph = new Graph;
    newGraph->V = V;
    newGraph->arr = new AdjList;

    for(int i = 0; i < V; i++)
        newGraph->arr[i].head = NULL;

    return newGraph;
}


// ADDS AN EDGE MAINTAINING ASCENDING ORDER
bool addEdge(Graph *graph, int source, int destination){

    bool change = false;
    AdjListNode *newNode = newAdjListNode(destination);


    if(graph->arr[source].head == NULL){
        graph->arr[source].head = newNode;
        return true;
    }

    AdjListNode *curr = graph->arr[source].head;
    AdjListNode *prev = NULL;

    while(curr != NULL && destination >= curr->data){
        if(destination == curr->data)
            return false;
        else{
            change = true;
            prev = curr;
            curr = curr->next;
        }
    }

    if(graph->arr[source].head == curr){
        newNode->next = curr;
        graph->arr[source].head = newNode;
        change = true;
    }
    else{
        prev->next = newNode;
        newNode->next = curr;
        change = true;
    }

    return change;
}


// CONVERT CHECKS IF A SINGLE CHARACTER IS UPPERCASE
bool isUpper(char ch){
    return ch >= 'A' && ch <= 'Z';
}


// CONVERTS ENTIRE STRING TO LOWERCASE
string toLower(string word){
    for(int i = 0; i < word.length(); i++){
        if(isUpper(word[i]))
            word[i]+=' ';
    }
    return word;
}


// BINARY SEARCH
int binarySearch(string words[], int numWords, string key){
    int lo = 0;
    int hi = numWords - 1;
    int mid;
    while(lo <= hi){
        mid = (lo + hi)/2;
        if(key == words[mid]) return mid;
        else if(key < words[mid]) hi = mid - 1;
        else lo = mid + 1;
    }
    return -1;
}


// TO INSERT WORD IN WORDS ALPHABETICALLY
void insertInPlace(string words[], int numWords,  string word){
    int i = numWords - 1;
    while(i >= 0 && word.compare(words[i]) < 0){
        words[i+1] = words[i];
        i--;
    }

    words[i+1] = word;
}


// 3. WORD SEARCH
void wordSearch(string words[], int numWords, Graph *graph){
    system("cls");
    string key;
    cout << "Enter word: ";
    cin >> key;

    key = toLower(key);

    int loc = binarySearch(words, numWords, key);

    if(loc == -1){
        cout << "Word does not exist in thesaurus!\n\n";
        return;
    }

    cout << endl << setw(11) << "SYNONYM(S): ";

    AdjListNode *curr = graph->arr[loc].head;
    while(curr != NULL){
        cout << words[curr->data] << setw(SPACE);
        curr = curr->next;
    }

    cout << "\n\n\n";
}


// 2. PRINT THESAURUS WITH NO REPEATS
void printThesaurusNoRepeats(string words[], int numWords, Graph *graph){
    system("cls");

    // SETTING ALL VERTICIES VISITED VALUE TO FALSE
    for(int i = 0; i < numWords; i++){
        graph->arr[i].visited = false;
    }

    cout << setw(SPACE) << "WORDS" << "\t\tSYNONYMS\n\n";
    for(int i = 0; i < numWords; i++){
        if(!graph->arr[i].visited){
            AdjListNode *curr = graph->arr[i].head;
            cout << setw(SPACE) << words[i] << "\t\t";
            while(curr != NULL){
                cout << words[curr->data] << setw(SPACE);
                graph->arr[curr->data].visited = true;
                curr = curr->next;
            }
            graph->arr[i].visited = true;
            cout << endl;
        }
    }
    cout << "\n\n\n";
}


// 1. PRINT THESAURUS WITH REPEATS
void printThesaurus(string words[], int numWords, Graph *graph){
    system("cls");
    cout << setw(SPACE) << "WORDS" << "\t\tSYNONYMS\n\n";
    for(int i = 0; i < graph->V; i++){
        AdjListNode *curr = graph->arr[i].head;
        cout << setw(SPACE) << words[i] << "\t\t";
        while(curr != NULL){
            cout << words[curr->data] << setw(SPACE);
            curr = curr->next;
        }
        cout << endl;
    }
    cout << "\n\n\n";
}


// MAIN MENU
int menu(string words[], int numWords, Graph *graph){

    cout << "CHRIS24's THESAURUS (I HAVE A LIMITED VOCABULARY) :)\n\n\n";
    cout << "1. Print alphabetical listing of the words and their synonyms (with repeats)\n";
    cout << "2. Print alphabetical listing of the words and their synonyms (without repeats)\n";
    cout << "3. Search for a word\n";
    cout << "4. Quit\n\n";

    int choice;
    cout << "Enter choice (1 to 4): ";
    cin >> choice;
    while(choice < 1 || choice > 4){
        cout << "\nINVALID INPUT!\n";
        cout << "Enter choice (1 to 4): ";
        cin >> choice;
    }

    if(choice == 1) printThesaurus(words, numWords, graph);
    else if(choice == 2) printThesaurusNoRepeats(words, numWords, graph);
    else if(choice == 3) wordSearch(words, numWords, graph);
    else{
        cout << "\n\nGOOD BYE :)\n\n";
        return SENTINEL;
    }
}


// PASS 2 LINKS ALL POSSIBLE SYNONYMS IN THE ADJACENCY LIST
bool pass2(string words[], int numWords, Graph *graph){
    bool change = false;

    AdjListNode *curr1, *curr2;
    for(int i = 0; i < graph->V; i++){
        curr1 = graph->arr[i].head;
        while(curr1 != NULL){
            curr2 = graph->arr[i].head;
            while(curr2 != NULL){
                if(addEdge(graph, curr2->data, i))
                    change = true;
                if(curr2->data != curr1->data){
                    if(addEdge(graph, curr2->data, curr1->data))
                        change = true;
                }
                curr2 = curr2->next;
            }
            curr1 = curr1->next;
        }
    }
    return change;
}


// PASS 1 ONLY ADDS THE WORDS FROM THE .IN FILE...NO FURTHER LINKING OF SYNONYMS IS DONE
void pass1(string words[], int numWords, Graph *graph){
    ifstream fin("words.in");
    if(!fin){
        cout << "Could not open file!!!\n\n\n";
        return;
    }

    string line;
    string word1;
    string word2;
    int source, destination;
    while(getline(fin, line)){
        istringstream ss1(line);

        ss1 >> word1;
        word1 = toLower(word1);
        source = binarySearch(words, numWords, word1);
        while(ss1 >> word1){
            word1 = toLower(word1);
            destination = binarySearch(words, numWords, word1);
            addEdge(graph, source, destination);
        }
    }

    fin.close();
}


// POPLUATE ADJACENCY LIST
void populateGraph(string words[], int numWords, Graph *graph){

    // PASS 1 ONLY ADDS THE WORDS FROM THE .IN FILE...NO FURTHER LINKING OF SYNONYMS IS DONE
    pass1(words, numWords, graph);

    // MULTIPLE PASS 2 REQUIRED (INTERLINKING ALL SYNONYMS) UNTIL NO FURTHER CHANGES IN THE ADJACENCY LIST OCCURS
    while(pass2(words, numWords, graph));
}


// POPULATES THE WORDS ARRAY
int populateWords(string words[], int numWords){

    ifstream fin("words.in");
    if(!fin){
        cout << "Could not open file!!!\n\n\n";
        return -1;
    }

    int newNumWords = 0;            // NO REPEATS
    string line;
    string word;
    while(getline(fin, line)){
        istringstream ss(line);     // PARSING THE LINE INTO INDIVIDUAL WORDS

        while(ss >> word){
            word = toLower(word);

            // IF NOT IN WORDS LIST
            if(binarySearch(words, newNumWords, word) == -1){
                // INSERT IN PLACE
                insertInPlace(words, newNumWords, word);
                newNumWords++;
            }
        }
    }

    fin.close();
    return newNumWords;
}


// RETURNS THE NUMBER OF WORDS IN THE FILE
int getNumWords(){
    ifstream fin("words.in");
    if(!fin){
        cout << "Could not open file!!!\n\n\n";
        return -1;
    }

    string word;
    int count = 0;
    fin >> word;
    while(!fin.eof()){
        count++;
        fin >> word;
    }

    fin.close();
    return count;
}


int main(){

    // GETS THE NUMBER OF WORDS IN THE THESAURUS (NO REPEATS)
    int numWords = getNumWords();
    if(numWords == 0){
        cout << "Thesaurus is Empty!\n\n";
        return -1;
    }

    // CREATING THE WORDS LIST OF (APPROXIMATE) SIZE REQUIRED
    string words[numWords];

    // POPULATING WORDS LIST
    numWords = populateWords(words, numWords);

    // CREATING ADJACENCY LIST OF EXACT SIZE
     Graph *graph = newAdjListGraph(numWords);

    // POPULATING ADJACENCY LIST
    populateGraph(words, numWords, graph);

    // CALLING THE MAIN MENU
    while(menu(words, numWords, graph) != SENTINEL);

    system("pause");
    return 0;
}
