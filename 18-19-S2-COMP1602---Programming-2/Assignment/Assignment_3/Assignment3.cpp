//Michel Leotaud
//816117751

#include <iostream>
#include <fstream>
#include <cstring> // for character arrays
#include <cstdlib> // for all sorts of stuff
#include <ctime> // for random numbers

	using namespace std;

#define NUMROWS 10				// for drawing hangman diagram
#define NUMCOLS 12				// for drawing hangman diagram
#define NUMLETTERS 10001
#define NUMLETTERSINALPHABET 26
#define NUMWORDS 100


struct Word {
	char word [25];
	char category [25];
	bool used;
};

int randomNumber (int max) {
	return rand() % max;
}


char toLower(char letter){
	if(letter >= 'A' && letter <='Z')
		letter = letter+' ';
	
	return letter;
}


int readCharacters(char data[]) {        
 
    ifstream fin;     
	char ch;     
	int i;             
	
	fin.open("words.txt");     
	
	if (!fin.is_open()) {         
		cout << "Error -- words.txt could not be opened." << endl;         
		return -1;
	}         
	
	i = 0;
	
	fin >> noskipws;          
	fin >> ch;  
	   
	while (!fin.eof()) {
		char letter= toLower(ch);

		data[i] = letter;          
		i = i + 1;           
		fin >> ch;     
	}          
	
	data[i] = '\0';          
	fin.close();
	                
	return i; 

} 

bool isLetter (char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return true;
	else
		return false;
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


void printWords(Word hangmanWords[], int numWords){
	for(int i=0; i<numWords;i=i+1)
		
		cout<<hangmanWords[i].word<<"\t"<<hangmanWords[i].category<<"\t"<<hangmanWords[i].used<<endl;
}


int getWords(char words[], Word hangmanWords[]){

	int end = 0;
	char word[25];
	Word hangmanWord;
	hangmanWord.used = false;
	char category[25];
	int numWords = 0;

	while(end != strlen(words)){

		end = getWord(words, end, word);
		end = getWord(words, end, category);
		strcpy(hangmanWord.word, word);
		strcpy(hangmanWord.category, category);
		hangmanWords[numWords] = hangmanWord;
		// cout << word << "\t" << category << endl;

		numWords++;

	}

	return numWords;

}


void prepareGallows(char drawing[NUMROWS][NUMCOLS]) {
	int i, j;
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			drawing[i][j] = ' ';
		}
	}
		
	for (j=3; j<7; j++)
		drawing[0][j] = '_';

	for (i=1; i<7; i++)
		drawing[i][2] = '|';
	
	for (j=5; j<11; j++)
		drawing[7][j] = '_';
			
	for (j=1; j<11; j++)
		drawing[9][j] = '_';
	
	drawing[1][7] = '|';
	
	drawing[6][1] = '_';
	drawing[6][3] = '_';
	
	drawing[7][0] = '|';
	drawing[8][0] = '|';
	drawing[9][0] = '|';

	drawing[7][4] = '|';	

	drawing[8][11] = '|';	
	drawing[9][11] = '|';	
}


void drawHangman (int livesLost) {
	char drawing [NUMROWS][NUMCOLS];
	int i, j;
	int lives;
	
	prepareGallows(drawing);
		
	if (livesLost >= 1)
		drawing[2][7] = 'o';

	if (livesLost >= 2) {
		drawing[3][7] = 'X';
		drawing[4][7] = 'X';				
	}

	if (livesLost >= 3)
		drawing[3][6] = '/';

	if (livesLost >= 4)
		drawing[3][8] = '\\';

	if (livesLost >= 5)
		drawing[5][6] = '/';

	if (livesLost == 6)
		drawing[5][8] = '\\';
	
	for (i=0; i<NUMROWS; i++) {
		for (j=0; j<NUMCOLS; j++) {
			cout << drawing[i][j];
		}
		cout << endl;
	}
	cout << endl;

	if (livesLost == 6)					// sound the alarm if player loses
		cout << "\a" << endl;
		
}


