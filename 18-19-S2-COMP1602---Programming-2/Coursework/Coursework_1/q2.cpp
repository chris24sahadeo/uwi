#include <iostream>
#include <cstring>
using namespace std;


// 2.a
char toLowerCase(char ch){
    if(ch >= 'A' && ch <= 'Z')
        ch = ch + ' ';
    return ch;
}


// 2.b
bool isIngWord(char s[]){
    int j = strlen(s);
    if(j < 3)
        return false;
    
    char lastCharacter = toLowerCase(s[j-1]);
    char secondTolastCharacter = toLowerCase(s[j-2]);
    char thirdToLastCharacter = toLowerCase(s[j-3]);

    return thirdToLastCharacter = 'i' && secondTolastCharacter = 'n' && thirdToLastCharacter = 'g';    
}


bool isDigit(char ch){
    return ch >= '0' && ch <= '9';
}


int charToInt(char digit){
    return digit - '0';
}


// 2.c
int getInt(char s[]){
    int i = 0;

    while(s[i] != '\0' && !isDigit(s[i]))
        i++;
    
    int number = 0;
    while(s[i] != '\0' && isDigit(s[i])){
        int digit = charToInt(s[i]);
        number = number*10 + digit;
        i++;
    }

    return number;
}


// 2.d
int commonLetter(char word1[], char word2[]){

    int i = 0;
    int count = 0;
    while(word1[i] != '\0' && word2[i] != '\0')
        if(toLowerCase(word1[i]) == toLowerCase(word2[i]))
            count++;
    
    return count;
}


int main(){

    return 0;
}