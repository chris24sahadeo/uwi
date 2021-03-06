# 816000772
# Christopher Sahadeo
# christophersahadeo@gmail.com


import collections
from collections import deque # https://docs.python.org/3/library/collections.html#collections.deque
import read_edgelist
import pprint
pp = pprint.PrettyPrinter(indent=4)


def printLists(iteration_number, open, closed):
    print('{}. open = {}; closed = {}'.format(iteration_number, open, closed))


def get_path(parent, start, goal):
    path = deque()
    curr = goal
    while(curr != start):
        path.appendleft(curr)
        curr = parent[curr]
        # print(curr)
    path.appendleft(start)
    return path


def bfs(G, start, goal): # queue
    
    open = deque(start) # initialize
    closed = deque()
    # path_tracking = collections.defaultdict(dict)
    # parent = None

    # for path finding
    parent = {}
    parent[start] = None

    iteration_number = 0
    printLists(iteration_number, open, closed)

    while open: # while states (nodes in graph) remain
        X = open.popleft() # remove LEFTMOST state X from open (in python)
        if X == goal: # if X is a goal then return path
            # path_tracking[X] = parent
            # print(path_tracking)
            # print('Path: {}'.format(get_path(path_tracking, start, goal)))
            return get_path(parent, start, goal)

        
        else:
            children = [child for child in G[X]] # generate children of X
            closed.appendleft(X) # put X on closed
            # path_tracking[X] = parent # tracking paths in a dictionary 'child': 'parent'
            # parent = X
            remaining_children = [child for child in children if child not in open and child not in closed] # if a child Y of X already open or closed then discard Y
            open.extend(remaining_children) # put remaining children on RIGHT end of open
            for child in reversed(remaining_children): 
                parent[child] = X

        # end else

        iteration_number+=1
        printLists(iteration_number, open, closed)
    
    # end while

    return 'FAIL' # no states left



G = read_edgelist.read()
pp.pprint(G)


# testing with start example from Dr K's lecture notes, 
# https://drive.google.com/file/d/1ssQ2Orax19v8z7WbKk3ixoN2XWV82mJM/view, slide 19
print(bfs(G, 'a', 'u'))