int getCategories(Word hangmanWords[], int numWords, Word categories[]){
	int numCategories=0;
	bool found;
	for(int i=0; i<numWords; i=i+1){
		found= false;
		for(int j=0; j<numCategories; j=j+1){
			if(strcmp(hangmanWords[i].category , categories[j].category)==0)
				found=true;

		}
		if(!found){
			categories[numCategories]=hangmanWords[i];
			numCategories=numCategories+1;
		}
			
	}
	return numCategories;
}


void printCategories(Word categories[], int numCategories){
	
	for(int i=0; i<numCategories; i=i+1){
		cout<< i+1 <<"." <<categories[i].category<<endl;
	}
	cout << "\nChoose category (1 to " << numCategories << "): "; 

}


void setWordToUsed(Word hangmanWords[], int numWords, char wordSelected[]){
	// This function finds wordSelected in the words
	// array and sets its used field to true. 

	for(int i=0; i< numWords; i=i+1){
		if(strcmp(wordSelected, hangmanWords[i].word)==0){
			hangmanWords[i].used=true;
			break;
		}
	}
}


bool findCategoryWord(Word hangmanWords[], int numWords, char category[], char wordSelected[]){    	// This function finds all the words in the words
																									// array that are in the category specified (if not
																									// used before) and stores them in an array. It
																									// then randomly chooses a word from this array
																									// and stores it in wordSelected. The
																									// randomNumber function can be called to
																									// generate a random location in the array. 

	Word wordsInCategory[numWords];
	int j=0;

	// put all words with the given category in wordsInCategory
	for(int i=0; i<numWords; i=i+1){
		if(strcmp(category, hangmanWords[i].category)==0 && hangmanWords[i].used==false){
			// cout << "found" << endl;
			wordsInCategory[j]=hangmanWords[i];
			j=j+1;
		}		
	}

	//because all words in category were already used
	if (j==0){
		cout << "No words in "<< category << " left\n";
		return false;
	}
		


	int randomLocation=randomNumber(j);
	strcpy(wordSelected, wordsInCategory[randomLocation].word);
	setWordToUsed (hangmanWords, numWords, wordSelected);
	return true;
}


bool checkLetter(char guessWord[], char displayWord[], char letter){
	// This function checks the word to be guessed to
	// determine if letter is present. If so, the
	// corresponding letters in the displayWord are
	// revealed. 

	bool found = false;
	for(int i = 0; i < strlen(guessWord); i++){
		if(guessWord[i] == letter){
			found = true;
			displayWord[i] = guessWord[i];
		}
	}
	return found;	
}


void initWord(char guessWord[], char displayWord[]){
	// This function initializes the word to be
	// displayed based on the word to be guessed. It
	// also reveals the letters from “RSTLNE” if they
	// are present. 
	
	char lettersGiven[7] = "rstlne";

	int i;
	for(i=0 ; i < strlen(guessWord);  i=i+1){
		bool found = false;
		for(int j=0; j < strlen(lettersGiven) ;j=j+1){
			if(guessWord[i]==lettersGiven[j]){
				displayWord[i] = guessWord[i];
				found = true;
				break;
			}			
		}
		if(!found){
			displayWord[i] = '_';
		}		
	}
	displayWord[i] = '\0';
}


void drawWord(char displayWord[]){
	// This function displays the word being guessed
	// by the player where each letter is separated by
	// a space
	for(int i = 0; i < strlen(displayWord); i++){
		cout << displayWord[i] << " ";
	}
	cout << endl;
}


int lettersMissing(char displayWord[]){
	// This function determines how many letters
	// must still be guessed in the displayWord. The
	// count includes repeated letters. 
	int num_ = 0;
	for(int i = 0; i < strlen(displayWord); i++){
		if(displayWord[i] == '_'){
			num_++;
		}
	}
	return num_;
}


bool isValidChoice(int choice, int numCategories){
	return choice >= 1 && choice <= numCategories;
}


int getChoice(Word categories[], int numCategories){
	// get choice from user
	int choice;
	printCategories(categories, numCategories);
	cin >> choice;
	cout << "\n\n";
	while(!isValidChoice(choice, numCategories)){
		cout << "Please select a choice in range!\n\n";
		printCategories(categories, numCategories);
		cin >> choice;
	}
	cout << "You chose \"" << categories[choice-1].category << "\""<< endl;
	return choice;
}


