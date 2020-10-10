import collections
import pprint

pp = pprint.PrettyPrinter(indent=4)

# function adapted from mr inzamam's code to read an edge list from a text file
# input: <parnet>, <child>, <cost>
# output: returns python dictionary with parents as keys and costs as values
def read(INPUT_FILEPATH = 'edgelist.txt', DELIMITER = ','):    

    G = collections.defaultdict(dict)

    with open(INPUT_FILEPATH, 'r') as fp:
        for line in fp:
            contents = line.split(DELIMITER)
            cost = 1
            u = (contents[0])
            v = (contents[1])
            if len(contents) > 2:
                cost = float(contents[2])
            # G[u][v] = {'cost': cost, 'h': None}
            G[u][v] = cost
    
    # for child in G['a']:
    #     print(child)    
    

    # pp.pprint(G)

    return G



# read()