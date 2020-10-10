

int binarySearch(int A[], int n){
    int f = 0;                  // start first at the beginning of the array
    int l = n-1;                // start last at the end of the array 
    while(f <= l){              // while first and last have not crossed over
        int m = (f+l)/2;            // calculate middle
        if(key < A[m])              // if key is to the left of the middle value
            l = m-1;                    // shrink the array to the left
        else if(key == A[m])        // else if key is equal to the middle value
            return m;                   // we are done, key found
        else                        // else the only other possibility is key is to the right of middle value
            f = m+1;                    // so shrink array to the right
    }
    return -1;                  // if first and last cross over then key is not found
}
