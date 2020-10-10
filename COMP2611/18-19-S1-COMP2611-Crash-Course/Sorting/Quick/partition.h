void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}


// puts pivot in its place
int partition_v1(int A[], int startIndex, int endIndex){
    int pivotLocation = startIndex;                         // consider the startIndex of the array as the pivotLocation
    int lastSmallerIndex = pivotLocation;                   // consider the pivotLocation the initial lastSmallerIndex

    for(int i = pivotLocation+1; i <= endIndex; i++)        // loop from pivotLocation+1 to endIndex
        if(A[i] < A[pivotLocation])                             // if we find a value that is smaller than the pivot value
            swap(A, ++lastSmallerIndex, i);                         // FIRST increment lastSmallerIndex and, THEN swap with the smaller value we found

    swap(A, pivotLocation, lastSmallerIndex);               // swap pivot and lastSmallerIndex
    return lastSmallerIndex;                                // return the division point (dp)
}


// does not put pivot in its place
int partition_v2(int A[], int left, int right){
    int pivotValue = A[left];                               // make left the pivot value
    while(left <= right){                                   // while left and right have not crossed
        while(A[left] < pivotValue) left++;                     // go right until we find a value greater than or equal to pivot
        while(A[right] > pivotValue) right--;                   // go left until we find a value less than or equal to pivot
        if(left <= right) swap(A, left++, right--);             // swap left and right values THEN increment left and decrement right
    }
    return left;                                            // this is our division point: all values from [1..left-1] are smaller than [l]
}
