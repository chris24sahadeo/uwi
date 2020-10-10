/*
    816000772
    COMP2611 - Data Structures
    17-18 S1 COMP2611 A3

    ASSUMPTIONS:
        1. Using a very basic list of reserved words
        2. Using a very basic list of user identifier types


    CONCERNS:
        1. Based on my method, is there a need for a 
        
    TO FIX/CONSIDER
		0. IDENTIFIES ARE EVERYTHING THAT ARE NOT RESERVED!!! THATS WHAT THE RESERVED LIST IS FOR!!! SORT LIST SO I CAN USE BINARY SEARCH LATER ON
    	1. For the love of God please do the outputting and processing separately
    	2. Use C Strings??
    	3. getline and Parsing
    	
    	4. ONLY ADD TO BST IF USER IDENTIFIER TYPE AND NOT ALREADY IN TREE
		5. HOW TO DEAL WITH STRUCTS AND #define AND #include?
		
		6. IF RESERVED OR NOT STARING VALUE OR NOT CONTINUING VALUE THEN JUMP TO CLOSEST WHITE SPACE!!!
		
    		resume session from line 314...
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
#define MAX_IDENTIFIER_TYPES 1000
#define FILENAME "userIdentifiers.cpp"
#define FILE_SIZE 1000000
#define SPACE 40 


// LIST OF RESERVED WORDS (MUST MAKE EXHAUSTIVE)
// SHOULD SORT THIS LIST SO A BINARY SEARCH CAN BE PERFORMED
// READ FROM A FILE??
string reservedWords[] = {
	
};
int numReservedWords = sizeof(reservedWords)/sizeof(string);


// LIST OF USER IDENTIFIER TYPES (DONT USE)
string userIdentifierTypes[] = {
    "#define",
    "char",
    "string",
    "int",
    "short",
    "long",
    "float",
    "double",
    "bool",
    "struct"
};
int numUserIdentifierTypes = sizeof(userIdentifierTypes)/sizeof(string);


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


// GETS WORD
Word getWord(string file, int i){
    Word word;    
    word.word+=file[i];

    i++;
	while(i < file.length() && isContinuingValue(file[i])){
		cout << file[i];
        word.word += file[i];
        i++;
    }
    
    word.i = i-1;    
    return word;
}


// CHECKS IF IS AN IDENTIFIER TYPE
bool isUserIdentifierType(string word){
	for(int i = 0; i < numUserIdentifierTypes; i++){
		if(word == userIdentifierTypes[i])
			return true;
	}
	return false;
}


// PRINT ENTIRE LL
void printLL(LLNode *firstLine){
    LLNode *current = firstLine;
    while(current != NULL){
        cout << current->lineNumber << " ";
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


// INSERT A NEW LL NODE IN PLACE (currently just appending to the end)
void insertLLNode(LLNode *root, int lineNumber){
	LLNode *newNode = newLLNode(lineNumber);
	LLNode *curr = root;
	
	while(curr->nextLine != NULL){
		curr = curr->nextLine;
	}
	
	curr->nextLine = newNode;
}


bool inList(LLNode *root, int lineNumber){
	LLNode *curr = root;
	while(curr != NULL){
		if(curr->lineNumber == lineNumber)
			return true;
		curr = curr->nextLine;
	}
	return false;
}


// POPULATE BST
BSTNode *populateBST(BSTNode *root, string file){
    
    char ch;
    bool pass;
    int i;    
    int fileLength = file.length();
    int lineNumber = 1;
    cout << lineNumber << ".\t";
    for(i = 0; i < fileLength; i++){
    	pass = false;
        cout << file[i];
	
		
		// EXCLUSIONS (I KNOW THIS CODE IS NOT PRETTY...BUT IT WORKS!!!)
        if(file[i] == '\"'){
            i++;
            while(i < fileLength && file[i] != '\"'){
                cout << file[i];
                if (file[i] == '\n'){
		            lineNumber++;
		            cout << lineNumber << ".\t";
		        }                
                i++;
                
            }
            cout << file[i];
        }
        
        
        if(file[i] == '\''){
            i++;
            while(i < fileLength && file[i] != '\''){
                cout << file[i];
                if (file[i] == '\n'){
		            lineNumber++;
		            cout << lineNumber << ".\t";
		        }                
                i++;
                
            }
            cout << file[i];
        }
        
        
        if(file[i] == '/' && i+1 < fileLength && file[i+1] == '/'){
            i++;
            while(i < fileLength && file[i] != '\n'){
                cout << file[i];                               
                i++;                
            }
            i--;       
		} 
		
        
        if(file[i] == '/' && i+1 < fileLength && file[i+1] == '*'){
            i++;
            cout << file[i];
            i++;
            while(i < fileLength && i+1 < fileLength && file[i] != '*' && file[i+1] != '/'){
                cout << file[i];
				 if (file[i] == '\n'){
		            lineNumber++;
		            cout << lineNumber << ".\t";
		        }                            
                i++;                
            }
            i--;  
			if (file[i] == '\n'){
		        pass = true;
		    }       
		}
		
		
		// CHECKING FOR IDENTIFIER
        if(isStartingValue(file[i])){
            Word word;
            word = getWord(file, i);
            i = word.i;
            
            if(isUserIdentifierType(word.word)){
            	i++;
            	
            	while(!isStartingValue(file[i])){
            		cout << file[i];
            		if(file[i] == '\n'){
            			lineNumber++;
            			cout << lineNumber << ".\t";
					}
            		i++;
				}
				
				
			}
            	
        	cout << "?" << word.word << "?";
        	i--;
        	word = getWord(file, i);
        	i = word.i;
        	cout << "~" << word.word << "~";
        	
        	// SEARCH BST
        	BSTNode *insertHere = search(root, word.word);
        	
        	// IF USER IDENTIFIER IS NOT IN TREE YET
        	if(insertHere == NULL){
        		root = insertBSTNode(root, word.word, lineNumber);
			}
			// IF USER IDENTIFIER IS ALREADY IN TREE
			else{
				
				// IF LINE NUMBER IS NOT IN THE LINKED LIST
				if(!inList(insertHere->firstLine, lineNumber)){
					insertLLNode(insertHere->firstLine, lineNumber);
				}
			}
			
        }            
		

        if (file[i] == '\n'){
        	if(pass);
        	else{
        		lineNumber++;
            	cout << lineNumber << ".\t";
			}         
        }
    }
	
	cout << "\n\n\n";
    return root;
}



// READ .cpp FILE
string readFile(){
    ifstream fin(FILENAME);
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
    file += '\0';
    fin.close();
    return file;
}



int main(){
    BSTNode *root = NULL;


    /*
    root = insertBSTNode(root, "cat", 1);
    root = insertBSTNode(root, "apple", 1);
    root = insertBSTNode(root, "bat", 2);
    */

    string file = readFile();
	root = populateBST(root, file);

    printBST(root);
    return 0;
}
