#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

// constants
#define NUM_LETTERS_1 21
#define MAX_COLS 100
#define MAX_ROWS 100
#define MAX_DICT_WORDS 500
#define FILENAME "synonyms.txt"
#define DICT_FILENAME "dictionary.txt"
#define SPACE 20
#define SENTENCE_LENGTH 101
#define SENTENCE_WORDS 50


// struct defintion
struct Word{
    char word[NUM_LETTERS_1];
};


struct Dimensions{
    // stores the dimensions of the 2d array
    int numRows, numCols;
};


void printMenu(){
    // prints menu
    cout << "Synonym Checker\n---------------------------------------------\n1. Load Synonyms\n2. Search Synonyms\n3. Display Words and Synonyms\n4. Parse Sentence\n5. Quit\n\nPlease enter an option: ";
}


void printThesaurus(Word thesaurus[][MAX_COLS], int R, int numWordsInRow[]){
    // prints all synonyms
    cout << setw(SPACE) << "WORD\t" << "SYNONYMS\n";
    for(int i = 0; i < R; i++){
        cout << setw(SPACE) << thesaurus[i][0].word << '\t';
        for(int j = 1; j < numWordsInRow[i]; j++){
            cout << thesaurus[i][j].word << "\t";
        }
        cout << "\n";
    }
    cout << endl;
}


void printDictionary(Word dictionary[], int n){
    // cout << "DICTIONARY:\n";
    for(int i = 0; i < n; i++){
        cout << dictionary[i].word << endl;
    }
    cout << endl;
}


int numCharacters(){
    // counts the number of characters in the file

    ifstream in;
    in.open(FILENAME);
    if(!in){
        cout << "Error! Aborting...\n";
        return -1;
    }

    int count = 0;
    char ch;
    in >> noskipws;
    in >> ch;
    while(!in.eof()){
        count++;
        in >> ch;
    }

    in.close();
    return count;

}


void readCharacters(char s[]){
    // reads all characters from file and stores in 1D array of char

    ifstream in;
    in.open(FILENAME);
    if(!in){
        cout << "Error! Aborting...\n";
        return;
    }

    int i = 0;
    char ch;
    in >> noskipws;
    in >> ch;
    while(!in.eof()){
        s[i] = ch;
        i++;
        in >> ch;
    }
    in.close();
    s[i] = '\0';
    // cout << s << endsl;

}


bool isUpper(char c){
    // checks if c is uppercase
    return c >= 'A' && c <= 'Z';
}


bool isLetter(char ch){
    // checks if c is a letter
    return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}


void toLower(char s[]){
    // makes the cstring s all lowercase letters
    int i = 0;
    while(s[i] != '\0'){
        if(isUpper(s[i])){
            s[i] += ' ';
        }
        i++;
    }
}


Dimensions getDimensionsAndWords(char s[], int use = 1, Word thesaurus[][MAX_COLS] = NULL, int numWordsinRow[] = NULL){
    // if use is 1 then get dimensions only
    // if use is 2 then put words in 2d array

    Dimensions dim = {0, 0};

    int i = 0;
    char word[NUM_LETTERS_1];
    while(s[i] != '\0'){
        int numCols = 0;
        while(s[i] != '\0' && s[i] != '\n'){
            int j = 0;
            while(isLetter(s[i])){
                word[j] = s[i];
                j++;
                i++;
            }
            word[j] = '\0';
            // cout << word << endl;
            if(use == 2){
                Word newWord;
                toLower(word);
                strcpy(newWord.word, word);
                thesaurus[dim.numRows][numCols] = newWord;
                // cout << newWord.word << endl;
            }
            // cout << "\t";
            numCols++;
            while(s[i] != '\0' && s[i] != '\n' && !isLetter(s[i])){
                i++;
            }
            // cout << endl;
        }
        if(use == 2) numWordsinRow[dim.numRows] = numCols;
        if(numCols > dim.numCols){
            dim.numCols = numCols;
        }
        if(s[i] == '\n') {
            i++;            
            // cout << "Num Rows: " << dim.numRows << endl;
        }
        dim.numRows++;        
    }

    // cout << "Num Rows: " << dim.numRows << "\tNum Cols: " << dim.numCols << endl;
    return dim;
}


