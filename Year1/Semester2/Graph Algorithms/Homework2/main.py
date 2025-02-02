from ui import UI

if __name__ == '__main__':

    ui = UI()

    ui.run()

"""
- parse (iterate) the set of vertices
- parse (iterate) the set of outbound edges of a specified vertex (that is, provide an iterator). 
For each outbound edge, the iterator shall provide the Edge_id of the current edge 
(or the target vertex, if no Edge_id is used).
- parse the set of inbound edges of a specified vertex (as above);

- Read the graph from a text file (as an external function); see the format below.
- Write the graph from a text file (as an external function); see the format below.
- Create a random graph with specified number of vertices and of edges (as an external function).
"""