bool won(char displayWord[]){
	return lettersMissing(displayWord) == 0;
}


bool lose(int livesRemaining){
	return livesRemaining <= 0;
}


bool endGame(char displayWord[], int livesRemaining){
	return won(displayWord) || lose(livesRemaining);
}


char getLetterInPosition(int position){
	return 'a' + position - 1;
}


int getPositionOfLetter(int letter){
	// assuming common letter
	return letter - 'a' + 1;
}


void printLettersGuessed(bool allLettersGuessed[]){ 
	cout << "Letters guessed: ";
	for(int position = 1; position <= NUMLETTERSINALPHABET; position++){
		if(allLettersGuessed[position]){
			cout << getLetterInPosition(position) << " ";
		}
	}
	cout << endl;
}


int playGame(Word hangmanWords[], int numWords){

	cout << "\n\n";
	Word categories[101];
	int numCategories= getCategories(hangmanWords,numWords, categories);

	char wordSelected[50];

	// get choice from user
	int choice = getChoice(categories, numCategories);

	// TODO: what if all words were used
	bool found = findCategoryWord(hangmanWords, numWords, categories[choice-1].category, wordSelected);
	while(!found){
		// get another choice
		int choice = getChoice(categories, numCategories);
		found = findCategoryWord(hangmanWords, numWords, categories[choice-1].category, wordSelected);
	}

	// cout << "Word to be guessed is " << wordSelected << endl;



	// game code
	int livesRemaining = 6;
	char letterGuess;
	char wordGuess[51];
	int score = 0;
	bool allLettersGuessed[NUMLETTERSINALPHABET+1] = {false};
	char displayWord[51];
	initWord(wordSelected, displayWord);
	

	while(!endGame(displayWord, livesRemaining)){

		drawHangman(6-livesRemaining);
		drawWord(displayWord);
		cout << "Lives remaining: " << livesRemaining << endl;
		printLettersGuessed(allLettersGuessed);

		cout << "Enter letter (enter # to guess the whole word): ";
		cin >> letterGuess;

		if(letterGuess == '#' && lettersMissing(displayWord) >= 2){ // trying to guess the whole word (if correct: +4 points, if wrong: -2 lives)
			cout << "Enter word: ";
			cin >> wordGuess;

			if(strcmp(wordGuess, wordSelected) == 0){ // whole word win
				drawHangman(6-livesRemaining);
				drawWord(displayWord);
				cout << "You Won by word guess! :)\n";
				return 4;
			}
			else{
				livesRemaining-=2;
			}
		}
		else if(letterGuess != '#'){ // trying to guess a single letter (if correct: , if wrong: -1 life)
			if(checkLetter(wordSelected, displayWord, letterGuess)){ // guess is correct!
				;
			}
			else if(!allLettersGuessed[getPositionOfLetter(letterGuess)]){
				livesRemaining--;
			}
			allLettersGuessed[getPositionOfLetter(letterGuess)] = true;
		}
		else
			cout << "One letter remaining, enter your guess!";
	}


	drawHangman(6-livesRemaining);
	drawWord(displayWord);

	if(won(displayWord)){ // individual letter win
		cout << "You Won by single letter guess!\n";
		return 2;
	}

	else{ // lost 
		cout << "You lost :(\n";
		return -2;
	}



}


int main() {
	
	srand(time(NULL));					// for better random number generation
	char words[NUMLETTERS];
	Word hangmanWords[NUMWORDS];

	int numCharacters = readCharacters(words);
	// cout<< words;

	int numWords = getWords(words, hangmanWords);
	
	// printWords(hangmanWords, numWords);

	// accept players name
	char playerName[51];
	cout << "Enter name: ";
	cin >> playerName;
	cout << "Hello, " << playerName << endl;

	bool playAgain = true;
	
	int score = 0;
	while(playAgain){

		score = score + playGame(hangmanWords, numWords);
		cout << "Score: " << score << endl;

		char choice = 'z';
		choice = toLower(choice);
		while(!(choice == 'y' || choice == 'n')){
			cout << "Play Again? (y/n): ";
			cin >> choice;
		}		
		if(choice == 'n')
			playAgain = false;

	}	


	cout << "\n\nThank you for playing :)\n";


	return 0;
}