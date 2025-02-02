class NeighborsIterator:

    def __init__(self, graph):
        self._index = 0
        self._neighbors = []

    def __next__(self):
        if self._index == len(self._neighbors):
            raise StopIteration

        returned_value = self._neighbors[self._index]

        self._index += 1

        return returned_value


class OutboundNeighborsIterator:

    def __init__(self, graph, vertex):
        self.__index = 0
        self.__neighbors = graph.get_outbound_neighbors(vertex)

    def __iter__(self):
        return self

    def __next__(self):
        if self.__index == len(self.__neighbors):
            raise StopIteration

        returned_value = self.__neighbors[self.__index]

        self.__index += 1

        return returned_value


class InboundNeighborsIterator:

    def __init__(self, graph, vertex):
        self.__index = 0
        self.__neighbors = graph.get_inbound_neighbors(vertex)

    def __iter__(self):
        return self

    def __next__(self):
        if self.__index == len(self.__neighbors):
            raise StopIteration

        returned_value = self.__neighbors[self.__index]

        self.__index += 1

        return returned_value


class VerticesIterator:

    def __init__(self, graph):
        # All the vertices are used as keys for the neighbor dictionaries
        self.__data = list(graph.get_vertices)

        self.__index = 0

    def __next__(self):
        if self.__index == len(self.__data):
            raise StopIteration

        next_vertex = self.__data[self.__index]

        self.__index += 1

        return next_vertex
