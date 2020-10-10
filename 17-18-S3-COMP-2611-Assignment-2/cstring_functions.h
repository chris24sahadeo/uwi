// basic char fucntions
bool isUpper(char ch){return ch >= 'A' && ch <= 'Z';}
bool isLower(char ch){return ch >= 'a' && ch <= 'z';}
bool isLetter(char ch){return isUpper(ch) || isLower(ch);}


char toUpper(char ch){
    if(isLower(ch)) return ch - ' ';
    return ch;
}
char toLower(char ch){
    if(isUpper(ch)) return ch + ' ';
    return ch;
}


// corrects capitalization, first letter capitalized, rest common
void correctCase(char word[]){

    // make first letter capital
    word[0] = toUpper(word[0]);

    // make all the other letters common
    for(int i = 1; word[i] != '\0'; i++)
        word[i] = toLower(word[i]);

}


// gets a single word from the FILE
// returns 0 if there are more words on a line and we have a name in word
// returns 1 if we have reached the end of a line and we have a name in word
// returns 2 if we have reached the end of the file and we have a name in word
int getWord(char *word, FILE **fin){

    // read until we hit a letter or \n or end of file
    char ch = '\0';
    ch = fgetc(*fin);
    while(!(isLetter(ch) || ch == '\n' || ch == EOF)) ch = fgetc(*fin);


    // checking what we have in c
    if(ch == '\n') return 1;
    if(ch == EOF) return 2;


    // else we have a word to get
    int i = 1;
    word[0] = ch;
    ch = fgetc(*fin);
    while(isLetter(ch)){
        word[i++] = ch;
        ch = fgetc(*fin);
    }

    // terminate cstring
    word[i] = '\0';

    // case correct
    correctCase(word);

    // take a step back
    fseek(*fin, -1L, SEEK_CUR);

    // more stuff to get
    return 0;

}
