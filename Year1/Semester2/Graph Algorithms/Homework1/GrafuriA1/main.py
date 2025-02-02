import random

class DirectedGraph:
    def __init__(self):
        self.vertices = set()
        self.out_edges = {}
        self.in_edges = {}

    def add_vertex(self, vertex):
        self.vertices.add(vertex)
        self.out_edges[vertex] = {}
        self.in_edges[vertex] = {}
        #O(1)

    def remove_vertex(self, vertex):
        if vertex in self.vertices:
            self.vertices.remove(vertex)  #O(1)
            del self.out_edges[vertex]    #O(1)
            del self.in_edges[vertex]     #O(1)
            for v in self.vertices:       #O(x)
                if vertex in self.out_edges[v]:     #O(y1)
                    del self.out_edges[v][vertex]  #O(1)
                if vertex in self.in_edges[v]:      #O(y2)
                    del self.in_edges[v][vertex]   #O(1)
        #O(x+y)

    def add_edge(self, source, target, edge_id=None, cost=None):
        if source not in self.vertices or target not in self.vertices:
            raise ValueError("Source or target vertex not in graph")
        self.out_edges[source][target] = (edge_id, cost)   #O(1)
        self.in_edges[target][source] = (edge_id, cost)    #O(1)

    def remove_edge(self, source, target):
        if source in self.out_edges and target in self.out_edges[source]:
            del self.out_edges[source][target]  #O(1)
            del self.in_edges[target][source]   #O(1)

    def get_num_vertices(self):
        return len(self.vertices)    #O(1)

    def get_vertices(self):
        return iter(self.vertices)   #O(1)

    def has_edge(self, source, target):
        return target in self.out_edges.get(source, {})  #O(1)

    def get_edge_id(self, source, target):
        return self.out_edges.get(source, {}).get(target, (None, None))[0]   #O(1)

    def get_out_degree(self, vertex):
        return len(self.out_edges.get(vertex, {}))    #O(1)

    def get_in_degree(self, vertex):
        return len(self.in_edges.get(vertex, {}))     #O(1)

    def get_outbound_edges(self, vertex):
        return iter(self.out_edges.get(vertex, {}).keys())   #O(1)

    def get_inbound_edges(self, vertex):
        return iter(self.in_edges.get(vertex, {}).keys())    #O(1)

    def get_edge_cost(self, source, target):
        return self.out_edges.get(source, {}).get(target, (None, None))[1]     #O(1)

    def set_edge_cost(self, source, target, cost):
        if source in self.out_edges and target in self.out_edges[source]:
            self.out_edges[source][target] = (self.out_edges[source][target][0], cost)  #O(1)
            self.in_edges[target][source] = (self.out_edges[source][target][0], cost)   #O(1)

    def copy(self):
        new_graph = DirectedGraph()
        new_graph.vertices = self.vertices.copy()
        new_graph.out_edges = {v: d.copy() for v, d in self.out_edges.items()}
        new_graph.in_edges = {v: d.copy() for v, d in self.in_edges.items()}
        return new_graph

    @staticmethod
    def read_from_file(file_path):
        graph = DirectedGraph()
        with open(file_path, 'r') as file:
            for line in file:
                if line.strip():
                    source, target, cost = map(int, line.split())
                    graph.add_vertex(source)
                    graph.add_vertex(target)
                    graph.add_edge(source, target, cost=cost)
        return graph

    def write_to_file(self, file_path):
        with open(file_path, 'w') as file:
            for source in self.vertices:
                for target in self.out_edges.get(source, {}):
                    cost = self.out_edges[source][target][1]
                    file.write(f"{source} {target} {cost}\n")

    @staticmethod
    def generate_random_graph(num_vertices, num_edges):
        graph = DirectedGraph()
        for vertex in range(num_vertices):
            graph.add_vertex(vertex)
        for _ in range(num_edges):
            source = random.randint(0, num_vertices - 1)
            target = random.randint(0, num_vertices - 1)
            cost = random.randint(1, 100)  # Random cost between 1 and 100
            graph.add_edge(source, target, cost=cost)
        return graph

class UI:
    def __init__(self):
        self.graph = DirectedGraph()

    def main_menu(self):
        while True:
            print("1. Read graph from file")
            print("2. Write graph to file")
            print("3. Add vertex")
            print("4. Remove vertex")
            print("5. Add edge")
            print("6. Remove edge")
            print("7. Get number of vertices")
            print("8. Get vertices")
            print("9. Check if edge exists")
            print("10. Get out degree")
            print("11. Get in degree")
            print("12. Get outbound edges")
            print("13. Get inbound edges")
            print("14. Get edge cost")
            print("15. Set edge cost")
            print("16. Copy graph")
            print("0. Exit")
            option = input("Choose an option: ")
            if option == "1":
                file_path = input("Enter file path: ")
                self.graph = DirectedGraph.read_from_file(file_path)
            elif option == "2":
                file_path = input("Enter file path: ")
                self.graph.write_to_file(file_path)
            elif option == "3":
                vertex = int(input("Enter vertex: "))
                self.graph.add_vertex(vertex)
            elif option == "4":
                vertex = int(input("Enter vertex: "))
                self.graph.remove_vertex(vertex)
            elif option == "5":
                source = int(input("Enter source vertex: "))
                target = int(input("Enter target vertex: "))
                cost = int(input("Enter cost: "))
                self.graph.add_edge(source, target, cost=cost)
            elif option == "6":
                source = int(input("Enter source vertex: "))
                target = int(input("Enter target vertex: "))
                self.graph.remove_edge(source, target)
            elif option == "7":
                print(self.graph.get_num_vertices())
            elif option == "8":
                print(list(self.graph.get_vertices()))
            elif option == "9":
                source = int(input("Enter source vertex: "))
                target = int(input("Enter target vertex: "))
                print(self.graph.has_edge(source, target))
            elif option == "10":
                vertex = int(input("Enter vertex: "))
                print(self.graph.get_out_degree(vertex))
            elif option == "11":
                vertex = int(input("Enter vertex: "))
                print(self.graph.get_in_degree(vertex))
            elif option =="12":
                return


# Example usage:
if __name__ == "__main__":
    random_graph = DirectedGraph.generate_random_graph(7, 20)
    random_graph.write_to_file("random_graph1.txt")

    graph_from_file = DirectedGraph.read_from_file("random_graph1.txt")
    UI().main_menu()
    copied_graph = graph_from_file.copy()

    copied_graph.write_to_file("modified_graph.txt")
