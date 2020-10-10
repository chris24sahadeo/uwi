// CHRISTOPHER SAHADEO
// 816000772
// LEVEL 2
#include <fstream>
// #include <iostream>
using namespace std;


void getLimits(int *left, int *right, int curr){
    if(curr > *left){
        (*right)++;
        (*left)++;
    }
}


void setHighest(int *highestLoc, int *highestSum, int currLoc, int currSum){
    if(currSum > *highestSum){
        *highestSum = currSum;
        *highestLoc = currLoc;
    }
}


int main(){

    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, w;
    fin >> n;
    fin >> w;

    int sums[n+1] = {0};

    int left = 1, right = w, numPeople;
    int highestLoc = 0, highestSum = -1;
    for(int i = 1; i <= n; i++){
        fin >> numPeople;
        getLimits(&left, &right, i);
        for(int j = left; !(j > right || j > n); j++){
            sums[j] += numPeople;
            // cout << numPeople << "\t" << j << "\t" << sums[j] << endl;
            setHighest(&highestLoc, &highestSum, left, sums[j]);
        }
    }

    fout << highestSum << endl << highestLoc-w+1;

    fout.close();
    fin.close();

    return 0;
}
    