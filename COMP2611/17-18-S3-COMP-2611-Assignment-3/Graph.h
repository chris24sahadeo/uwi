struct AdjacencyListNode{
    int child, weight;
    struct AdjacencyListNode *next;
};


struct AdjacencyList{
    struct BSTNode *nameNode;
    struct AdjacencyListNode *head;
};


struct Graph{
    int V;
    struct AdjacencyList *array;
};


// makes a new AdjacencyListNode
struct AdjacencyListNode *newAdjacencyListNode(int child, int weight){
    struct AdjacencyListNode *newNode = (struct AdjacencyListNode *) malloc(sizeof(struct AdjacencyListNode));
    newNode->child = child;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


// adds address of names in BST to the graph's AdjacencyList
// performs inorder traversal to obtain alphabetical order
int populateAdjacencyListWithBSTNodeNames(struct BSTNode *root, struct Graph *graph, int location){

    if(root == NULL) return location;
    location = populateAdjacencyListWithBSTNodeNames(root->left, graph, location);
    graph->array[location].nameNode = root;
    location++;
    location = populateAdjacencyListWithBSTNodeNames(root->right, graph, location);

}


// traverses the graphs adj list and prints names to the screen
void printGraphAdjacencyList(struct Graph *graph){
    for(int i = 0; i < graph->V; i++){
        printf("%s   ", graph->array[i].nameNode->name);
    }
    printf("\n\n");
}



// inits a blank graph, and populates with pointers to names in the BST
struct Graph *initGraph(int V, struct BSTNode *BSTOfNodeNames){

    // makes empty graph
    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    graph->array = (struct AdjacencyList *) malloc(V*sizeof(struct AdjacencyList));
    graph->V = V;
    for(int i = 0; i < V; i++){
        graph->array[i].head = NULL;
        graph->array[i].nameNode = NULL;
    }

    // tesi print of AdjacencyList
    // printGraphAdjacencyList(graph);

    // performs inorder traveral of BST and populates adj list with addresses of names from BST
    populateAdjacencyListWithBSTNodeNames(BSTOfNodeNames, graph, 0);

    // tesi print of AdjacencyList
    printGraphAdjacencyList(graph);

