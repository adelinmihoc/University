from random import *
import pygame
from Utils import *
import numpy as np


class Gene:
    def __init__(self):
        self.__code = randint(1, 4)

    def getCode(self):
        return self.__code


class Individual:
    def __init__(self, size):
        self.__size = size
        self.__x = [Gene().getCode() for _ in range(self.__size)]
        self.__f = None

    def getFitness(self):
        return self.__f

    def fitness(self, mmap, starting_node):
        # compute the fitness for the individual
        # and save it in self.__f
        self.__f = 0
        path = self.to_path(starting_node)
        visited = []

        for node in path:
            if node[0] < 0 or node[0] > 19 or node[1] < 0 or node[1] > 19:
                self.__f = 0
                break
            if mmap.surface[node[0]][node[1]] == 1:
                self.__f = 0
                break
            # UP
            for i in range(node[0], 0, -1):
                if mmap.surface[i][node[1]] == 1:
                    break
                elif (i, node[1]) not in visited:
                    self.__f += 1
                    visited.append((i, node[1]))
            # DOWN
            for i in range(node[0], mmap.m):
                if mmap.surface[i][node[1]] == 1:
                    break
                elif (i, node[1]) not in visited:
                    self.__f += 1
                    visited.append((i, node[1]))
            # LEFT
            for i in range(node[1], 0, -1):
                if mmap.surface[node[0]][i] == 1:
                    break
                elif (node[0], i) not in visited:
                    self.__f += 1
                    visited.append((node[0], i))
            # Right
            for i in range(node[1], mmap.n):
                if mmap.surface[node[0]][i] == 1:
                    break
                elif (node[0], i) not in visited:
                    self.__f += 1
                    visited.append((node[0], i))

    def to_path(self, node):
        path = [node]

        for point in self.__x:
            x = node[0]
            y = node[1]
            if point == 1:
                node = [x - 1, y]
            if point == 2:
                node = [x + 1, y]
            if point == 3:
                node = [x, y + 1]
            if point == 4:
                node = [x, y - 1]
            path.append(node)

        return path

    def mutate(self, mutateProbability=0.04):
        # perform a mutation with respect to the representation
        if random() < mutateProbability:
            self.__x[randint(0, self.__size - 1)] = randint(1, 4)

    def crossover(self, otherParent, crossoverProbability=0.8):
        # perform the crossover between the self and the otherParent
        offspring1, offspring2 = Individual(self.__size), Individual(self.__size)

        if random() < crossoverProbability:
            # rate = randint(0, self.__size - 1)
            # offspring1.__x = otherParent.__x[:rate] + self.__x[rate:]
            # offspring2.__x = self.__x[:rate] + otherParent.__x[rate:]
            # # for i in range(0, rate):
            # #     offspring1.__x.append(self.__x[i])
            # #     offspring2.__x.append(otherParent.__x[i])
            # # for i in range(rate, self.__size - 1):
            # #     offspring1.__x.append(otherParent.__x[i])
            # #     offspring2.__x.append(self.__x[i])
            offspring1.__x = []
            offspring2.__x = []

            parents_chunk = []
            index = 0
            length = self.__size
            while index < length:
                randomNumber = randint(1, length - index + 1)
                parents_chunk.append(self.__x[index:index + randomNumber])
                index = index + randomNumber

            index = 0
            length = otherParent.__size
            while index < length:
                randomNumber = randint(1, length - index + 1)
                parents_chunk.append(otherParent.__x[index:index + randomNumber])
                index = index + randomNumber

            shuffle(parents_chunk)

            for chunk in parents_chunk:
                for gene in chunk:
                    if len(offspring1.__x) == offspring1.__size:
                        break
                    offspring1.__x.append(gene)

            shuffle(parents_chunk)

            for chunk in parents_chunk:
                for gene in chunk:
                    if len(offspring2.__x) == offspring2.__size:
                        break
                    offspring2.__x.append(gene)

        return offspring1, offspring2

    def __str__(self):
        return str(self.__x)

    def __gt__(self, other):
        if self.__f > other.__f:
            return True
        else:
            return False

    def __lt__(self, other):
        if self.__f < other.__f:
            return True
        else:
            return False


class Population:
    def __init__(self, populationSize=0, individualSize=0):
        self.__populationSize = populationSize
        self.__v = [Individual(individualSize) for _ in range(populationSize)]

    def getAverage(self):
        fitness = []
        for x in self.__v:
            fitness.append(x.getFitness())
        return np.average(fitness)

    def getPopulationSize(self):
        return self.__populationSize

    def getIndividuals(self):
        return self.__v

    def evaluate(self, mmap, starting_node):
        # evaluates the population
        for x in self.__v:
            x.fitness(mmap, starting_node)

    def selection(self, k=0):
        graded = [x for x in self.__v]
        graded = sorted(graded, reverse=True)

        return graded[:k]

    def __str__(self):
        string = ""
        for x in self.__v:
            string += str(x)
        return string