int search(Word thesaurus[][MAX_COLS], int R, int C[], char word[] = "noinput"){
    // searches for word in thesaurus
    // if no word found 
        // then return -1
    // else word found
        // if no synonym found
            // return 0
        // else synonym found
            // return row number
    // returns the row in which synonym was found

    bool foundWord = false, foundSynonym = false;
    // char word[NUM_LETTERS_1];
    if(strcmp(word, "noinput") == 0){        
        cout << "Enter word: ";
        cin >> word;
    }
    
    toLower(word);

    for(int r = 0; r < R; r++){
        for(int c = 0; c < C[r]; c++){
            if(strcmp(thesaurus[r][c].word, word) == 0){
                foundWord = true;
                cout << "Synonyms:\t";
                for(int i = 0; i < C[r]; i++){
                    if(strcmp(thesaurus[r][i].word, word) != 0){
                        foundSynonym = true;
                        cout << thesaurus[r][i].word << "\t";
                    }
                }
                if(!foundSynonym){
                    cout << "No synonyms found\n\n";
                    return 0;
                }else{ // synonym founds
                    cout << "Synonyms found in row " << r << "\n\n";
                    return r;
                }
            }
        }
    }
    if(!foundWord) {
        cout << word << " not found\n\n";
        return -1;
    }
}


void insertWordInPlace(Word words[], int numWords, Word word){
    int j = numWords-1;
    while(j >= 0 && strcmp(word.word, words[j].word)<0){
        words[j+1] = words[j];
        j--;
    }
    words[j+1] = word;
}


int readDictionary(Word dictionary[]){
    ifstream fin(DICT_FILENAME);
    if(!fin){
        cout << "error opening dictionary\n";
        exit(-1);
    }

    char word[NUM_LETTERS_1];
    
    int count = 0;
    while(!fin.eof()){
        fin >> word;
        toLower(word);
        Word dictWord;
        strcpy(dictWord.word, word);
        insertWordInPlace(dictionary, count, dictWord);
        count++;
        // fin >> word;
    }

    fin.close();
    return count;
}


int binarySearchDictionary(Word dictionary[], int numWords, Word key){
    int l = 0, r = numWords-1;
    while(l <= r){
        int m = (l+r)/2;
        if(strcmp(key.word, dictionary[m].word) < 0) r = m-1;
        else if(strcmp(key.word, dictionary[m].word) > 0) l = m+1;
        else return m;
    }
    return -1;
}


int getWord (char words[], int start, char word[]) { 
 
    int i, j, length;         
	
	length = strlen (words);			// find how many characters in words
	
	i = start;
	while (i < length && !isLetter(words[i]))
		i = i + 1;             
		
	if (i == length)					// there are no more words
		return -1;						
		
	j = 0;     							// copy characters to word
	while (isLetter(words[i])) {
		word[j]= words[i];
		i = i + 1;
		j = j + 1;     
	}       
 
    word[j]= '\0';          
    
	return i;							// starting position to look for next word
}


int getWords(char words[], Word wordsArray[]){

	int end = 0;
	char word[25];
	Word temp;
	// hangmanWord.used = false;
	// char category[25];
	int numWords = 0;

	while(end != strlen(words)){

		end = getWord(words, end, word);
		// end = getWord(words, end, category);
        toLower(word);
		strcpy(temp.word, word);
		// strcpy(wordsArray.category, category);
		wordsArray[numWords] = temp;
		// cout << word << "\t" << category << endl;

		numWords++;

	}

	return numWords;

}


