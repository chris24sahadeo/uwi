/*
    816000772
    CHRISTOPHER SAHADEO
    COMP2611 - Data Structures
    17-18 S1 COMP2611 A3
    
    INSTRUCTIONS TO MARKER:
    	** I AM SURE THAT THIS PROGRAM COMPILES WELL USING TDM-GCC 4.9.2 64-BIT RELEASE, ON A WINDOWS 10 64 BIT SYSTEM
    	** KINDLY ADJUST YOUR COMMAND WINDOW'S DIMENSIONS AND BUFFER SIZE SUCH THAT THE OUTPUT DISPLAYS PROPERLY
    	

    ASSUMPTIONS MADE:
    	** IF A USER IDENTIFIER OCCURS MULTIPE TIMES PER LINE, THEN STORE THE LINE NUMBERS MULTIPLE TIMES IN THE LL


    CONCERNS:
		** WHAT ABOUT WORDS LIKE setw, include, define, namespace, struct, ??


    TO FIX/CONSIDER:
    	** CURRENTLY WORDS LIKE include AND eof ARE NOT IN THE RESERVED WORDS FILE
		** IF < THEN READ UNTIL > ??
	
																									~~REGARDS, chris24 :)
*/


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <ctime>
using namespace std;
#define MAX_RESERVED_WORDS 1000
#define RESERVED_WORDS_FILE "reservedWords.txt"
#define FILE_SIZE 1000000
#define SPACE 40


// WORD STRUCT
struct Word{
	string word;
	int i;
};


// LINKED LIST NODE
struct LLNode{
    int lineNumber;
    LLNode *nextLine;
};


// BINARY SEARCH TREE NODE
struct BSTNode{
    string userIdentifier;
    BSTNode *left;
    LLNode *firstLine;
    BSTNode *right;
};


// CREATE A NEW LINKED LIST NODE
LLNode *newLLNode(int lineNumber){
    LLNode *newLLNode = new LLNode;
    newLLNode->lineNumber = lineNumber;
    newLLNode->nextLine = NULL;
    return newLLNode;
}


// CREATE A NEW BST NODE
BSTNode *newBSTNode(string userIdentifier, int lineNumber){
    BSTNode *newBSTNode = new BSTNode;
    newBSTNode->userIdentifier = userIdentifier;
    newBSTNode->left = NULL;
    newBSTNode->firstLine = newLLNode(lineNumber);
    newBSTNode->right = NULL;
    return newBSTNode;
}


// INSERT IN PLACE FOR STIRNG ARRAY
void insertInPlaceStringArray(string reservedWords[], string key, int numWords){
	int i = numWords-1;
	while(i >=0 && key < reservedWords[i]){
		reservedWords[i+1] = reservedWords[i];
		i--;
	}
	reservedWords[i+1] = key;
}


// BINARY SEARCH FOR STRING ARRAY
int binarySearchStringArray(string reservedWords[], string key, int numWords){
	int hi = numWords-1, lo = 0;
	while(lo <= hi){
		int mid = (lo+hi)/2;
		if(key < reservedWords[mid]) hi = mid-1;
		else if(key == reservedWords[mid]) return mid;
		else lo = mid+1;
	}
	return -1;
}


// CHECKS IF CHARACTER IS A LETTER
bool isLetter(char ch){
	return ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z';
}


// CHECKS IF CHARACTER IS A DIGIT
bool isNumber(char ch){
	return ch >= '0' && ch <= '9';
}


// CHECKS IF CHARACTER IS A SUITABLE STARTING VALUE
bool isStartingValue(char ch){
	return isLetter(ch) || ch  == '_';
}


// CHECKS IF CHARATER IS A SUITABLE CONTINUING VALUE
bool isContinuingValue(char ch){
	return isStartingValue(ch) || isNumber(ch);
}


