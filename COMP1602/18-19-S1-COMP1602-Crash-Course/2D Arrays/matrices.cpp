#include <iostream>
using namespace std;


#define MAX_ROWS 5
#define MAX_COLS 5


void zeros(int A[][MAX_COLS], int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            A[i][j] = 0;
        }
    }
}


void print(int A[][MAX_COLS], int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


void transpose1(int A[][MAX_COLS], int B[][MAX_COLS], int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            B[j][i] = A[i][j];
}


void transpose2(int A[][MAX_COLS], int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < m; j++)
            int temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
}


bool isDiagonal(int A[][MAX_COLS], int n, int m){
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < m; j++)
            if(!(A[i][j] == 0 && A[j][i] == 0))
                return false;
    return true;
}


struct Sum{
    int left, right;
};


Sum sumDiagonals1(int A[][MAX_COLS], int n, int m){
    Sum s;
    s.left = 0;
    s.right = 0;
    for(int i = 0; i < n; i++){
        s.left = s.left + A[i][i];
        s.right = s.right + A[i][m-1-i];
    }
    return s;
}


Sum sumDiagonals2(int A[][MAX_COLS], int n, int m){
    Sum s;
    s.left = 0;
    s.right = 0;
    for(int i = 0, j = m-1; i < n, j >= 0; i++, j--){
        s.left = s.left + A[i][i];
        s.right = s.right + A[i][j];
    }
    return s;
}


void swapDiagonals(int A[][MAX_COLS], int n, int m){
    for(int i = 0, j = m-1; i < n, j >= 0; i++, j--){
        int temp = A[i][i];
        A[i][i] = A[i][j];
        A[i][j] = temp;
    }
}


bool isSparse(int A[][MAX_COLS], int n){
    int nonZeroCount = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(A[i][j] != 0)
                nonZeroCount++;

    return nonZeroCount < 0.2*n*n;
}




int main(){

    int n = MAX_ROWS;
    int m = MAX_COLS;

    int A[MAX_ROWS][MAX_COLS];

    zeros(A, n, m);
    print(A, n, m);



    return 0;
}
