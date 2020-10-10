# 816000772
# Christopher Sahadeo
# christophersahadeo@gmail.com


import read_maze
import collections
import pprint
pp = pprint.PrettyPrinter(indent=4)


# priority queues in python
# https://docs.python.org/2/library/heapq.html
# https://www.geeksforgeeks.org/priority-queue-in-python/
from heapq import *

# deque for closed
from collections import deque # https://docs.python.org/3/library/collections.html#collections.deque


def printLists(iteration_number, open, closed, g):
    print('{}. open = {}; closed = {}; g = {}'.format(iteration_number, open, closed, g))
    print('\n\n')


# # h is a dict of heuristic values
# # state is a tuple (x, y)
# def calc_h(h, state):
#     return h[state];


# # current and child ar tuples (x, y)
# def calc_g(current, child):



# def calc_f(g, h):


# NOTE: each state (square in maze) can have MULTIPLE PARENTS
def get_path(parent, start, goal):
    path = deque()
    curr = goal
    while(curr != start):
        path.appendleft(curr)
        curr = parent[curr]
        print(curr)
    path.appendleft(start)
    return path
        


def astar(G, h, start, goal): # f(n) = g(n) + h(n)

    # initialize
    open = [] # Priority queue STRUCTURE: (f((x,y)), (x,y)) ... ordered by f
    heappush(open, (h[start], start)) # priority queue, init with start, NB: g(start) = 0 => f(n) = h(n)
    # G[start]['g'] = 0 # init start g value OLD METHOD
    closed = deque()
    g = {}
    g[start] = 0 # init start g value

    parent = {}
    parent[start] = None

    iteration_number = 0
    printLists(iteration_number, open, closed, g)

    while open:
        X = heappop(open) # remove leftmost state X from open 
        f_X = X[0]
        X = X[1]      
        
        # if X is a goal then return the path from Start to X
        if X == goal: 
            # return get_path(parent, start, goal)
            return 'SUCCESS'
        
        # else generate the children of X
        else:
            for child in G[X]: # https://stackoverflow.com/questions/10756427/loop-through-all-nested-dictionary-values

                parent[child] = X
                # G[child]['g'] = G[X]['g'] + G[X][child]['cost'] # get g value for child using the g value for parent (stored in graph) OLD
                # old_g_child = 
                new_g_child = g[X] + G[X][child]['cost']

                if child not in [state for (f, state) in open] and child not in closed: # case 1: child is not on open or closed
                    g[child] = new_g_child
                    f_child = g[child] + h[child] # assign child a heuristic value f(n) = g(n) + h(n)
                    open.append((f_child, child)) # add child to open

                elif child in [state for (f, state) in open]: # case 2: child is already on open
                    if new_g_child < g[child]: # if child was reached by a shorter path (g value only, not f!)
                        f_child = g[child] + h[child]
                        open.remove((f_child, child)) # then give the state on open the shorter path (new f value) AND HEAPIFY (done below)
                        g[child] = new_g_child
                        f_child = g[child] + h[child] # assign child a heuristic value f(n) = g(n) + h(n)                    
                        open.append((f_child, child))
                
                elif child in closed: # case 3: child is already on closed
                    if new_g_child < g[child]: # if child was reached by a shorter path
                        closed.remove(child) # then remove the state from closed
                        g[child] = new_g_child
                        f_child = g[child] + h[child] # assign child a heuristic value f(n) = g(n) + h(n)
                        open.append((f_child, child))# add child to open

                # end case, end for
                
            # put X on closed
            closed.append(X)

            # reorder states on open by heuristic meric (best leftmost) (HEAPIFY)
            heapify(open)

        # end else

        iteration_number+=1
        printLists(iteration_number, open, closed, g)

    # end while

    return 'FAIL' # (open is empty and goal was not reached)

        

# graph structure slightly modified from inzamam's method
G, h = read_maze.read(INPUT_FILE="maze2.txt", END_X=8, END_Y=8)

print("Graph")
pp.pprint(G)

print("H estimates")
pp.pprint(h)

start = (4, 3)
end = (8, 8)
print('path: {}'.format(astar(G, h, start, end)))