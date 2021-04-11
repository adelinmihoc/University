import heapq


class UndirectedGraph:
    def __init__(self, vertices):
        self.__no_of_vertices = vertices
        self.__edge_dict = {}
        self.__cost_dict = {}
        for i in range(vertices):
            self.__edge_dict[i] = []

    def is_vertex(self, x):
        if x in self.__edge_dict.keys():
            return True
        return False

    def add_edge(self, x, y, cost):
        if self.is_vertex(x) is False:
            raise ValueError("invalid initial vertex\n")
        if self.is_vertex(y) is False:
            raise ValueError("invalid final vertex\n")
        if x not in self.__edge_dict[y] and y not in self.__edge_dict[x]:
            self.__edge_dict[x].append(y)
            self.__edge_dict[y].append(x)
            self.__cost_dict[(x, y)] = cost
            self.__cost_dict[(y, x)] = cost
        else:
            raise ValueError("edge already exists!\n")

    def add_vertex(self, x):
        if x not in self.__edge_dict:
            self.__edge_dict[x] = []
            self.__no_of_vertices += 1
        else:
            raise ValueError("vertex already exists!\n")

    def parse_neighbours(self, x):
        return self.__edge_dict[x]

    def get_edge_dict(self):
        return self.__edge_dict

    def get_cost_dict(self):
        return self.__cost_dict

    def get_cost(self, x, y):
        if (x, y) not in self.__cost_dict:
            raise ValueError("edge does not exits!\n")
        return self.__cost_dict[(x, y)]

    def prims_algorithm(self):
        # step 1 prepare queue, prev, dist, edges, source, vertices, total cost
        q = []
        prev = {}
        dist = {}
        edges = []
        s = 1
        vertices = [s]
        total_cost = 0

        # step 2 push in  queue all vertices that are accessible from the source
        # the vertices with priority are the ones with minimum cost from source to them
        for x in self.parse_neighbours(s):
            dist[x] = self.get_cost(x, s)
            prev[x] = s
            heapq.heappush(q, (dist[x], x))

        # step 3 iterate through queue
        # at each iteration pop the vertex with the minimum cost from the previous vertex to itself
        # add a new edge and increase the the total cost
        # then push in queue the vertices that are accessible from the current vertex.
        # the ones with minimum cost from themselves to the current vertex have priority
        while q:
            x = heapq.heappop(q)
            if x[1] not in vertices:
                edges.append((x[1], prev[x[1]]))
                total_cost += self.get_cost(x[1], prev[x[1]])
                vertices.append(x[1])
                for y in self.parse_neighbours(x[1]):
                    if y not in dist.keys() or self.get_cost(x[1], y) < dist[y]:
                        dist[y] = self.get_cost(x[1], y)
                        heapq.heappush(q, (dist[y], y))
                        prev[y] = x[1]

        # final step print all the edges and the total cost
        print("a minimum spanning tree is:")
        for x in edges:
            print(x)
        print("total cost: ", total_cost)

    def hamiltonian_cycle_is_safe(self, v, pos, path):
        if path[pos - 1] not in self.__edge_dict[v] and v not in self.__edge_dict[path[pos - 1]]:
            return False
        for vertex in path:
            if vertex == v:
                return False
        return True

    def hamiltonian_cycle_util(self, path, pos):
        if pos == self.__no_of_vertices:
            if path[pos - 1] in self.__edge_dict[path[0]] and path[0] in self.__edge_dict[path[pos - 1]]:
                return True
            else:
                return False

        for v in range(0, self.__no_of_vertices):
            if self.hamiltonian_cycle_is_safe(v, pos, path):
                path[pos] = v
                if self.hamiltonian_cycle_util(path, pos + 1):
                    return True
                path[pos] = -1
        return False

    def hamiltonian_cycle(self):
        path = [-1] * self.__no_of_vertices
        for i in range(self.__no_of_vertices):
            path[0] = i
            if self.hamiltonian_cycle_util(path, 1) is False:
                print("no hamiltonian cycles\n")
            else:
                print("Found a hamiltonian cycle:")
                for vertex in path:
                    print(vertex, end=" ")
                print(path[0], '\n')
