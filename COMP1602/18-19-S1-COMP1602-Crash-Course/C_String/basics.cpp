#include <iostream>
using namespace std;


bool isUpper(char ch){return ch >= 'A' && ch <= 'Z';}
bool isLower(char ch){return ch >= 'a' && ch <= 'z';}
bool isLetter(char ch){return isLower(ch) || isUpper(ch);}
char toUpper(char ch){
    if(isLower(ch))
        return ch - ' ';
    else
        return ch;
}

int position(char ch){
    ch = toUpper(ch);
    return ch - 'A' + 1;
}


bool isPanagram(char s[]){
    int i = 0;
    bool alphabet[27] = {false};
    while(s[i] != '\0'){
        if(isLetter(s[i])){
            int j = position(s[i]);
            // cout << s[i] << '\t' << j << endl;
            alphabet[j] = true;
        }
        i++;
    }

    for(int i = 1; i <= 26; i++){
        // cout << i << '\t' << alphabet[i] << endl;
        if(alphabet[i] == false)
            return false;
    }
    return true;

}


int strlen(char s[]){
    int i = 0;
    while(s[i] != '\0')
        i++;
    return i;
}


void strcpy(char to[], char from[]){
    int i = 0;
    while(from[i] != '\0'){
        to[i] = from[i];
    }
    to[i] = '\0';
}


void strcat(char s1[], char s2[]){
    int i = 0;
    while(s1[i] != '\0')    // to go the end of s1
        i++;

    int j = 0;
    while(s2[j] != '\0'){   // copy from s2[j] to s1[i]
        s1[i] = s2[j];
        i++;
        j++;
    }

    s1[i] = '\0';
}


int strcmp(char s1[], char s2[]){
    int i = 0;
    while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;

    if(s1[i] < s2[i]) return -1;
    else if(s1[i] == s2[i]) return 0;
    else return 1;
}


bool isPalindrome(char s[]){
    int i = 0;
    int j = strlen(s)-1;
    while(i < j){
        if(s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}



int main(){

    // char ch = 'A';
    // ch = ch + ' ';
    //
    // cout << ch;
    //
    // char name[30];
    // cin >> name;
    // cout << name;
    //
    // int num[30];
    // cin >> num[3];
    // cout << num;

    char s[] = "The Quick Brown Fox Jumps Over The Lazy Dog!";
    // cout << isPanagram(s);

    char s1[] = "batman";
    char s2[] = "batman";
    cout << strcmp(s1, s2);

    return 0;
}
