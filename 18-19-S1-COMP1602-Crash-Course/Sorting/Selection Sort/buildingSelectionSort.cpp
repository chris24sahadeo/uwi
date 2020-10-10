


void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}


int findSmallestLocationInUnsortedPortion(int A[], int start, int n){
    int s = start;                          // assume that the start location has the smallest value in unsorted portion
    for(int i = start+1; i < n; i++){       // check the REST of the unsorted portion for any value that may be smaller
        if(A[i] < A[s]){                        // if i find some values less than what i currently believe to be the smallest
            s = i;                                  // then update smallest location
        }
    }
    return s;
}


void selectionSort(int A[], int n){
    // start i at zero
    // we write i < n-1 because the last step automatically sorts the last 2 locations
    for(int i = 0; i < n-1; i++){
        int s = findSmallestLocationInUnsortedPortion(A, i, n);
        swap(A, i, s);
    }
}
