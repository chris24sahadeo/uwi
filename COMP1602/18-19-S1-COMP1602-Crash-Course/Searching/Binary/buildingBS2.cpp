


int binarySearch(int A[], int n, int key){
    int f = 0;                  // start 'first' at the beginning of the array
    int l = n-1;                //start 'last' at the end of the array
    while(f <= l){              //loop while i think key is in the array (that is, while first and last have not crossed over):
        int m = (f+l)/2;            // calculate middle location
        if(key > A[m])              // if key is to the right of the middle value:
            f = m+1;                    // shrink array down to the right portion
        else if(key < A[m])         // else if key is to the left of the middle value:
            l = m-1;                    // shrink array down to the left portion
        else                        // else key is equal to the middle value:
            return m;                   // found! return middle location immediately
    }
                                // if the program reaches outside the loop, it means that first and last have crossed over
    return -1;                          // so key does not exist in the array  
}
