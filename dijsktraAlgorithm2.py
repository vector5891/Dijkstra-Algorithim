
class Graph(object):
    def __init__(self):
        self.nodes = set()
        self.edges = {}
        self.cost = {}
    
    def addNode(self, value):
        #total number of nodes in the graph
        self.nodes.add(value)

    def addEdge(self, src, dest, distance):
        #uses v0 and v1 and their edge values to construct the connections
        self._add_edge(src, dest, distance)
        self._add_edge(dest, src, distance)
 
    def _add_edge(self, src, dest, distance):
        #used to construct the graph
        self.edges.setdefault(src, [])
        self.edges[src].append(dest)
        self.cost[(src, dest)] = distance
 

def dijkstra(graph, src):
    visited = {src: 0}        ##initially keeps track of all visited nodes, starts at 0
    currentNode = src         ##starts at source(src)
    path = {}                 ##used to store the path
    nodes = set(graph.nodes)  ##takes in a complete list of nodes from the path
    
    while nodes:              ##iterates through list of nodes in the graph
        min_node = None
        for node in nodes:    ##iterates through list of nodes in the graph
            if node in visited:         ##checks if node has been visited
                if min_node is None:    ##compares node path with the their edge values
                    min_node = node     ##if less, then set as new lowest
                elif visited[node] < visited[min_node]:       ##compares visted node with current lowest node edge
                    min_node = node
        if min_node is None:
            break
        nodes.remove(min_node)
        cur_wt = visited[min_node]
        
        for edge in graph.edges[min_node]:
            wt = cur_wt + graph.cost[(min_node, edge)]
            if edge not in visited or wt < visited[edge]:
                visited[edge] = wt
                path[edge] = min_node          ##appends the edge with lowest cost to the path
    return visited, path
 
def shortestPath(graph, src, dest):
    cost, paths = dijkstra(graph, src)        ##calls dijkstra's algorithm
    route = [dest]                            ##initiate with the destination
    path = []
    while dest != src:
        route.append(paths[dest])            ##append the edge path into the route of lowest cost
        dest = paths[dest]
 
    route.reverse()
    return route                             ##once the destination is reached, return the route
 
 
if __name__ == '__main__':
    """using Graph 1 from the given project"""
    # a = 1, b = 2, c = 3, ....... l = 12
    # https://github.com/DzouOnionGardener/dijkstra-s-Algorithm/blob/master/DSC_0001.JPG?raw=true
    graph1 = Graph()
    graph1.nodes = set(range(1, 13))
    ##graph construction via edges
    #edges from source vertex0 to destination vertex1 and edge value
    graph1.addEdge(1, 2, 3)  #a to b
    graph1.addEdge(1, 3, 5)  #a to c
    graph1.addEdge(1, 4, 4)  #a to d
    graph1.addEdge(2, 5, 3)  #b to e
    graph1.addEdge(2, 6, 6)  #b to f
    graph1.addEdge(3, 4, 2)  #c to d
    graph1.addEdge(3, 7, 4)  #c to g
    graph1.addEdge(4, 8, 5)  #d to h
    graph1.addEdge(4, 5, 1)  #d to e
    graph1.addEdge(5, 6, 2)  #e to f
    graph1.addEdge(5, 9, 4)  #e to i
    graph1.addEdge(6, 10, 5) #f to j
    graph1.addEdge(7, 11, 6) #g to k
    graph1.addEdge(7, 8, 3)  #g to h
    graph1.addEdge(8, 9, 6)  #h to i
    graph1.addEdge(8, 11, 7) #h to k
    graph1.addEdge(9, 10, 3) #i to j
    graph1.addEdge(9, 12, 5) #i to l
    graph1.addEdge(10, 12, 9)#j to l
    graph1.addEdge(11, 12, 8)#k to l

    source = input("enter start/source node: ")
    destination = input("enter end/destination node: ")
    path = shortestPath(graph1, source, destination)

    print ("the shorest path from %s to %s is %s" % (source,destination, path))
