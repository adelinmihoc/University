import copy
from math import inf


class DirectGraph:
    def __init__(self, no_of_vertices):
        """
        Constructor function for a direct graph
        :param no_of_vertices: int
        """
        self._no_of_vertices = no_of_vertices
        self._inbound_dict = {}
        self._outbound_dict = {}
        self._cost_dict = {}
        for i in range(self._no_of_vertices):
            self._inbound_dict[i] = []
            self._outbound_dict[i] = []

    ############################################
    # just for test
    def get_in_dict(self):
        return self._inbound_dict

    def get_out_dict(self):
        return self._outbound_dict

    def get_cost_dict(self):
        return self._cost_dict

    ############################################

    def is_edge(self, initial_vertex, final_vertex):
        """
        Function that determines whether or not an edge exists
        :param initial_vertex: int
        :param final_vertex: int
        :return: True - if the edge exists
                 False - if the edge does not exist
        """
        return final_vertex in self._outbound_dict[initial_vertex]

    def is_vertex(self, vertex):
        """
        Function that determines whether or not a vertex exists
        :param vertex: int
        :return: True - if the vertex exists
                 False - if the vertex does not exists
        """
        if vertex in self._outbound_dict.keys():
            return True
        return False

    def get_no_of_vertices(self):
        """
        Getter function for the number of vertices
        :return: number of vertices
        """
        return self._no_of_vertices

    def get_no_of_edges(self):
        """
        Getter function for the number of edges
        :return: number of edges
        """
        return len(self._cost_dict)

    def parse_set_of_vertices(self):
        """
        Function that returns an iterable containing all vertices
        :return: all the keys from the outbound dictionary
        """
        return self._outbound_dict.keys()

    def parse_outbound_neighbours(self, vertex):
        """
        Function that returns an iterable containing the outbound neighbours of a vertex
        :param vertex: int
        :return: list with all the outbound neighbours
                 ValueError - if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!\n")
        return self._outbound_dict[vertex]

    def parse_inbound_neighbours(self, vertex):
        """
        Function that returns an iterable containing the inbound neighbours of a vertex
        :param vertex: int
        :return: list with all the inbound neighbours
                 ValueError - if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!\n")
        return self._inbound_dict[vertex]

    def get_in_degree(self, vertex):
        """
        Getter for the number of connected edges (in) of a vertex
        :param vertex: int
        :return: length of the inbound dictionary
                 ValueError - if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!\n")
        return len(self._inbound_dict[vertex])

    def get_out_degree(self, vertex):
        """
        Getter for the number of connected edges (out) of a vertex
        :param vertex: int
        :return: length of the outbound dictionary
                 ValuerError - if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!\n")
        return len(self._outbound_dict[vertex])

    def get_cost_edge(self, initial_vertex, final_vertex):
        """
        Getter for the cost of an edge
        :param initial_vertex: int
        :param final_vertex: int
        :return: the value associated with the edge
                 ValueError - if the edge does not exist
        """
        if not self.is_edge(initial_vertex, final_vertex):
            raise ValueError("Edge does not exist!\n")
        return self._cost_dict[(initial_vertex, final_vertex)]

    def set_cost_edge(self, initial_vertex, final_vertex, new_cost):
        """
        Setter for the cost of an edge
        :param initial_vertex: int
        :param final_vertex: int
        :param new_cost: int
        :return: ValueError - if the edge associated with the two vertices does not exist
        """
        if not self.is_edge(initial_vertex, final_vertex):
            raise ValueError("Edge does not exist!\n")
        self._cost_dict[(initial_vertex, final_vertex)] = new_cost

    def add_edge(self, initial_vertex, final_vertex, cost):
        """
        Function that adds an edge to the graph
        :param initial_vertex: int
        :param final_vertex: int
        :param cost: int
        :return: ValueError - if the vertexes are not valid or if the edge already exists
        """
        if not self.is_vertex(initial_vertex) or not self.is_vertex(final_vertex):
            raise ValueError("Not a valid vertex!\n")
        if self.is_edge(initial_vertex, final_vertex):
            raise ValueError("Edge already exists!\n")
        self._inbound_dict[final_vertex].append(initial_vertex)
        self._outbound_dict[initial_vertex].append(final_vertex)
        self._cost_dict[(initial_vertex, final_vertex)] = cost

    def add_vertex(self, vertex):
        """
        Function that adds a vertex to the graph
        :param vertex: int
        :return: ValueError - if the vertex already exists
        """
        if self.is_vertex(vertex):
            raise ValueError("Vertex already exists!\n")
        self._inbound_dict[vertex] = []
        self._outbound_dict[vertex] = []

    def remove_edge(self, initial_vertex, final_vertex):
        """
        Function that removes an edge from the graph
        :param initial_vertex: int
        :param final_vertex: int
        :return: ValueError - if the edge does not exist
        """
        if not self.is_edge(initial_vertex, final_vertex):
            raise ValueError("Edge does not exist!\n")
        self._inbound_dict[final_vertex].remove(initial_vertex)
        self._outbound_dict[initial_vertex].remove(final_vertex)
        for key in self._cost_dict.keys():
            if initial_vertex == key[0] and final_vertex == key[1]:
                del self._cost_dict[(key[0], key[1])]
                return

    def remove_vertex(self, vertex):
        """
        Function that removes a vertex from the graph
        :param vertex: int
        :return: ValueError - if the vertex does not exist
        """
        if not self.is_vertex(vertex):
            raise ValueError("Vertex does not exist!\n")
        edges = []
        for neighbour in self.parse_outbound_neighbours(vertex):
            edges.append([vertex, neighbour])
        for i in range(len(edges)):
            self.remove_edge(edges[i][0], edges[i][1])
        del self._inbound_dict[vertex]
        del self._outbound_dict[vertex]
        self._no_of_vertices -= 1

    def make_copy(self):
        """
        Function that makes a deep copy of the graph
        :return: the copy
        """
        return copy.deepcopy(self)

    def __str__(self):
        """
        Function that transforms the graph into a string
        :return:
        """
        string = ""
        string = string + str(self.get_no_of_vertices()) + " " + str(self.get_no_of_edges()) + "\n"
        for item in self._cost_dict.items():
            string = string + str(item[0][0]) + " " + str(item[0][1]) + " " + str(item[1]) + "\n"
        return string

    def BFS_END_TO_START(self, final_vertex):
        """
            Function that finds a lowest length path between two vertices, by using a forward breadth-first search
        from the starting vertex
        :param final_vertex: int
        :return:
        """
        queue = [final_vertex]
        path = [0] * self._no_of_vertices
        length = [0] * self._no_of_vertices
        visited = [False] * len(self._inbound_dict.keys())
        length[final_vertex] = 0
        visited[final_vertex] = True
        while queue:
            current_vertex = queue[0]
            del queue[0]
            for inbound_vertex in self._inbound_dict[current_vertex]:
                if not visited[inbound_vertex]:
                    queue.append(inbound_vertex)
                    visited[inbound_vertex] = True
                    length[inbound_vertex] = length[current_vertex] + 1
                    path[inbound_vertex] = current_vertex
        return path

    def bellmanFord(self, source, target):
        # Complexity: O(n * m) n - no of vertices, m - no of edges
        # step 1
        distance = [inf for _ in range(self._no_of_vertices)]
        distance[source] = 0
        predecessor = [False for _ in range(self._no_of_vertices)]

        # step 2
        for _ in range(self._no_of_vertices - 1):
            flag = False
            for item in self._cost_dict.items():
                if distance[item[0][1]] > distance[item[0][0]] + item[1]:
                    distance[item[0][1]] = distance[item[0][0]] + item[1]
                    predecessor[item[0][1]] = item[0][0]
                    flag = True
            # if there are no modifications in the distance then the minimum distance was found
            if not flag:
                break

        # step 3
        for item in self._cost_dict.items():
            if distance[item[0][1]] > distance[item[0][0]] + item[1]:
                raise ValueError("Graph contains a negative cost cycle!\n")

        if distance[target] == inf:
            print("No path found!\n")
            return

        # construct the path
        print("A lowest cost walk from " + str(source) + " to " + str(target) + " is " + str(distance[target]))
        walk = ""
        current_vertex = target
        while current_vertex != source:
            walk += str(current_vertex) + " <- "
            current_vertex = predecessor[current_vertex]
        walk += str(source)
        print(walk)




