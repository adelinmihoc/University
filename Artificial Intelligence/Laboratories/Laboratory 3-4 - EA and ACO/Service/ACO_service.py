from random import *

from Domain.ACO_entities import Ant
from Service.PathFinding_service import PathFindingService


class AcoService:
    def __init__(self, d_map=None, trace=None, alpha=1.9, beta=0.9, rho=0.05, q0=0.5, sensors=None,
                 starting_node=None, no_of_ants=20, no_of_epochs=600, no_of_sensors=7,
                 visibility=None, initial_pheromone=1):
        self.d_map = d_map
        self.alpha = alpha
        self.beta = beta
        self.rho = rho
        self.q0 = q0
        self.initial_pheromone = initial_pheromone
        self.no_of_ants = no_of_ants
        self.no_of_epochs = no_of_epochs

        if sensors is None:
            self.no_of_sensors = no_of_sensors
            self.sensors = []

            while no_of_sensors:
                x = randint(0, 19)
                y = randint(0, 19)
                while self.d_map.surface[x][y] != 0:
                    x = randint(0, 19)
                    y = randint(0, 19)
                self.sensors.append((x, y))
                no_of_sensors -= 1
        else:
            self.sensors = sensors
            self.no_of_sensors = len(sensors)

        x = randint(0, 19)
        y = randint(0, 19)
        while self.d_map.surface[x][y] != 0:
            x = randint(0, 19)
            y = randint(0, 19)

        self.starting_node = (x, y)

        if starting_node is not None:
            self.starting_node = starting_node

        self.sensors_graph = {}
        self.sensors_paths = {}

        self.pathfinding = PathFindingService()

        self.compute_sensors_graph_and_path()

        # compute optimal energy needed by the sensors
        self.sensors_powers = {}
        self.sensors_energy_needed = {}
        self.sensors_all_powers = {}
        for sensor in self.sensors:
            v = [[-1, 0], [0, 1], [1, 0], [0, -1]]
            energy_so_far = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0}
            for energy in range(1, 6):
                for d in v:
                    aux = energy
                    x = sensor[0] + d[0]
                    y = sensor[1] + d[1]
                    while True:
                        if aux == 0 or 0 > x or 0 > y or x >= self.d_map.n or y >= self.d_map.m or self.d_map.surface[x][y] != 0:
                            break
                        aux -= 1
                        energy_so_far[energy] += 1
                        x = x + d[0]
                        y = y + d[1]
            # print(energy_so_far)
            for i in range(1, 6):
                if energy_so_far[i] == energy_so_far[i - 1]:
                    break
                self.sensors_energy_needed[sensor] = i
                self.sensors_all_powers[sensor] = energy_so_far

        self.global_trace = {}
        if trace is None:
            self.trace = {}
            for edge in self.sensors_graph:
                self.trace[(edge[0], edge[1])] = self.initial_pheromone
            self.global_trace = self.trace
        else:
            self.trace = trace
            self.global_trace = trace
        if visibility is None:
            self.visibility = {}
            for edge in self.sensors_graph:
                # visibility = next sensor total squares surveilled / length to that sensor
                self.visibility[(edge[0], edge[1])] = 1 / self.sensors_graph[(edge[0], edge[1])]
        else:
            self.visibility = visibility

        self.final_sensors_energies = {}

    def get_sensors_powers(self):
        return self.sensors_powers

    def get_starting_point(self):
        return self.starting_node

    def compute_sensors_graph_and_path(self):
        self.sensors_graph = {}

        dummy_sensors = self.sensors
        for i in range(0, len(dummy_sensors)):
            j = i + 1
            while j < len(dummy_sensors):
                path = self.pathfinding.searchAStar(self.d_map, dummy_sensors[i], dummy_sensors[j])
                self.sensors_graph[(dummy_sensors[i], dummy_sensors[j])] = len(path)
                self.sensors_paths[(dummy_sensors[i], dummy_sensors[j])] = path

                path = self.pathfinding.searchAStar(self.d_map, dummy_sensors[j], dummy_sensors[i])
                self.sensors_paths[(self.sensors[j], self.sensors[i])] = path
                self.sensors_graph[(dummy_sensors[j], dummy_sensors[i])] = len(path)
                j += 1

    def get_sensors_paths(self):
        return self.sensors_paths

    def get_sensors(self):
        return self.sensors

    # def epoch(self, ant_energy):
    #     self.trace = self.global_trace
    #
    #     ant_set = [Ant(self.no_of_sensors, ant_energy) for _ in range(self.no_of_ants)]
    #     for i in range(self.no_of_sensors):
    #         for ant in ant_set:
    #             # increase partial solution
    #             ant.add_node(self.trace, self.visibility, self.alpha, self.beta, self.q0, self.sensors)
    #             # locally modify the trace of pheromones
    #             for j in range(len(ant.path) - 1):
    #                 x = ant.path[j]
    #                 y = ant.path[j + 1]
    #                 self.trace[(self.sensors[x], self.sensors[y])] = \
    #                     (1 - self.rho) * self.trace[(self.sensors[x], self.sensors[y])] + \
    #                     self.rho * self.initial_pheromone
    #
    #     fitnesses = [[ant_set[i].fitness(self.sensors, self.sensors_graph), i] for i in range(len(ant_set))]
    #     # return the best ant
    #     return ant_set[min(fitnesses)[1]]

    def epochv2(self, ant_energy):
        self.trace = self.global_trace

        ant_set = [Ant(self.no_of_sensors, ant_energy) for _ in range(self.no_of_ants)]
        # add the energy to the first sensor
        for ant in ant_set:
            new_sensor = self.sensors[ant.path[-1]]

            optimal_energy = self.sensors_energy_needed[new_sensor]
            while ant.energy > 0 and optimal_energy > 0:
                ant.energy -= self.sensors_all_powers[new_sensor][optimal_energy]
                self.final_sensors_energies[new_sensor] = optimal_energy
                if ant.energy < 0:
                    ant.energy += self.sensors_all_powers[optimal_energy]
                    optimal_energy -= 1
                else:
                    break

        # main iteration
        for ant in ant_set:
            while ant.energy > 0 and len(ant.path) < ant.size:

                # increase partial solution
                ant.add_node(self.trace, self.visibility, self.alpha, self.beta, self.q0, self.sensors)
                new_path_cost = self.sensors_graph[(self.sensors[ant.path[-2]], self.sensors[ant.path[-1]])]
                new_sensor = self.sensors[ant.path[-1]]
                ant.energy -= new_path_cost

                if ant.energy < 0:
                    ant.path.pop()  # delete the last sensor from path - can't get there
                    ant.energy = 0
                elif ant.energy > 0:
                    optimal_energy = self.sensors_energy_needed[new_sensor]
                    while ant.energy > 0 and optimal_energy > 0:
                        ant.energy -= self.sensors_all_powers[new_sensor][optimal_energy]
                        self.final_sensors_energies[new_sensor] = optimal_energy
                        if ant.energy < 0:
                            ant.energy += self.sensors_all_powers[new_sensor][optimal_energy]
                            optimal_energy -= 1
                        else:
                            break

                    # locally modify the trace of pheromones
                    for j in range(len(ant.path) - 1):
                        x = ant.path[j]
                        y = ant.path[j + 1]
                        self.trace[(self.sensors[x], self.sensors[y])] = \
                            (1 - self.rho) * self.trace[(self.sensors[x], self.sensors[y])] + \
                            self.rho * self.initial_pheromone

        fitnesses = [[ant_set[i].fitness(self.sensors, self.sensors_graph), i]
                     for i in range(len(ant_set))]
        # return the best ant
        return ant_set[min(fitnesses)[1]]

    def solver(self, ant_energy):
        sol = []
        energy_each_sensor = None
        best_fitness = 1000000
        for i in range(self.no_of_epochs):
            print("Epoch number: " + str(i))
            ant = self.epochv2(ant_energy)

            if ant.fitness(self.sensors, self.sensors_graph) < best_fitness:
                best_ant = ant
                best_fitness = ant.fitness(self.sensors, self.sensors_graph)  # length of the cost path
                # modify the global trace of pheromones
                for j in range(len(best_ant.path) - 1):
                    x = ant.path[j]
                    y = ant.path[j + 1]
                    self.global_trace[(self.sensors[x], self.sensors[y])] = \
                        (1 - self.rho) * self.global_trace[(self.sensors[x], self.sensors[y])] + \
                        self.rho * (1 / best_fitness)
                sol = best_ant.path
                energy_each_sensor = self.final_sensors_energies
        return sol, energy_each_sensor
