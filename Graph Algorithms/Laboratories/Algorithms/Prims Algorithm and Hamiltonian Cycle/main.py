from undirected_graph import UndirectedGraph


class UI:
    def __init__(self):
        self.__graph = None

    def __ui_read_graph_from_file(self):
        file_name = input("insert name of the file:\n>>>")
        with open(file_name, "r") as f:
            line = f.readline()
            line = line.strip()
            parts = line.split()
            no_of_vertices = int(parts[0])
            no_of_edges = int(parts[1])
            graph = UndirectedGraph(no_of_vertices)
            for _ in range(no_of_edges):
                line = f.readline()
                line = line.strip()
                parts = line.split()
                graph.add_edge(int(parts[0]), int(parts[1]), int(parts[2]))
        self.__graph = graph

    def __ui_print_dictionaries(self):
        if self.__graph is None:
            raise ValueError("graph uninitialized!\n")
        edge_dict = self.__graph.get_edge_dict().items()
        cost_dict = self.__graph.get_cost_dict().items()
        print("edge dictionary:")
        for item in edge_dict:
            print(item[0], "--->", item[1])
        print("\ncost dictionary: ")
        for item in cost_dict:
            print(item[0], "--->", item[1])

    def __ui_prims_algorithm(self):
        if self.__graph is None:
            raise ValueError("graph uninitialized!\n")
        self.__graph.prims_algorithm()

    def __ui_add_edge(self):
        if self.__graph is None:
            raise ValueError("graph uninitialized!\n")
        x = int(input("input initial vertex:\n>>>"))
        y = int(input("input final vertex:\n>>>"))
        cost = int(input("input cost:\n>>>"))
        self.__graph.add_edge(x, y, cost)

    def __ui_add_vertex(self):
        if self.__graph is None:
            raise ValueError("graph uninitialized!\n")
        x = input("input a vertex:\n>>>")
        self.__graph.add_vertex(x)

    def __ui_hamiltonian_cycle(self):
        if self.__graph is None:
            raise ValueError("graph uninitialized!\n")
        self.__graph.hamiltonian_cycle()

    @staticmethod
    def __ui_print_help_menu():
        print("help menu:\n"
              "0 - exit\n"
              "1 - read graph from file\n"
              "2 - print dictionaries\n"
              "3 - prim's algorithm\n"
              "4 - add edge\n"
              "5 - add vertex\n"
              "6 - hamiltonian cycle\n")

    def run(self):
        commands = {
            '1': self.__ui_read_graph_from_file,
            '2': self.__ui_print_dictionaries,
            '3': self.__ui_prims_algorithm,
            '4': self.__ui_add_edge,
            '5': self.__ui_add_vertex,
            '6': self.__ui_hamiltonian_cycle
        }
        while True:
            self.__ui_print_help_menu()
            command = input("input command:\n>>>")
            if command == '0':
                return
            if command not in commands:
                print("invalid command\n")
            else:
                try:
                    commands[command]()
                except ValueError as ve:
                    print("error occurred!\n" + str(ve))
                except FileNotFoundError:
                    print("file not found!\n")


ui = UI()
ui.run()