// EXCLUSION CHECKING
int exclude(string file, int i){
	int fileLength = file.length();

	/*
	// EXCLUDES C++ LIBRARIES
	if(i < fileLength && file[i] == '<'){
		i++;
		while(i < fileLength && file[i] != '>'){
			i++;
		}
		i++;
	}
	*/
	
	// EXCLUDES ""
	if(i < fileLength && file[i] == '\"'){
		i++;
		while(i < fileLength && file[i] != '\"'){
			i++;
		}
		i++;
	}

	// EXCLUDES ''
	if(i < fileLength && file[i] == '\''){
		i++;
		while(i < fileLength && file[i] != '\''){
			i++;
		}
		i++;
	}

	// EXCLUDES //
	if(i < fileLength && file[i] == '/' && i+1 < fileLength && file[i+1] == '/'){
		i+=2;
		while(i < fileLength && file[i] != '\n'){
			i++;
		}
		i++;
	}

	// EXCLUDES /**/
	if(i < fileLength && file[i] == '/' && i+1 < fileLength && file[i+1] == '*'){
		i+=2;
		while(i < fileLength && i+1 < fileLength && (file[i] != '*' || file[i+1] != '/')){
			i++;
		}
		i+=2;
	}
	// END OF EXCLUSIONS CHECKING

	return i;
}


// GETS WORD
Word getWord(string file, int i){
    Word word;
	word.word = "";
	int fileLength = file.length();

	// READING UNTIL A VALID STARTING VALUE IS FOUND
	i = exclude(file, i);
	while(i < fileLength && !isStartingValue(file[i])){
		i++;
		i = exclude(file, i);
	}

	// GETTING A POSSIBLE USER IDENTIFIER
	while(i < fileLength && isContinuingValue(file[i])){
		word.word+=file[i];
		i++;
	}

	word.i = i;
    return word;
}


// PRINT ENTIRE LL
void printLL(LLNode *firstLine){
    LLNode *current = firstLine;
    bool comma = false;
    while(current != NULL){
    	if(comma){
    		cout << ", ";
		}
        cout << current->lineNumber;
        comma = true;
        current = current->nextLine;
    }
}


// PRINT DATA IN A SINGLE BST NODE
void printBSTNode(BSTNode *current){
    cout << setw(SPACE) << current->userIdentifier << "\t";
    printLL(current->firstLine);
    cout << endl;
}


// INORDER TRAVERSAL TO PRINT THE ENTIRE BST
void printBST(BSTNode *root){
    if(root == NULL)
        return;

    printBST(root->left);
    printBSTNode(root);
    printBST(root->right);
}


// INORDER TRAVERSAL TO SEARCH BST
BSTNode *search(BSTNode *root, string userIdentifier){
    if(root == NULL)
        return NULL;

	if(userIdentifier < root->userIdentifier)
        return search(root->left, userIdentifier);

    if(userIdentifier == root->userIdentifier)
    	return root;

    if(userIdentifier > root->userIdentifier)
        return search(root->right, userIdentifier);
}


// INSERT A NEW BST NODE IN PLACE
BSTNode *insertBSTNode(BSTNode *root, string userIdentifier, int lineNumber){
    if(root == NULL)
        return newBSTNode(userIdentifier, lineNumber);

    if(userIdentifier < root->userIdentifier)
        root->left = insertBSTNode(root->left, userIdentifier, lineNumber);
    if(userIdentifier > root->userIdentifier)
        root->right = insertBSTNode(root->right, userIdentifier, lineNumber);

    return root;
}


// INSERT A NEW LL NODE IN PLACE (currently just appending to the end since the lines are in consecutuve order by default :) )
void insertLLNode(LLNode *root, int lineNumber){
	LLNode *newNode = newLLNode(lineNumber);
	LLNode *curr = root;

	while(curr->nextLine != NULL){
		curr = curr->nextLine;
	}

	curr->nextLine = newNode;
}


// CHECKS IF A LINE NUMBER HAS ALREADY BEEN ENTERED INTO THE LL FOR A GIVEN NODE
bool inList(LLNode *root, int lineNumber){
	LLNode *curr = root;
	while(curr != NULL){
		if(curr->lineNumber == lineNumber)
			return true;
		curr = curr->nextLine;
	}
	return false;
}


// GETS THE LINE NUMBER OF A GIVEN CHARACTER REFERENCED BY i...ie: file[i]
int getLineNumber(string file, int i){
	int fileLength = file.length();
	int lineNumber = 1;
	for(int j = 0; j <= i; j++){
		if(file[j] == '\n')
			lineNumber++;
	}
	return lineNumber;
}


