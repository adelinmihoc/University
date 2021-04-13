from random import *
import pygame

from Domain.ACO_entities import Ant
from Utils import *

from Service.PathFinding_service import PathFindingService


class AcoService:
    def __init__(self, d_map=None, trace=None, alpha=1.9, beta=0.9, rho=0.05, q0=0.5, sensors=None,
                 starting_node=None, no_of_ants=0, no_of_epochs=0, no_of_sensors=7, visibility=None):
        if trace is None:
            self.trace = []
        else:
            self.trace = trace
        if visibility is not None:
            self.visibility = visibility
        else:
            self.visibility = []
        self.d_map = d_map
        self.alpha = alpha
        self.beta = beta
        self.rho = rho
        self.q0 = q0
        self.no_of_ants = no_of_ants
        self.no_of_epochs = no_of_epochs
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

        x = randint(0, 19)
        y = randint(0, 19)
        while self.d_map.surface[x][y] != 0:
            x = randint(0, 19)
            y = randint(0, 19)

        self.starting_node = (x, y)

        if sensors is not None:
            self.sensors = sensors
        if starting_node is not None:
            self.starting_node = starting_node
        self.sensors_graph = {}
        self.sensors_paths = {}

        self.pathfinding = PathFindingService()

        self.compute_sensors_graph()

    def compute_sensors_graph(self):
        self.sensors_graph = {}
        self.sensors_paths = {}

        dummy_sensors = self.sensors.copy()
        dummy_sensors.append(self.starting_node)
        for i in range(0, len(dummy_sensors)):
            j = i + 1
            while j < len(dummy_sensors):
                path = self.pathfinding.searchAStar(self.d_map, dummy_sensors[i], dummy_sensors[j])
                self.sensors_graph[(dummy_sensors[i], dummy_sensors[j])] = len(path)
                self.sensors_graph[(dummy_sensors[j], dummy_sensors[i])] = len(path)
                self.sensors_paths[(dummy_sensors[i], dummy_sensors[j])] = path
                #self.sensors_paths[(self.sensors[j], self.sensors[i])] = path
                j += 1

    def compute_visibility(self):
        pass

    def compute_trace(self):
        pass

    def get_sensors_paths(self):
        all_paths = []
        for key in self.sensors_paths.keys():
            all_paths.append(self.sensors_paths.get(key))
        return all_paths

    def get_sensors(self):
        return self.sensors

    def epoch(self):
        ant_set = [Ant(self.no_of_sensors + 1) for i in range(self.no_of_ants)]
        for i in range(self.no_of_sensors):
            for ant in ant_set:
                ant.add_node(self.trace, self.visibility, self.alpha, self.beta, self.q0)
        #TODO update pheromone trail

    def solver(self):
        pass
