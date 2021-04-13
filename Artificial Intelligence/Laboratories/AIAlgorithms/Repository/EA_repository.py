from Domain.EA_entities import *


class EaRepository:
    def __init__(self):
        self.__populations = []
        self.__individual_size = 0
        self.__population_size = 0
        self.__seeds = []

    def create_populations(self, no_of_populations):
        self.__populations = []
        self.__seeds = []
        for i in range(0, no_of_populations):
            seed(no_of_populations - i)
            self.__seeds.append(no_of_populations - i)
            population = Population(self.__population_size, self.__individual_size)
            self.__populations.append(population)

    def get_seeds(self):
        return self.__seeds

    def set_individual_size(self, size):
        self.__individual_size = size

    def set_population_size(self, size):
        self.__population_size = size

    def get_individual_size(self):
        return self.__individual_size

    def get_population_size(self):
        return self.__population_size

    def get_populations(self):
        return self.__populations
