// method from youtube hackerrank
// helper functions
int parent(int i) {return i/2;}
int leftChild(int i) {return 2*i;}
int rightChild (int i) {return 2*i+1;}

bool hasLeftChild(int i, int heapSize){return leftChild(i) <= heapSize;}
bool hasRightChild(int i, int heapSize){return rightChild(i) <= heapSize;}
bool hasParent(int i, int heapSize){parent(i) >= 1;}

void swap(int A[], int i, int j){
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}


void levelOrderTraversal(int heap[], int heapSize){
    for(int i = 1; i <= heapSize; i++){
        cout << heap[i] << '\t';
    }
    cout << endl;
}


// dr kalicharan's way
void siftDown (int newItem, int heap[], int heapSize, int i) {

    // while i has children (only need to check for left because heaps store left to right)
    while(hasLeftChild(i, heapSize)){

        // determine the larger of two children index
        int largerIdx = leftChild(i);
        if(hasRightChild(i, heapSize) && heap[rightChild(i)] > heap[leftChild(i)]){
            largerIdx = rightChild(i);
        }

        // if newItem is larger than the larger child, do nothing
        if(newItem > heap[largerIdx]){
            break;
        }

        // put larger child in i
        heap[i] = heap[largerIdx];

        // go to larger child index
        i = largerIdx;
    }

    // put new item in i
    heap[i] = newItem;
}


// puts the new item in location i and sifts down
void siftDown_v2 (int newItem, int heap[], int heapSize, int i) {

    heap[i] = newItem;                                                                  // put newItem in heap
    while(hasLeftChild(i, heapSize)){                                                   // while i has children (only need to check for left because heaps store left to right)
                                                                                            // determine the larger of two children index
        int largerIdx = leftChild(i);
        if(hasRightChild(i, heapSize) && heap[rightChild(i)] > heap[leftChild(i)]){
            largerIdx = rightChild(i);
        }
                                                                                            // if newItem is larger than the larger child, do nothing
        if(heap[i] > heap[largerIdx]){
            return;
        }
                                                                                            // else swap with the larger child and move down the tree
        swap(A, largerIdx, i);
        i = largerIdx;
    }
}


// sift up the value in A[i]
void siftUp(int A[], int n, int i){
    while(hasParent(i, n)){                     // while we have a parent
        int parentIdx = parent(i);
        if(A[i] < A[parentIdx])                     // if i is less than parent, then it is a heap, so STOP
            return;
        swap(A, i, parentIdx);                      // else swap parent and i
        i = parentIdx;                              // move up the tree
    }
}


void buildHeap_siftDown(int A[], int n){
    for(int i = n/2; i >= 1; i--){      // start at the first non leaf node and loop backwards through the tree
        siftDown(A[i], A, n, i);           // call siftDown_v2 on i
        // levelOrderTraversal(A, n);
    }
}


void buildHeap_siftUp(int A[], int n){
    if(!hasLeftChild(1))
        return;
    for(int i = 2; i <= n; i++){
        siftUp(A, i-1, i);
    }
}


bool isMaxHeap(int A[], int i, int n){
    if(!hasLeftChild(i))                                                                // BASE CASE: if it is a leaf (no children AKA no left child)
        return true;                                                                        // all leaves are heaps

    // else, we have at least a left child
    if(A[leftChild(i)] > A[i] || (hasRightChild(i, n) && A[rightChild(i)] > A[i]))      // if either of the children are bigger than the parent
        return false;                                                                       // not a heap

    return isMaxHeap(A, leftChild(i), n) && isMaxHeap(A, rightChild(i), n);             // else recur down the heap and check maxheaps at each child
}
