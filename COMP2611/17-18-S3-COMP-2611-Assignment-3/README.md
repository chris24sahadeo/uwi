# 17-18-S3-COMP-2611-Assignment-3
## Graphs  

![Image of graph](https://github.com/chris24s/17-18-S3-COMP-2611-Assignment-3/blob/master/Graph.png?raw=true)


COMP2611/COMP2000 – Data Structures  
Semester 3, 2017-2018  
Assignment 3  
Graph Due: 11.55 p.m., July 7th, 2018    
  
  

Write a program to do the following:  

### Part (a)
Read a description of a graph and create its adjacency list representation.   
The information at each node consists of a string no longer than 16 characters.  
Data for the program will be supplied as follows:  

* The names of the nodes;   
Each name is a one-word string consisting of letters and/or digits, for example, London.   
This portion of the data is terminated by the ‘name’ END.   
The number of nodes is unknown beforehand.   
The nodes are to be kept in a binary search tree (BST).  

*  The description of the edges of the graph.   
The edges emanating from a node are specified by the name of the node, followed by an integer, n, (indicating the number
of edges leaving the node), followed by n pairs of values.   
Each pair consists of a node name (the child) and an positive integer weight (the cost of going from the
node to the child).   
The number of edges is unknown beforehand.   
Edges from a node must be stored in alphabetical order by node name but they may be given in
arbitrary order in the data.  
However, the names of the nodes are NOT to be stored in the adjacency list.   
Instead, the BST location of the node must be stored.   
Data is terminated by a node END.  
  
* Output the graph, listing the nodes in alphabetical order.   
Each node is followed by the name and weight of the edges leaving it (in alphabetical order).  
  
    

### Part (b)
Read the names of two nodes and give the depth-first and breadth-first traversals of
the graph from each of these nodes.   
Print only the names of the nodes.  
  
    

### Part (c)
Read the names of several nodes (one per line) and, for each node, find the minimal
cost path to all the other nodes.   
Data is terminated by END.   
Use a heap structure to maintain the priority queue.   
Output the path and the minimal cost to each node.   
Use 9999 to represent an infinite cost.  
  
 
  

## N.B.
- [ ] Data are stored in the file input.txt.  
- [ ] All output must be sent to the file output.txt.
