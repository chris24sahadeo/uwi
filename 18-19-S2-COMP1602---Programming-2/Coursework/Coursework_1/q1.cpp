#include <iostream>
#include <cstring>
using namespace std;


// 1.a
struct Part{
    int id;
    char name[20];
    float price;
    int numAvailable;
};


struct Date{
    int day, month, year;
}


// 1.b
int readPart(Part parts[]){

    ifstream fin('parts.txt');
    if(!fin){
        exit(-1);
    }

    
    int numParts = 0;
    Part tempPart;

    fin >> tempPart.id;
    while(tempPart != 99999){
        fin >> tempPart.name >> tempPart.price >> tempPart.numAvailable;

        parts[numParts] = tempPart;
        numParts++;

        fin >> tempPart.id;
    }

    fin.close();

    return numParts;

}


// 1.c
void displayPart(Part part){
    cout << "ID: " << part.id << endl;
    cout << "NAME: " << part.name << endl;
    cout << "SELLING PRICE: " << part.price << endl;
    cout << "QUANTITY AVAILABLE: " << part.numAvailable << endl;
}


// 1.d sequential search
int hasPart(Part parts[], int numParts, int partNo){
    for(int i = 0; i < numParts; i++){
        if(partNo == parts[i].id){
            return i;
        }
    }
    return -1;
}


// 1.e
int sellPart(Part parts[], int numParts, int partNo, int quantity){

    int loc = hasPart(parts, numParts, partNo);

    if(loc == -1)
        return loc;
    
    if(parts[loc].numAvailable < quantity)
        return 0;
    
    parts[loc].numAvailable = parts[loc].numAvailable - quantity;
    return 1;

}


// 1.f
bool isLeapYear(int year){
    return year%400 == 0 || year%4 == 0 && year%100 != 0;
}

Date deliveryDate(Date d){

    int daysIn[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeapYear(d.year))
        daysIn[2]++;
    
    d.day++;
    if(d.day > daysIn[d.month]){
        d.day = 1;
        d.month++;
    }
    if(d.month > 12){
        d.month = 1;
        d.year;
    }

    return d;

}


int main(){

    Part parts[1000];



}