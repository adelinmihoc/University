from repository import *
import heapq


class Controller:
    def __init__(self, repository):
        self.__repository = repository

    def iteration(self, args):
        # args - list of parameters needed to run one iteration
        population = args[0]
        m = args[1]
        starting_node = args[2]

        population.evaluate(m, starting_node)

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
            offspring1.fitness(m, starting_node)
            offspring2.fitness(m, starting_node)

            best = [parent1, parent2, offspring1, offspring2]

            best = sorted(best, reverse=True)
            # pop the ones with the best fitness and put them in population
            population.getIndividuals()[i1] = best[0]
            population.getIndividuals()[i2] = best[1]

        return population

    def run(self, args):
        # args - list of parameters needed in order to run the algorithm
        # args = [population, noOfIterations, map, starting_node]

        population = args[0]
        noOfIterations = args[1]

        for _ in range(noOfIterations):
            population = self.iteration([population, args[2], args[3]])

        result = population.selection(population.getPopulationSize())

        return result

        # until stop condition
        #    perform an iteration
        #    save the information need it for the statistics

        # return the results and the info for statistics

    def solver(self, args):
        # args - list of parameters needed in order to run the solver
        # args = [population_size, individual_size, noOfIterations, map, starting_node]

        # create the population,
        population = self.__repository.createPopulation([args[0], args[1]])

        # run the algorithm
        result = self.run([population, args[2], args[3], args[4]])
        return result

        # TODO return the results and the statistics
