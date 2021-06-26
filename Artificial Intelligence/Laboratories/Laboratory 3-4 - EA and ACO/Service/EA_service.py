from random import *
import numpy as np


class EaService:
    def __init__(self, repository):
        self.__repository = repository
        self.__no_of_iterations = 100
        self.__no_of_populations = 30
        self.__starting_node = (0, 0)
        self.__best_fitness_list = []
        self.__best_individuals = []
        self.__averages = []

    def set_starting_node(self, node):
        self.__starting_node = node

    def get_starting_node(self):
        return self.__starting_node

    def set_no_of_iterations(self, number):
        self.__no_of_iterations = number

    def set_no_of_populations(self, number):
        self.__no_of_populations = number

    def set_individual_size(self, size):
        self.__repository.set_individual_size(size)

    def set_population_size(self, size):
        self.__repository.set_population_size(size)

    def get_no_of_iterations(self):
        return self.__no_of_iterations

    def get_no_of_populations(self):
        return self.__no_of_populations

    def get_individual_size(self):
        return self.__repository.get_individual_size()

    def get_population_size(self):
        return self.__repository.get_population_size()

    def iteration(self, population, d_map):
        population.evaluate(d_map, self.__starting_node)

        # a iteration:
        # selection of the parents
        # randomly
        i1 = randint(0, population.getPopulationSize() - 1)
        i2 = randint(0, population.getPopulationSize() - 1)

        parent1 = population.getIndividuals()[i1]
        parent2 = population.getIndividuals()[i2]

        # create offsprings by crossover of the parents
        if parent1 != parent2:
            offspring1, offspring2 = parent1.crossover(parent2)
            # apply some mutations
            offspring1.mutate()
            offspring2.mutate()
            # selection of the survivors
            offspring1.fitness(d_map, self.__starting_node)
            offspring2.fitness(d_map, self.__starting_node)

            best = [parent1, parent2, offspring1, offspring2]

            best = sorted(best, reverse=True)
            # pop the ones with the best fitness and put them in population
            population.getIndividuals()[i1] = best[0]
            population.getIndividuals()[i2] = best[1]

        return population

    def run(self, d_map):
        self.__repository.create_populations(self.__no_of_populations)
        self.__best_fitness_list = []
        self.__best_individuals = []

        i = 1
        for population in self.__repository.get_populations():
            result = self.solver(population, d_map)
            print("population no: " + str(i) + " done")
            self.__best_fitness_list.append(result[0].getFitness())
            self.__best_individuals.append(result[0])
            i += 1

        average = np.average(self.__best_fitness_list)
        stddev = np.std(self.__best_fitness_list)

        print("Averages for each iteration: " + str(self.__averages))

        return self.__best_individuals, self.__best_fitness_list, average, stddev, self.__repository.get_seeds()

    def solver(self, population, d_map):
        self.__averages = []
        for _ in range(self.__no_of_iterations):
            population = self.iteration(population, d_map)
            population.evaluate(d_map, self.__starting_node)
            self.__averages.append(population.getAverage())
        # result = all the individuals in the population
        result = population.selection(population.getPopulationSize())
        return result
