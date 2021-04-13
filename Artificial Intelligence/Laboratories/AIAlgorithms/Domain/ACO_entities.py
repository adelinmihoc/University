from random import *


class Ant:
    def __init__(self,  no_of_sensors):
        self.size = no_of_sensors
        self.path = [randint(0, no_of_sensors - 1)]

    def next_nodes(self, a):
        new = []
        for i in range(0, self.size):
            if i not in self.path:
                new.append(i)
        return new.copy()

    def add_node(self, trace, visibility, alpha, beta, q0):
        current_node = self.path[-1]
        next_nodes = self.next_nodes(current_node)

        if len(next_nodes) == 0:
            return False

        if random() < q0:
            best_node = None
            best_x = 0
            for next_node in next_nodes:
                x = (trace[(current_node, next_node)] ** alpha) * (visibility[(current_node, next_node)] ** beta)
                if x > best_x:
                    best_node = next_node
                    best_x = x
            self.path.append(best_node)
        else:
            self.path.append(choice(next_nodes))
        return True

    def fitness(self):
        pass
