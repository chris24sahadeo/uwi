# Intelligent Systems Assignment 1 Notes
816000772
___
[Inzamam's GitHub Repo for Assignment 1](https://github.com/InzamamRahaman/COMP3608-2019/tree/master/Assignment%201%20Sample%20Data)
___

### Libraries used
- [Pretty Print](https://docs.python.org/3/library/pprint.html) 
- [heapq](https://docs.python.org/2/library/heapq.html) for priority queue
- [deque](https://docs.python.org/3/library/collections.html#collections.deque) for stack and queues

### General Notes
- I repurposed the code given by Mr Rahaman to return the graph read from the file `edgelist.txt` to *return* the graph as read in by the `read()` function. This function is used for `dfs.py`, `bfs.py` and `ucs.py`
- I repurposed the code given by Mr Rahaman to return the graph read from the file `maze.txt` to *return* the graph as read in by the `read()` function. This function is used for `bestfs.py` and `astar.py`
- Input files `edgelist.txt` and `edgelist2.txt` are used by `dfs.py`, `bfs.py` and `ucs.py`
- Input files `maze.txt`, `maze2.txt` and `maze3.txt` are used for `bestfs.py` and `astar.py`
- Solution paths work for `dfs.py`, `bfs.py` and `ucs.py`
- Solution paths do **Not** work for `bestfs.py` or `astar.py`
