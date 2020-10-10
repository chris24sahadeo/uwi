////////////////////////////////////////////////////////////////////////////////
// STRUCT DEFINITIONS
////////////////////////////////////////////////////////////////////////////////
// graph edge struct
struct Edge{
    int child, weight;
    Edge *next;
};


// graph node struct
struct Node{
    string id;
    string colour;
    int parent, cost, discover, finish, inDegree;
    Edge *first;
};


// graph struct
struct Graph{
    int V;                   // number of nodes
    Node node[MAX_V+1];     // array of nodes
};


////////////////////////////////////////////////////////////////////////////////
// MAKE NEW FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
// makes a new node and returns the pointer to the node
Node newNode(string id){
    Node node;
    node.id = id;
    node.first = NULL;
    return node;
}


// makes a new edge and returns the pointer to the edge
Edge *newEdge(int child, int weight){
    Edge *edge = new Edge;
    edge->child = child;
    edge->weight = weight;
    edge->next = NULL;
    return edge;
}


// makes a new graph to hold V nodes
Graph *newGraph(int V){
    Graph *graph = new Graph;
    graph->V = V;
    return graph;
}


////////////////////////////////////////////////////////////////////////////////
// BUILD GRAPH FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
// gets the location of key int the node array
int getIndex(Graph *graph, string key){
    for(int i = 1; i <= graph->V; i++){
        if(key == graph->node[i].id)
            return i;
    }
    return -1;
}


// added edge from parent to child
void addEdge(string parent, string child, int weight, Graph *graph){
    int childIndex = getIndex(graph, child);                            // get child index
    int parentIndex = getIndex(graph, parent);                          // get parent index
    Edge *edge = newEdge(childIndex, weight);                           // make edge node

                                                                        // traversing the linked list
    Edge *prev, *curr;
    prev = curr = graph->node[parentIndex].first;
    while(curr != NULL && graph->node[curr->child].id < child){         // while we have not reached the end AND current value < key
        prev = curr;                                                        // keep checking
        curr = curr->next;
    }
    if(prev == curr){                                                   // insert at head
        edge->next = graph->node[parentIndex].first;
        graph->node[parentIndex].first = edge;
    }
    else{                                                               // insert lower down the list
        edge->next = curr;
        prev->next = edge;
    }
}


// reads from the file 'data.txt'
void buildGraph(Graph *graph){
    ifstream fin(FILENAME);                                 // open file
    fin >> graph->V;                                        // get number of nodes

                                                            // add nodes to graph
    string nodeId;
    for(int i = 1; i <= graph->V; i++){
        fin >> nodeId;
        graph->node[i] = newNode(nodeId);
    }

                                                            // add edges to graph
    string child, parent;
    int weight, numEdges;
    for(int i = 1; i <= graph->V; i++){                     // loop for V nodes
        fin >> parent >> numEdges;
        for(int j = 1; j <= numEdges; j++){                     // loop for E edges
            fin >> child >> weight;
            addEdge(parent, child, weight, graph);
        }
    }

    fin.close();
}


////////////////////////////////////////////////////////////////////////////////
// PRINT FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
void printNode(Node node){
    cout << "[" << node.id << "]";
}


void printEdge(Edge *edge, Graph *graph){
    cout << " -> (" << graph->node[edge->child].id << ", " << edge->weight << ")";
}


void printEdgeList(Edge *top, Graph *graph){
    Edge *curr = top;
    while(curr != NULL){
        printEdge(curr, graph);
        curr = curr->next;
    }
    cout << endl;
}


void printGraph(Graph *graph){
    for(int i = 1; i <= graph->V; i++){
        printNode(graph->node[i]);
        printEdgeList(graph->node[i].first, graph);
    }
}


////////////////////////////////////////////////////////////////////////////////
// DEPTH FIRST TRAVERSAL
////////////////////////////////////////////////////////////////////////////////
void DFTNode(Graph *graph, int nodeIndex){
    printNode(graph->node[nodeIndex]);                          // visit the node
    graph->node[nodeIndex].colour = VISITING;                   // mark node as VISITING

    Edge *curr = graph->node[nodeIndex].first;
    while(curr != NULL){                                        // for all nodes leaving the current node
        if(graph->node[curr->child].colour == UNVISITED){           // if the node is unvisited
            DFTNode(graph, curr->child);                                // then visit it
        }
        curr = curr->next;
    }

    graph->node[nodeIndex].colour = VISITED;                    // mark current node as visited
}


void DFTGraph(Graph *graph, int startIndex){
    for(int i = 1; i <= graph->V; i++){                         // init
        graph->node[i].colour = UNVISITED;
        graph->node[i].parent = NO_PARENT;
    }

    DFTNode(graph, startIndex);                                 // visit the node

    for(int i = 1; i <= graph->V; i++){                         // visiting any left over unvisited nodes
        if(graph->node[i].colour == UNVISITED){
            DFTNode(graph, i);
        }
    }
}


void followPath(Graph *graph, int index){
    if(index != 0){
        followPath(graph, graph->node[index].parent);
        printNode(graph->node[index]);
    }
}


void printPath(Graph *graph, string destination){
    int destinationIndex = getIndex(graph, destination);
    cout << "Path to " << destination << endl;
    followPath(graph, destinationIndex);
}
