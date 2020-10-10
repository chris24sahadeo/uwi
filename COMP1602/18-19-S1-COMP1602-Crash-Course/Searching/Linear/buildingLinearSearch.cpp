

int linearSearchUnsorted(int A[], int n, int key){
    int i = 0;                      // start at the beginning of the array
    while(i < n && A[i] != key)     // while (we haven't reached the end of the array) AND our current value is not key:
        i++;                            //go to the next location
    if(A[i] == key)                 // if current value that we are examining is key:
        return i;                       // we are done, return the LOCATION of key
    else                            // else we went outside the bounds of the array (i is not less than n):
        return -1;                      //not found
}


int linearSearchSorted(int A[], int n, int key){
    int i = 0;                      // start at the beginning of the array
    while(i < n && A[i] < key)     // while (we haven't reached the end of the array) AND our current value is not key:
        i++;                            //go to the next location
    if(A[i] == key)                 // if current value that we are examining is key:
        return i;                       // we are done, return the LOCATION of key
    else                            // else we went outside the bounds of the array (i is not less than n):
        return -1;                      //not found
}
