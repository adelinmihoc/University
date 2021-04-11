from Graph import DoubleDictGraph


def read_from_file():
    file_name = input("Insert name of the file:\n>>>")
    with open(file_name, "r") as f:
        line = f.readline()
        line = line.strip()
        parts = line.split()
        no_of_vertices = int(parts[0])
        no_of_edges = int(parts[1])
        graph = DoubleDictGraph(no_of_vertices)
        for _ in range(no_of_edges):
            line = f.readline()
            line = line.strip()
            parts = line.split()
            graph.addEdge(int(parts[0]), int(parts[1]))
    return graph


def bfs(graph, start_vertex):
    visited = {}
    queue = [start_vertex]
    visited[start_vertex] = []
    while queue:
        current_vertex = queue.pop(0)
        for vertex in graph.parseNout(current_vertex):
            if vertex not in visited:
                queue.append(vertex)
                visited[vertex] = []
                visited[current_vertex].append(vertex)
    return visited


grph = read_from_file()
strt_vert = int(input("Insert start vertex:\n>>>"))
print(bfs(grph, strt_vert))