void sentenceCheck(Word dictionary[], int numDictWords, Word thesaurus[][MAX_COLS], Dimensions dim, int numWordsInRow[]){

    char sentence[SENTENCE_LENGTH];
    cout << "Enter sentence: ";
    cin.ignore();
    cin.getline(sentence, SENTENCE_LENGTH);
    // cout << sentence;

    Word sentenceWords[SENTENCE_WORDS];
    Word errors[SENTENCE_WORDS];    int numErrors = 0;
    Word okays[SENTENCE_WORDS];     int numOkays = 0;
    int numSentenceWords = getWords(sentence, sentenceWords);
    // printDictionary(sentenceWords, numSentenceWords);

    for(int i = 0; i < numSentenceWords; i++){
        cout << "*** Sentence word: " << sentenceWords[i].word << endl;
        int loc = binarySearchDictionary(dictionary, numDictWords, sentenceWords[i]);
        if(loc == -1){ // not found in dict so check synonyms
            int row = search(thesaurus, dim.numRows, numWordsInRow, sentenceWords[i].word);
            if(row == -1 || row == 0){ // word not found in synonyms or no actual synonym found
                // flag as error
                errors[numErrors] = sentenceWords[i];
                numErrors++;
            }else{
                // check if any of the synonymns (that is not word i) are in the dictionary
                for(int j = 0; j < numWordsInRow[row]; j++){
                    if(strcmp(thesaurus[row][j].word, sentenceWords[i].word) != 0){ // make sure it is a synonym and not the word itself
                        int locInDict = binarySearchDictionary(dictionary, numDictWords, sentenceWords[i]);
                        if(loc != -1){// if synonym is in dict then word is okay
                            okays[numOkays] = dictionary[loc];
                            numOkays++;
                        }else{ // flag as error
                            errors[numErrors] = sentenceWords[i];
                            numErrors++;
                        }
                    }
                }
            }
            
        }
        // else{ // found in dict
        //     cout << sentenceWords << " found in dictionary.\n";
        // }
    }

    cout << "ERROR WORDS:\n\n";
    printDictionary(errors, numErrors);

}


int main(){

    int nC = numCharacters(); // get number of characters in the file
    char fileCharacters[nC+1]; // all characters in the file
    Dimensions dim; // actual dimensions for 2d array
    Word thesaurus[MAX_ROWS][MAX_COLS]; // make 2d array  
    Word dictionary[MAX_DICT_WORDS]; // make dict
    int numDictWords;
    int numWordsInRow[MAX_ROWS] = {0}; // keep track of the number of words per row
    bool thesaurusRead = false;
    bool dictionaryRead = false;


    int choice = 1;
    while(choice != 5){

        printMenu();
        cin >> choice;

        if(choice == 1){
            readCharacters(fileCharacters); // reads all characters from the file
            dim = getDimensionsAndWords(fileCharacters); // gets the dimensions for the 2d array                      
            // cout << "hello\n";
            getDimensionsAndWords(fileCharacters, 2, thesaurus, numWordsInRow); // get the dimension of the 2d array and populate it
            // cout << "hello\n";
            cout << "Synonymns loaded\n\n";
            thesaurusRead = true;

            numDictWords = readDictionary(dictionary);
            cout << "Dictionary loaded\n\n";
            dictionaryRead = true;
            // printDictionary(dictionary, numDictWords);
        }
        else if(choice == 2){
            if(!thesaurusRead || ! dictionaryRead) cout << "No thesaurus in memory\nPlease select option 1 to read the thesaurus\n\n";
            else search(thesaurus, dim.numRows, numWordsInRow);
        }
        else if(choice == 3){
            if(!thesaurusRead || !dictionaryRead) cout << "No thesaurus in memory\nPlease select option 1 to read the thesaurus\n\n";
            else printThesaurus(thesaurus, dim.numRows, numWordsInRow);
        }
        else if(choice == 4)
            if(!thesaurusRead || !dictionaryRead) cout << "No thesaurus in memory\nPlease select option 1 to read the thesaurus\n\n";
            else sentenceCheck(dictionary, numDictWords, thesaurus, dim, numWordsInRow);
        else if(choice == 5){
            cout << "Goodbye\n";
        }
        else {
            cout << "Invalid choice\n\n";
        }

    }
    
   return 0;
}