// POPULATE BST
BSTNode *populateBST(BSTNode *root, string file, string reservedWords[], int numReservedWords){

    char ch;
    bool pass;
    int i = 0;
    int fileLength = file.length();
    int lineNumber;
    while(i < fileLength){
    	
		// GET A WORD
		Word word = getWord(file, i);
		i = word.i;
		lineNumber = getLineNumber(file, i);
		
		// FOR USER IDENTIFIERS THAT HAPPEN TO BE THE LAST WORD ON A LINE
		if(file[i] == '\n'){
			lineNumber--;
		}
		// cout << lineNumber << "\t" << word.word << endl;


		// CHECK IF WORD IS A POSSIBLE USER IDENTIFIER
		if(binarySearchStringArray(reservedWords, word.word, numReservedWords) == -1){

			// SEARCH BST FOR WORD
			BSTNode *insertHere = search(root, word.word);

			// CHECK IF NOT IN BST
			if(insertHere == NULL){
				// INSERT THIS NEW NDOE INTO BST
				root = insertBSTNode(root, word.word, lineNumber);
			}
			else{// WORD ALREADY IN THE BST -> ADD NEW LINE NUMBER
				insertLLNode(insertHere->firstLine, lineNumber);						
			}
		}
	}
	
	return root;
}


// PRINT LIST OF RESERVED WORDS
void printReservedWords(string reservedWords[], int numWords){
	cout << "******************************************************************************************************************************************LIST OF RESERVED WORDS...\n";
	for(int i = 0; i < numWords; i++){
		cout << reservedWords[i] << endl;
	}
	cout << "ENDOFLIST\n\n\n";
}


// READ RESERVED WORDS
int readReservedWords(string reservedWords[]){
	ifstream fin(RESERVED_WORDS_FILE);
	if(!fin){
	    cout << "Reserved Words File Error!\n\n";
	    exit(-1);
	}

	int i = 0;
	string word;
	fin >> word;
	while(!fin.eof()){
		if(binarySearchStringArray(reservedWords, word, i) == -1){
			insertInPlaceStringArray(reservedWords, word, i);
			i++;
		}

		fin >> word;
	}

	fin.close();
	return i;
}


// PRINT FILE TO BE ANALYSED
void printFile(string file){
	cout << "\n******************************************************************************************************************************************FILE TO BE ANALYSED...\n\n";

	int lineNumber = 1;
	cout << lineNumber << ".\t";
	for(int i = 0; i < file.length(); i++){
		cout << file[i];
		if(file[i] == '\n'){
			lineNumber++;
			cout << lineNumber << ".\t";
		}
	}

	cout << "\n\n\n";
}


// READ FILE TO BE ANALYSED
string readFile(string fileToAnalyse){
    ifstream fin(fileToAnalyse.c_str());
    if(!fin){
        cout << "File Error!\n\n";
        exit(-1);
    }

    char ch;
    string file;
    fin >> noskipws;
    fin >> ch;
    while(!fin.eof()){
        file += ch;
        fin >> ch;
    }
    
    fin.close();
    return file;
}


// GET FILE TO ANALYSE
string getFileNameToAnalyse(){
	string fileToAnalyse;
	cout << "Enter file name you wish to analyse (with extension): ";
	cin >> fileToAnalyse;
	return fileToAnalyse;
}


int main(){
	
	// CREATING POINTER TO ROOT NODE OF BST
    BSTNode *root = NULL;

	// GETTING THE LIST C++ RESERVED WORDS FROM A TEXT FILE
	string reservedWords[MAX_RESERVED_WORDS];
	int numReservedWords = readReservedWords(reservedWords);
	printReservedWords(reservedWords, numReservedWords);


	// GETTING THE C++ FILE TO BE ANALYSED
	string fileToAnalyse = "sampleInput.cpp";
	
	// getFileNameToAnalyse();
	
  	string file = readFile(fileToAnalyse);

	// DISPLAYING THE C++ FILE TO BE ANALYSED;
	printFile(file);

	// POPULAITNG THE BST
	root = populateBST(root, file, reservedWords, numReservedWords);

	// PRINT THE BST
	cout << "\n\n\n******************************************************************************************************************************************FILE ANALYSIS\n" << setw(SPACE) << "IDENTIFIER" << "\tLINE(S)\n\n";
	printBST(root);
	
	
    return 0;
}
