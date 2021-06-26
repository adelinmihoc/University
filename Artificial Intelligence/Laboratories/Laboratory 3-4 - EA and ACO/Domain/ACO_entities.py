from random import *
from numpy.random import choice as np_choice


class Ant:
    def __init__(self,  no_of_sensors, energy):
        self.size = no_of_sensors
        self.path = [randint(0, no_of_sensors - 1)]
        self.energy = energy

    def next_nodes(self, a):
        new = []
        for i in range(0, self.size):
            if i not in self.path:
                new.append(i)
        return new.copy()

    def add_node(self, trace, visibility, alpha, beta, q0, sensors):
        current_node = self.path[-1]
        next_nodes = self.next_nodes(current_node)

        if len(next_nodes) == 0:
            return False

        if random() < q0:
            best_node = None
            best_x = 0
            for next_node in next_nodes:
                x = (trace[(sensors[current_node], sensors[next_node])] ** alpha) * \
                    (visibility[(sensors[current_node], sensors[next_node])] ** beta)
                if x > best_x:
                    best_node = next_node
                    best_x = x
            self.path.append(best_node)
        else:
            probability_distribution = []
            sum_x = 0
            for next_node in next_nodes:
                sum_x += (trace[(sensors[current_node], sensors[next_node])] ** alpha) * \
                    (visibility[(sensors[current_node], sensors[next_node])] ** beta)
            for next_node in next_nodes:
                probability_distribution.append((trace[(sensors[current_node], sensors[next_node])] ** alpha) *
                                                (visibility[(sensors[current_node], sensors[next_node])] ** beta) /
                                                sum_x)
            draw = np_choice(next_nodes, 1, probability_distribution)
            self.path.append(draw[0])
        return True

    def fitness(self, sensors, sensor_graph):
        f = 0
        for i in range(len(self.path) - 1):
            f += sensor_graph[(sensors[self.path[i]], sensors[self.path[i + 1]])]
        return f
