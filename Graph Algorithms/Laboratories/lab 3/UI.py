from Graph import DirectGraph
import random


class UI:
    def __init__(self):
        self.__graph = None

    def __ui_read_graph_from_file(self):
        """
        Function that reads a graph from a file
        :return:
        """
        file_name = input("Insert name of the file:\n>>>")
        with open(file_name, "r") as f:
            line = f.readline()
            line = line.strip()
            parts = line.split()
            no_of_vertices = int(parts[0])
            no_of_edges = int(parts[1])
            graph = DirectGraph(no_of_vertices)
            for _ in range(no_of_edges):
                line = f.readline()
                line = line.strip()
                parts = line.split()
                graph.add_edge(int(parts[0]), int(parts[1]), int(parts[2]))
        self.__graph = graph

    def __ui_create_simple_graph(self):
        """
        Function that creates a simple graph with 5 vertices and 6 edges (not random)
        :return:
        """
        graph = DirectGraph(5)
        graph.add_edge(0, 1, 5)
        graph.add_edge(0, 2, 20)
        graph.add_edge(1, 3, 30)
        graph.add_edge(1, 2, 10)
        graph.add_edge(2, 3, 5)
        self.__graph = graph

    def __ui_create_random_graph(self):
        """
        Function that creates a random graph
        :return:
        """
        no_of_vertices = int(input("Insert number of vertices:\n>>>"))
        no_of_edges = int(input("Insert number of edges:\n>>>"))
        while no_of_edges > no_of_vertices**2:
            print("Too many edges!\nTry again!\n")
            no_of_edges = int(input("Insert number of edges:\n>>>"))
        graph = DirectGraph(no_of_vertices)
        while no_of_edges:
            initial_vertex = random.choice(list(range(0, no_of_vertices)))
            final_vertex = random.choice(list(range(0, no_of_vertices)))
            cost = random.choice(list(range(-1000, 1000)))
            if graph.is_edge(initial_vertex, final_vertex):
                continue
            graph.add_edge(initial_vertex, final_vertex, cost)
            no_of_edges -= 1
        self.__graph = graph

    def __ui_print_dictionaries(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        in_dict = self.__graph.get_in_dict().items()
        out_dict = self.__graph.get_out_dict().items()
        cost_dict = self.__graph.get_cost_dict().items()
        print("Inbound dictionary:")
        for item in in_dict:
            print(item[0], "<---", item[1])
        print("\nOutbound dictionary:")
        for item in out_dict:
            print(item[0], "--->", item[1])
        print("\nCost dictionary: ")
        for item in cost_dict:
            print(item[0], "--->", item[1])

    @staticmethod
    def __ui_print_menu():
        print("Menu:\n"
              "'0'  to exit.\n"
              "'1'  to create a simple graph.\n"
              "'2'  to create a random graph.\n"
              "'3'  to read a graph from a file.\n"
              "'4'  to print the graph's dictionaries.\n"
              "'5'  to add an edge.\n"
              "'6'  to add a vertex.\n"
              "'7'  to remove an edge.\n"
              "'8'  to remove a vertex.\n"
              "'9'  to get the number of vertices.\n"
              "'10' to parse the set of vertices.\n"
              "'11' to parse the outbound neighbours of a vertex.\n"
              "'12' to parse the inbound neighbours of a vertex.\n"
              "'13' to get the in degree of a vertex.\n"
              "'14' to get the out degree of a vertex.\n"
              "'15' to get the cost of an edge.\n"
              "'16' to set the cost of an edge.\n"
              "'17' to copy the graph.\n"
              "'18' to find shortest path between two vertices with backward bfs\n"
              "'19' to find the lowest cost walk between two vertices with Bellman-Ford\n"
              )

    def __ui_add_edge(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        initial_vertex = int(input("Insert initial vertex:\n>>>"))
        final_vertex = int(input("Insert final vertex:\n>>>"))
        cost = int(input("Insert the cost of the edge:\n>>>"))
        self.__graph.add_edge(initial_vertex, final_vertex, cost)

    def __ui_add_vertex(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        vertex = int(input("Insert vertex:\n>>>"))
        self.__graph.add_vertex(vertex)

    def __ui_remove_edge(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        initial_vertex = int(input("Insert initial vertex:\n>>>"))
        final_vertex = int(input("Insert final vertex:\n>>>"))
        self.__graph.remove_edge(initial_vertex, final_vertex)

    def __ui_remove_vertex(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        vertex = int(input("Insert vertex:\n>>>"))
        self.__graph.remove_vertex(vertex)

    def __ui_get_no_of_vertices(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        print(self.__graph.get_no_of_vertices())

    def __ui_parse_set_of_vertices(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        for x in self.__graph.parse_set_of_vertices():
            print("Vertex: ", x)
            print("Inbound neighbours: ")
            string = ""
            for y in self.__graph.parse_inbound_neighbours(x):
                string += str(y)
                string += " "
            print(string)
            print("Outbound neighbours: ")
            string = ""
            for y in self.__graph.parse_outbound_neighbours(x):
                string += str(y)
                string += " "
            print(string)
            print("")

    def __ui_parse_outbound_neighbours(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        vertex = int(input("Insert vertex:\n>>>"))
        string = ""
        for x in self.__graph.parse_outbound_neighbours(vertex):
            string += str(x)
            string += " "
        print(string)
        print("")

    def __ui_parse_inbound_neighbours(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        vertex = int(input("Insert vertex:\n>>>"))
        string = ""
        for x in self.__graph.parse_inbound_neighbours(vertex):
            string += str(x)
            string += " "
        print(string)
        print("")

    def __ui_get_in_degree(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        vertex = int(input("Insert vertex:\n>>>"))
        print(self.__graph.get_in_degree(vertex))

    def __ui_get_out_degree(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        vertex = int(input("Insert vertex:\n>>>"))
        print(self.__graph.get_out_degree(vertex))

    def __ui_get_cost_edge(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        initial_vertex = int(input("Insert initial vertex:\n>>>"))
        final_vertex = int(input("Insert final vertex:\n>>>"))
        print(self.__graph.get_cost_edge(initial_vertex, final_vertex))

    def __ui_set_cost_edge(self):
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        initial_vertex = int(input("Insert initial vertex:\n>>>"))
        final_vertex = int(input("Insert final vertex:\n>>>"))
        new_cost = int(input("Insert the new cost of the edge:\n>>>"))
        self.__graph.set_cost_edge(initial_vertex, final_vertex, new_cost)

    def __ui_make_copy(self):
        """
        Function that makes a copy of the graph and writes it in a file
        :return:
        """
        if self.__graph is None:
            raise ValueError("Graph uninitialized!\n")
        file_name = input("Insert the name of the file to copy:\n>>>")
        copied_graph = self.__graph.make_copy()
        with open(file_name, "w") as f:
            f.write(str(copied_graph))

    def __ui_find_shortest_path(self):
        initial_vertex = int(input("Insert initial vertex:\n>>>"))
        final_vertex = int(input("Insert final vertex:\n>>>"))
        print()
        print()
        path = self.__graph.BFS_END_TO_START(final_vertex)
        ok = False
        for i in path:
            if i != 0:
                ok = True
        if ok is False:
            raise ValueError("There is no path!\n")
        current_vertex = initial_vertex
        path_string = ""
        length = 0
        while current_vertex != final_vertex:
            path_string += str(current_vertex) + " -> "
            current_vertex = path[current_vertex]
            length += 1
        path_string += str(final_vertex)
        print("The minimum path length is: " + str(length))
        print("The vertices path is: " + path_string)
        print()
        print()

    def __ui_bellman_ford(self):
        source = int(input("Insert source vertex:\n>>>"))
        target = int(input("Insert target vertex:\n>>>"))
        self.__graph.bellmanFord(source, target)

    def run(self):
        commands = {
            '1':  self.__ui_create_simple_graph,
            '2':  self.__ui_create_random_graph,
            '3':  self.__ui_read_graph_from_file,
            '4':  self.__ui_print_dictionaries,
            '5':  self.__ui_add_edge,
            '6':  self.__ui_add_vertex,
            '7':  self.__ui_remove_edge,
            '8':  self.__ui_remove_vertex,
            '9':  self.__ui_get_no_of_vertices,
            '10': self.__ui_parse_set_of_vertices,
            '11': self.__ui_parse_outbound_neighbours,
            '12': self.__ui_parse_inbound_neighbours,
            '13': self.__ui_get_in_degree,
            '14': self.__ui_get_out_degree,
            '15': self.__ui_get_cost_edge,
            '16': self.__ui_set_cost_edge,
            '17': self.__ui_make_copy,
            '18': self.__ui_find_shortest_path,
            '19': self.__ui_bellman_ford
        }
        while True:
            self.__ui_print_menu()
            command = input("Insert a command:\n>>>")
            if command == '0':
                return
            if command not in commands:
                print("Invalid command!\n")
            else:
                try:
                    commands[command]()
                except ValueError as ve:
                    print("Error occurred!\n" + str(ve))


ui = UI()
ui.run()
