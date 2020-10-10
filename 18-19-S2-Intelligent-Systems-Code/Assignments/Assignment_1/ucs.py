# 816000772
# Christopher Sahadeo
# christophersahadeo@gmail.com


import collections
import read_edgelist
import pprint
pp = pprint.PrettyPrinter(indent=4)

# priority queues in python
# https://docs.python.org/2/library/heapq.html
# https://www.geeksforgeeks.org/priority-queue-in-python/
from heapq import *

# deque for closed
from collections import deque # https://docs.python.org/3/library/collections.html#collections.deque



def printLists(iteration_number, open, closed):
    print('{}. open = {}; closed = {}'.format(iteration_number, open, closed))


# When a new node v is generated
# check whether it is already in open (priority queue of tuples).
#     - If v is in open, we keep a single copy of v
#         with the smallest g-value among the two copies
#         (labeled v’ in the algorithm).

#     - If v is in closed, its new copy is discarded.
def check_for_duplicates(v, g_v, open, closed):
    if v in closed:
        return open, None
    
    #  if in open, then determine the smaller of the two, remove the one from open, heapify, return the new smaller tuple
    for (g_u, u) in open:
        if u[-1] == v:
            open.remove((g_u, u))
            heapify(open)
            smaller_g = min(g_v, g_u)
            return open, (smaller_g, v)
    
    # not in open or closed
    return open, (g_v, v)


def ucs(G, s, goal): # priority queue
    
    open = [] # open is a priority queue (list) of tuples
    heappush(open, (0, [s])) # states are added to the priority queue using the structure (<g(v)>, [<list of state_names>])
    closed = deque() # is a deque (list) of state_names
    # path_tracking = collections.defaultdict(dict)
    # parent = None

    iteration_number = 0
    printLists(iteration_number, open, closed)

    while open: # while states (nodes in graph) remain

        u_tuple = heappop(open) # pop from priority queue
        g_u = u_tuple[0]
        u = u_tuple[1] # list keeping track of path
        

        if u[-1] == goal: # if u is a goal then return path to u
            # path_tracking[X] = parent
            # print(path_tracking)
            # print('Path: {}'.format(get_path(path_tracking, start, goal)))
            return u
        
        else: # u is not goal
            u_last = u[-1]
            for v in G[u_last]: # for each child v of u
                g_v = g_u + G[u_last][v] # get cost from s to v
                open, (g_v_prime, v_prime) = check_for_duplicates(v, g_v, open, closed)
                if v_prime is not None:
                    # u.append(v_prime) # cant do it this way because u will change
                    heappush(open, (g_v_prime, u+[v_prime]))
            
            closed.append(u_last)

        # end else

        iteration_number+=1
        printLists(iteration_number, open, closed)
    
    # end while

    return 'FAIL' # no states left



G = read_edgelist.read(INPUT_FILEPATH='edgelist2.txt')

print('Graph')
pp.pprint(G)


# testing with start example from Dr K's lecture notes, 
# https://drive.google.com/file/d/1ssQ2Orax19v8z7WbKk3ixoN2XWV82mJM/view, slide 45
print('Path: {}'.format(ucs(G, 's', 'e')))
