import copy
from graph_iterator import InboundNeighborsIterator, OutboundNeighborsIterator, VerticesIterator


class GraphException(Exception):
    pass


class Graph:

    def __init__(self, nr_vertices: int):

        self.__inbound_neighbors = {}  # Predecessors
        self.__outbound_neighbors = {}  # Successors

        self.__edge_weight = {}

        for i in range(nr_vertices):
            self.add_vertex(str(i))

    @property
    def get_number_of_vertices(self):
        return len(self.__inbound_neighbors.keys())

    @property
    def get_number_of_edges(self):
        return len(self.__edge_weight.keys())

    @property
    def get_copy(self):
        return copy.deepcopy(self)

    @property
    def get_vertices(self):

        array = []

        for x in self.__inbound_neighbors.keys():
            array.append(x)

        return array

    def get_edge(self, x, y):

        # if not self.is_edge(x, y):
        #     return None

        return self.__edge_weight[(x, y)]

    def update_edge(self, x, y, weight):

        # if not self.is_edge(x, y):
        #     return None

        self.__edge_weight[(x, y)] = weight

    def add_vertex(self, vertex):

        # if self.is_vertex(vertex):
        #     return
        self.__inbound_neighbors[vertex] = []
        self.__outbound_neighbors[vertex] = []

    def is_vertex(self, vertex):

        return vertex in self.__inbound_neighbors or vertex in self.__outbound_neighbors
        # return (vertex in list(self.__inbound_neighbors.keys())
        #         or vertex in list(self.__outbound_neighbors.keys()))

    def add_edge(self, x, y, cost: int):

        # # Check if the vertices exist
        # if not self.is_vertex(x) or not self.is_vertex(y):
        #     # Add the vertices instead?
        #     return False
        #
        # if self.is_edge(x, y):
        #     return False

        # Add y to x's outbound n.
        # Add x to y's inbound n.

        self.__inbound_neighbors[y].append(x)
        self.__outbound_neighbors[x].append(y)

        # Add the edge itself

        self.__edge_weight[(x, y)] = cost

    def is_edge(self, x, y):

        # if not self.is_vertex(x) or not self.is_vertex(y):
        #     return False

        # Check if x is an inbound n. of y
        # and if y is an outbound n. of x

        return self.is_inbound_neighbor(x, y) and self.is_outbound_neighbor(y, x)


    def is_inbound_neighbor(self, x, y):
        # TC - O(deg(y))
        return x in self.__inbound_neighbors[y]

    def is_outbound_neighbor(self, x, y):
        # TC - O(deg(y))
        return x in self.__outbound_neighbors[y]

    def get_inbound_degree(self, vertex):

        if not self.is_vertex(vertex):
            return None

        return len(self.__inbound_neighbors[vertex])

    def get_outbound_degree(self, vertex):

        if not self.is_vertex(vertex):
            return None

        return len(self.__outbound_neighbors[vertex])

    def remove_edge(self, x, y):

        # if not self.is_edge(x, y):
        #     return

        # Remove x from y's inbound n. and y from x's outbound n.
        self.__inbound_neighbors[y].remove(x)
        self.__outbound_neighbors[x].remove(y)

        # Remove the edge from the cost dictionary

        self.__edge_weight.pop((x, y))

    def remove_vertex(self, x):

        # if not self.is_vertex(x):
        #     return

        # Traverse the list of outbound neighbors
        # For each neighbor remove the vertex from the inbound dict
        # Also delete the edge

        for outbound_neighbor in self.__outbound_neighbors[x]:
            # Remove the edge
            self.__edge_weight.pop((outbound_neighbor, x))
            self.__inbound_neighbors[outbound_neighbor].remove(x)

        # Same for inbound neighbors

        for inbound_neighbor in self.__inbound_neighbors[x]:
            self.__edge_weight.pop(x, inbound_neighbor)
            self.__outbound_neighbors[inbound_neighbor].remove(x)

        # Remove the keys
        self.__inbound_neighbors.pop(x)
        self.__outbound_neighbors.pop(x)

    def get_inbound_neighbors(self, vertex):
        if not self.is_vertex(vertex):
            return None

        return copy.deepcopy(self.__inbound_neighbors[vertex])

    def get_outbound_neighbors(self, vertex):
        if not self.is_vertex(vertex):
            return None

        return copy.deepcopy(self.__outbound_neighbors[vertex])

    def inbound_neighbors(self, vertex):

        if not self.is_vertex(vertex):
            raise StopIteration

        return InboundNeighborsIterator(self, vertex)

    def outbound_neighbors(self, vertex):

        if not self.is_vertex(vertex):
            raise StopIteration

        return OutboundNeighborsIterator(self, vertex)

    def __iter__(self):

        return VerticesIterator(self)
