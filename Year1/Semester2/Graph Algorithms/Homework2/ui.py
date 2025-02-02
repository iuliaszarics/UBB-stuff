import random
# PB 3 pt lab 2
from graph import *
from problem import shortest_path


class UI:

    def __init__(self):
        self.__commands = {
            "1": self.__ui_add_vertex,
            "2": self.__ui_remove_vertex,
            "3": self.__ui_get_inbound_degree,
            "4": self.__ui_get_outbound_degree,
            "5": self.__ui_add_edge,
            "6": self.__ui_remove_edge,
            "7": self.__ui_update_edge,
            "8": self.__ui_check_edge,
            "9": self.__ui_print_graph,
            "10": self.__ui_read_graph_file,
            "11": self.__ui_print_graph_file,
            "12": self.__ui_generate_random_graph,
            "13": lambda: print(f"The graph has {self.__graph.get_number_of_vertices} vertices."),
            "14": lambda: print(f"The graph has {self.__graph.get_number_of_edges} edges."),
            "15": self.__ui_shortest_path,
        }
        self.__graph = Graph(0)

    @staticmethod
    def __get_user_input(msg):
        return input(msg).strip()

    @staticmethod
    def __print_menu():
        print("Graph menu")
        print()
        print("1. Add vertex")
        print("2. Remove vertex")
        print("3. Inbound Degree")
        print("4. Outbound Degree")
        print("Edges operations")
        print("6. Remove edge")
        print("7. Update edge")
        print("8. Check edge")
        print("9. Print the graph")
        print("10. Read graph from a file")
        print("11. Print graph in a file")
        print("12. Generate random graph")
        print("13. Get number of vertices")
        print("14. Get number of edges")
        print("15. Shortest path between 2 vertices")
        print("0. Exit")

    def run(self):

        while True:

            self.__print_menu()
            user_input = self.__get_user_input(">")

            if user_input == "":
                continue

            if user_input == "0":
                return

            if user_input in self.__commands.keys():

                try:
                    self.__commands[user_input]()

                except Exception as ex:
                    print(ex)

            else:
                print("Invalid input, try again!")

            print()

    def __ui_add_vertex(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        vertex = self.__get_user_input("Vertex: ")

        if self.__graph.is_vertex(vertex):
            raise GraphException("Vertex already exists!")

        self.__graph.add_vertex(vertex)

        print("Vertex added successfully!")

    def __ui_remove_vertex(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        vertex = self.__get_user_input("Vertex: ")

        if not self.__graph.is_vertex(vertex):
            raise GraphException("Vertex does not exist!")

        self.__graph.remove_vertex(vertex)

        print("Vertex removed successfully!")

    def __ui_get_inbound_degree(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        vertex = self.__get_user_input("Vertex: ")

        if not self.__graph.is_vertex(vertex):
            raise GraphException("Vertex does not exist!")

        print(f"The inbound degree of vertex {vertex} is {self.__graph.get_inbound_degree(vertex)}")

    def __ui_check_edge(self):
        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        x = self.__get_user_input("Vertex x: ")
        y = self.__get_user_input("Vertex y: ")

        if not self.__graph.is_vertex(x) or not self.__graph.is_vertex(y):
            raise GraphException("Vertices do not exist!")

        if self.__graph.is_edge(x, y):
            print(f"The edge ({x},{y}) exists and has a weight of {self.__graph.get_edge(x, y)}")
        else:
            print("The edge does not exist!")

    def __ui_get_outbound_degree(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        vertex = self.__get_user_input("Vertex: ")

        if not self.__graph.is_vertex(vertex):
            raise GraphException("Vertex does not exist!")

        print(f"The outbound degree of vertex {vertex} is {self.__graph.get_outbound_degree(vertex)}")

    def __ui_add_edge(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        x = self.__get_user_input("Vertex x: ")
        y = self.__get_user_input("Vertex y: ")

        if not self.__graph.is_vertex(x) or not self.__graph.is_vertex(y):
            raise GraphException("Vertices do not exist!")

        if self.__graph.is_edge(x, y):
            raise GraphException("Edge already exists!")

        weight = int(self.__get_user_input("Weight: "))

        self.__graph.add_edge(x, y, weight)

        print("Edge added successfully!")

    def __ui_remove_edge(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        x = self.__get_user_input("Vertex x: ")
        y = self.__get_user_input("Vertex y: ")

        if not self.__graph.is_vertex(x) or not self.__graph.is_vertex(y):
            raise GraphException("Vertices do not exist!")

        if not self.__graph.is_edge(x, y):
            raise GraphException("Edge does not exist!")

        self.__graph.remove_edge(x, y)

        print("Edge removed successfully!")

    def __ui_update_edge(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        x = self.__get_user_input("Vertex x: ")
        y = self.__get_user_input("Vertex y: ")

        if not self.__graph.is_vertex(x) or not self.__graph.is_vertex(y):
            raise GraphException("Vertices do not exist!")

        if not self.__graph.is_edge(x, y):
            raise GraphException("Edge does not exist!")

        weight = int(self.__get_user_input("New weight: "))

        self.__graph.update_edge(x, y, weight)

        print("Edge updated successfully!")

    def __ui_print_graph(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        print(f"The graph has {self.__graph.get_number_of_vertices} vertices.")

        for vertex in self.__graph:
            print(f"The vertex {vertex} has the following outbound neighbors: ")

            for neighbor in self.__graph.outbound_neighbors(vertex):
                print(f"{neighbor} - the edge ({vertex},{neighbor}) "
                      f"has a weight of {self.__graph.get_edge(vertex, neighbor)}")
            print()

    def __ui_read_graph_file(self):

        file_path = self.__get_user_input("Please enter the path to the file: ")

        file_path = "./" + file_path

        with open(file_path, "r") as file:
            n, m = [int(i.strip()) for i in file.readline().split()]

            self.__graph = Graph(n)

            for i in range(m):
                x, y, weight = [(i.strip()) for i in file.readline().split()]
                self.__graph.add_edge(x, y, int(weight))

        print("Graph read successfully!")

    def __ui_print_graph_file(self):

        if self.__graph.get_number_of_vertices == 0:
            raise GraphException("There is no graph")

        file_path = self.__get_user_input("Please enter the path to the file: ")

        file_path = "./" + file_path

        with open(file_path, "w") as file:
            file.write(f"{self.__graph.get_number_of_vertices} {self.__graph.get_number_of_edges}\n")

            for vertex in self.__graph:
                for neighbor in self.__graph.outbound_neighbors(vertex):
                    file.write(f"{vertex} {neighbor} {self.__graph.get_edge(vertex, neighbor)}\n")

        print("Graph written successfully!")

    def __ui_generate_random_graph(self):

        n = int(self.__get_user_input("Number of vertices: "))
        m = int(self.__get_user_input("Number of edges: "))

        if m > n * (n - 1):
            raise GraphException("Too many edges!")

        self.__graph = Graph(n)

        for i in range(m):

            while True:
                x = str(random.randint(0, n - 1))
                y = str(random.randint(0, n - 1))

                if x == y:
                    continue

                if self.__graph.is_edge(x, y):
                    continue

                self.__graph.add_edge(x, y, random.randint(0, 100))

                break

        print("Graph generated successfully!")

    def __ui_shortest_path(self):

        start = self.__get_user_input("Start vertex: ")
        end = self.__get_user_input("End vertex: ")

        if not self.__graph.is_vertex(start) or not self.__graph.is_vertex(end):
            raise GraphException("Vertices do not exist!")

        father = shortest_path(self.__graph, start, end)

        if father is None:
            print("There is no path between the two vertices!")
            return

        path = []
        length = 0
        n = end

        while n != start:
            path.append(n)
            length += 1
            n = father[n]

        path.append(start)
        path.reverse()

        print(f"The path is: {path}")
