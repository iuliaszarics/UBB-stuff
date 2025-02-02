from graph import Graph


def shortest_path(g: Graph, start, end):
    father = {}

    for vertex in g:
        father[vertex] = None

    father[start] = -1

    queue = [start]

    while len(queue):
        vertex = queue[0]
        # Remove the last element from the queue
        queue = queue[1:]

        for neigh in g.outbound_neighbors(vertex):
            if father[neigh] is None:

                father[neigh] = vertex

                if neigh == end:
                    return father

                queue.append(neigh)
