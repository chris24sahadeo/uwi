from collections import defaultdict
# import pprint
# pp = pprint.PrettyPrinter(indent=4)


def is_valid_coord(t, n):
    x = t[0]
    y = t[1]
    test1 = x >= 0
    test2 = x < n
    test3 = y >= 0
    test4 = y < n
    return (test1 and test2 and test3 and test4)


# indices for this function starts at 1
def taxi_cab_distance(current_row, current_column, goal_row, goal_column):
    return abs(current_row - goal_row) + abs(current_column - goal_column)


def read(END_X, END_Y, INPUT_FILE = 'maze.txt'):    

    G = defaultdict(lambda: defaultdict(dict)) # handling the case where accessing a key that doesnt exist, automaticallly adds a new dict (nested)
    h = {}

    fp = open(INPUT_FILE, 'r')
    data = fp.read()
    fp.close()

    data = data.split('\n') # creating nested list (2d array)

    # assuming square maze only
    n = len(data)

    # goal state
    # END_X = 1
    # END_Y = 4

    for i in range(n):
        for j in range(n):
            if data[i][j] != 'X': # if square can be occupied, we ommit all the impassable (wall) squares
                coords = [(i-1,j),(i+1,j),(i,j+1),(i,j-1)] # generate surrounding coordinates: L R U D, EXCLUDING THE POSSIBILITY OF MOVING DIAGONALLY
                coords = list(filter(lambda x: is_valid_coord(x, n), coords)) # eliminate out of bounds squares
                for x,y in coords: 
                    if data[x][y] != 'X':
                        G[(i+1,j+1)][(x+1,y+1)]['cost'] = 1 # +1 on the index for real-word maze grid offset
                h[(i+1,j+1)] = taxi_cab_distance(i+1, j+1, END_X, END_Y) # taxi cab distance

    G = dict(G)
    G = {k:dict(v) for k, v in G.items()}
    return G, h