    return graph;

}


// adds a single edge to an undirected graph in alphabetical order
void addEdgeInOrder(struct Graph *graph, int parent, int child, int weight){

    struct AdjacencyListNode *newNode = newAdjacencyListNode(child, weight);

    struct AdjacencyListNode *curr = graph->array[parent].head;
    struct AdjacencyListNode *prev = NULL;
    while(curr != NULL && newNode->child > curr->child){
        prev = curr;
        curr = curr->next;
    }
    newNode->next = curr;
    if(prev != NULL)
        prev->next = newNode;
    else
        graph->array[parent].head = newNode;

}


// performs a binary search on the graphs adj list for a word key
int binarySearch(struct Graph *graph, char key[]){
    int f = 0, l = graph->V;
    while(f<=l){
        int m = (f+l)/2;
        if(strcmp(key, graph->array[m].nameNode->name) < 0) l = m-1;
        else if(strcmp(key, graph->array[m].nameNode->name) == 0) return m;
        else f = m+1;
    }
    return -1;
}


// prints entire graph with edges and weights
void printGraph(struct Graph *graph){
    for(int i = 0; i < graph->V; i++){
        printf("%s -> ", graph->array[i].nameNode->name);
        struct AdjacencyListNode *curr = graph->array[i].head;
        while(curr != NULL){
            printf("(%s, %d) ", graph->array[curr->child].nameNode->name, curr->weight);
            curr = curr->next;
        }
        printf("\n");
    }
}


// prints entire graph to file with edges and weights
void printGraphToFile(FILE **fout, struct Graph *graph){

    fprintf(*fout, "==================================Part (a)==================================\nAdjacency List Representation of Graph:\n");

    for(int i = 0; i < graph->V; i++){
        fprintf(*fout, "%s -> ", graph->array[i].nameNode->name);
        struct AdjacencyListNode *curr = graph->array[i].head;
        while(curr != NULL){
            fprintf(*fout, "(%s, %d) ", graph->array[curr->child].nameNode->name, curr->weight);
            curr = curr->next;
        }
        fprintf(*fout, "\n");
    }
}


// continues reading from the file and populates the graph with Edges
void addEdgesFromFile(FILE **fin, struct Graph *graph){

    // get words from the FILE
    char parentName[MAX_CHAR_PER_WORD+1];
    fscanf(*fin, "%s", parentName);     // get parent
    capitalize(parentName);
    while(strcmp(parentName, FILE_SENTINEL) != 0){

        // search graph for location of parentName address in adj list
        int parentLocation = binarySearch(graph, parentName);

        // get number of Edges
        int E;
        fscanf(*fin, "%d", &E);

        // loop to get children names and weights
        char childName[MAX_CHAR_PER_WORD+1];
        int weight;
        for(int i = 0; i < E; i++){
            fscanf(*fin, "%s", childName);
            capitalize(childName);
            fscanf(*fin, "%d", &weight);

            // search graph for location of child address in adj list
            int childLocation = binarySearch(graph, childName);

            // add edge to graph in alphabetical order
            addEdgeInOrder(graph, parentLocation, childLocation, weight);

        }


        fscanf(*fin, "%s", parentName);
        capitalize(parentName);
    }

    // test print to screen
    // printGraph(graph);

}


// recursion for DFS
void DFSUtil(FILE **fout, struct Graph *graph, int currentLocation, bool visited[]){

    // set to currentLocation to visited
    visited[currentLocation] = true;

    // add to stack (DONT NEED)

    // print
    fprintf(*fout, "%s   ", graph->array[currentLocation].nameNode->name);
    // printf("%s -> ", graph->array[currentLocation].nameNode->name);

    // iterate through adj list nodes
    struct AdjacencyListNode *curr = graph->array[currentLocation].head;
    while(curr != NULL){
        if(!visited[curr->child])
            DFSUtil(fout, graph, curr->child, visited);
        curr = curr->next;
    }

    // pop from stack (DONT NEED)

}


// DFS
void DFS(FILE **fout, struct Graph *graph, char start[]){

    fprintf(*fout, "\n\nDFS:\n");

    // stack to keep track of which node we are dealing with (DON'T NEED)

    // visited array
    bool visited[graph->V];
    for(int i = 0; i < graph->V; i++)
        visited[i] = false;

    // find start point
    int startingLocation = binarySearch(graph, start);

    // call utility function
    DFSUtil(fout, graph, startingLocation, visited);

    // fprintf(*fout, "\n\n");

}


// BFS
void BFS(FILE **fout, struct Graph *graph, char start[]){

    fprintf(*fout, "\n\nBFS:\n");

    // visited array
    bool visited[graph->V];
    for(int i = 0; i < graph->V; i++)
        visited[i] = false;

    // find start point
    int startingLocation = binarySearch(graph, start);

    // queue to keep track of which node we are dealing with (DON'T NEED)
    struct Queue *queue = createQueue();

    // add start node to Queue
    enQueue(queue, startingLocation);
    visited[startingLocation] = true;

    while(!isEmpty(queue)){

        // display the vertex from the Queue front
        int currentLocation = queue->front->key;
        fprintf(*fout, "%s  ", graph->array[currentLocation].nameNode->name);
        deQueue(queue);

        struct AdjacencyListNode *curr = graph->array[currentLocation].head;
        while(curr != NULL){
            if(!visited[curr->child]){
                visited[curr->child] = true;
                enQueue(queue, curr->child);
            }
            curr = curr->next;
        }

    }

}


// prints dijkstra's path
void printPath(FILE **fout, struct Graph *graph, int parent[], int i){
    if(parent[i] == -1) return;
    printPath(fout, graph, parent, parent[i]);
    fprintf(*fout, "%s ", graph->array[i].nameNode->name);
}


// Dijkstra's
// for dijkstras
// A utility function used to print the solution
void printArr(FILE **fout, struct Graph *graph, int dist[], int parent[], int n, int src)
{
    fprintf(*fout, "KEY: [DESTINATION] [COST] [PATH]\n");
    for (int i = 0; i < n; ++i){
        fprintf(*fout, "[%s] [%d] [%s ", graph->array[i].nameNode->name, dist[i], graph->array[src].nameNode->name);
        if(dist[i] != INF){
            // fprintf(*fout, "[");
            printPath(fout, graph, parent, i);
            fprintf(*fout, "]");
        }
        else
            fprintf(*fout, " [NO PATH] ");
        fprintf(*fout, "\n");
    }
}


// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(FILE **fout, struct Graph* graph, int src)
{

    fprintf(*fout, "\n\nDijkstra's starting from %s\n", graph->array[src].nameNode->name);

    int V = graph->V;// Get the number of vertices in graph
    int dist[V];      // dist values used to pick minimum weight edge in cut
    int parent[V];  // for printing paths

    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);

    // Initialize min heap with all vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
        parent[v] = -1;
    }

    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmptyHeap(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number

        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjacencyListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->child;

            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
            if (isInMinHeap(minHeap, v) && dist[u] != INF && pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                parent[v] = u;
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // print the calculated shortest distances
    printArr(fout, graph, dist, parent, V, src);
}
