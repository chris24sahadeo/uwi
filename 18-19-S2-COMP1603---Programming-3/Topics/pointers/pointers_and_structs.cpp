#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;


struct Student{
    int id;
    char name;
    int gpa;

};


int main(){


    Student *s = (Student*) malloc (sizeof(Student));
    s->id = 1234;
    cout<<s->id<<endl;
    cout<<s<<endl;

    return 0;
}