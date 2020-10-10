// combination of material from: https://www.geeksforgeeks.org/binary-heap/
// and: https://www.geeksforgeeks.org/greedy-algorithms-set-7-dijkstras-algorithm-for-adjacency-list-representation/
// and: https://www.youtube.com/watch?v=t0Cq6tVNRBA&t=288s

// struct defintion for array implementation of MinHeap
// Implements priority queue based on dist
struct MinHeapNode{
    int v;          // index of a vertex in the graph
    int dist;       // distance from starting vertex to v, initially all set to INF
};


// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}


struct MinHeap{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};


// creates a new MinHeap
struct MinHeap *createMinHeap(int capacity){
    struct MinHeap *newHeap = (struct MinHeap *) malloc(sizeof(struct MinHeap));
    newHeap->pos = (int *) malloc(capacity*sizeof(int));    // pointer to array of int needed for decreaseKey
    newHeap->size = 0;
    newHeap->capacity = capacity;
    newHeap->array = (struct MinHeapNode **) malloc(capacity * sizeof(struct MinHeapNode));     // pointer to array of pointers of MinHeapNode
    return newHeap;
}


// swaps two nodes, needed for min h
void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b){
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}


// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;             // assumes parent is smallest of itself and left and right child
    left = 2 * idx + 1;         // indes of left child
    right = 2 * idx + 2;        // index of right child

    // determining whether left or right child is smaller in terms of dist
    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
      smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;

    // if parent isnt already smaller both children
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is ampty or not
int isEmptyHeap(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmptyHeap(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
