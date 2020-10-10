#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DICTIONARY_FILE_NAME "dictionary_en_randomized_four_letter.txt"
#define DICTIONARY_SENTINEL "$$$$"
#define DIGIT_STRING_SENTINEL "0"
#define MAX_WORD_LENGTH 20


void printArrayToTextFile(char **array, int n){

    FILE *fp = fopen("test_output.txt", "w");
    if(fp == NULL){
        printf("File not open\n");
        exit(-1);
    }


    for(int i = 0; i < n; i++)
        fprintf(fp, "%s\n", array[i]);

    fclose(fp);

}


int getNumWords(){

    FILE *fp = fopen(DICTIONARY_FILE_NAME, "r");
    if(fp == NULL)
        exit(-1);

    int numWords = 0;
    char word[MAX_WORD_LENGTH];
    fscanf(fp, "%s", word);
    while(strcmp(word, DICTIONARY_SENTINEL)!=0){
        fscanf(fp, "%s", word);
        numWords++;
    }

    fclose(fp);
    return numWords;

}


void insertInPlace(char **dictionary, int numWordsInArray, char *word){

    int j = numWordsInArray-1;
    while(j >= 0 && strcmp(word, dictionary[j]) < 0){
        strcpy(dictionary[j+1], dictionary[j]);
        j--;
    }
    strcpy(dictionary[j+1], word);

}


char **importDictionary(int numWords, FILE **fp){


    // make dictionary on the heap becuase the stack is too small
    char **dictionary = (char **) malloc(numWords*sizeof(char *));
    for(int i = 0; i < numWords; i++){
        dictionary[i] = (char *) malloc(MAX_WORD_LENGTH);
    }

    // read and insert in place ascending
    int numWordsInArray = 0;
    char *word = (char *) malloc(MAX_WORD_LENGTH);
    fscanf(*fp, "%s", word);
    for(int i = 0; i < numWords; i++){
        //printf("%d\n", numWordsInArray);
        insertInPlace(dictionary, numWordsInArray, word);
        fscanf(*fp, "%s", word);
        numWordsInArray++;
    }

    return dictionary;

}


int binarySearch(char **dictionary, int numWords, char *word){

    int f = 0, l = numWords-1;
    while(f <= l){
        int m = (f+l)/2;
        if(strcmp(word, dictionary[m])<0) l = m-1;
        else if(strcmp(word, dictionary[m])==0) return m;
        else f = m+1;
    }
    return -1;

}


int toDigit(char ch){
    return ch - '0';
}



void predict(char **dictionary, int numWords, char *digitString, int position, char keypad[][5], char *possibleWord, FILE **fp){

    // base case
    if(digitString[position] == '\0'){
        possibleWord[position] = '\0';
        if(binarySearch(dictionary, numWords, possibleWord) != -1)
            fprintf(*fp, "%s\t", possibleWord);
        else
            return;
    }

    // recursive case, building the combinations
    else{

        if(position == 0){
            strcpy(possibleWord, "\0");
        }

        char *original = (char *) malloc(MAX_WORD_LENGTH);
        strcpy(original, possibleWord);
        int i = 0;
        while(keypad[toDigit(digitString[position])][i] != '\0'){
            strcpy(possibleWord, original);
            possibleWord[position] = keypad[toDigit(digitString[position])][i];
            possibleWord[position+1] = '\0';
            predict(dictionary, numWords, digitString, position+1, keypad, possibleWord, fp);
            i++;
        }
    }
}


void print2DCharArray(char A[][5]){
    for(int i = 2; i <= 9; i++){
        int j = 0;
        while(A[i][j] != '\0'){
            printf("%c\n", A[i][j]);
            j++;
        }
    }
}




int main(){

    int numWords = getNumWords();
    // printf("\n\n%d\n\n", numWords);

    // alphabet for keypad
    char keypad[10][5] = {
        "",
        "",
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz"
    };

    // print2DCharArray(keypad);


    // file stuff
    FILE *fp = fopen(DICTIONARY_FILE_NAME, "r");
    if(fp == NULL)
        exit(-1);

    FILE *fp_out = fopen("output.txt", "w");
    if(fp_out == NULL)
        exit(-1);


    // get dictionary in order
    char **dictionary = importDictionary(numWords, &fp);
    //printArrayToTextFile(dictionary, numWords);
    //printf("%d\n", binarySearch(dictionary, numWords, "pale"));


    // get and analyse digit string
    char *digitString = (char *) malloc(MAX_WORD_LENGTH);
    char *possibleWord = (char *) malloc(MAX_WORD_LENGTH);
    fscanf(fp, "%s", digitString);
    while(strcmp(digitString, DIGIT_STRING_SENTINEL)!=0){
        fprintf(fp_out, "%s\t", digitString);
        predict(dictionary, numWords, digitString, 0, keypad, possibleWord, &fp_out);
        fprintf(fp_out, "\n");
        fscanf(fp, "%s", digitString);
    }


    fclose(fp);
    fclose(fp_out);
    return 0;
}
