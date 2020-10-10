//Vishma Singh
//816003377
//My program works 100% well.

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void grades(int *mark, char *grade){
    if(*mark >= 90)
        *grade = 'A';

    else if(*mark >= 80)
        *grade = 'B';

    else if(*mark >= 60)
        *grade = 'C';

    else if(*mark >= 50)
        *grade = 'D';

    else *grade = 'F';

}

int main(){

    ifstream fin;
    ofstream fout;
   
    fin.open("input.txt");
   
    fout.open("output.txt");

    int *ID = (int*) malloc(sizeof(int));
    int *math = (int*) malloc(sizeof(int));
    int *english = (int*) malloc(sizeof(int));
    int *count = (int*) malloc(sizeof(int));
    int *highestMath = (int*) malloc(sizeof(int));
    int *highestEnglish = (int*) malloc(sizeof(int));
    int *mathTotal =(int*) malloc(sizeof(int));
    int *englishTotal=(int*) malloc (sizeof(int));

    float *avgMath = (float*) malloc (sizeof(float));
    float *avgEnglish = (float*) malloc (sizeof(float));

    char *mathGrade = (char*) malloc(sizeof(char));
    char *englishGrade = (char*) malloc(sizeof(char));

    fin>>*ID;
    *count=0;
    *highestMath = 0;
    *highestEnglish = 0;

    fout<<"ID"<<"\t\t"<<"Mathematics Mark"<<'\t'<<"Mathematics Grade"<<'\t'<<"English Mark"<<'\t'<<"English Grade"<<endl;

    while (*ID!=0){
        fin>>*math>>*english;
        *count = *count+1;

        if(*math>*highestMath)
            *highestMath=*math;

        if(*english>*highestEnglish)
            *highestEnglish=*english;

        *mathTotal = *mathTotal + *math;
        *englishTotal = *englishTotal + *english;

        grades(math, mathGrade);
        grades(english, englishGrade);

        fout<<*ID<<"\t\t\t"<<*math<<"\t\t\t\t"<<*mathGrade<<"\t\t\t\t"<<*english<<"\t\t\t\t"<<*englishGrade<<"\t\t\t\t"<<endl;

        fin>>*ID;  

    }

    *avgMath = (*mathTotal)*1.0/(*count);
    *avgEnglish = (*englishTotal)*1.0/(*count);

    fout<<"\nNumber of candidates : "<<*count<<endl;
    fout<<"Highest mark in Mathematics : "<<*highestMath<<endl;
    fout<<"Highest mark in English : "<<*highestEnglish<<endl;
    fout<<"Average mark in Mathematics : "<<*avgMath<<endl;
    fout<<"Average mark in English : "<<*avgEnglish<<endl;

    fin.close();
    fout.close();

    return 0;
}