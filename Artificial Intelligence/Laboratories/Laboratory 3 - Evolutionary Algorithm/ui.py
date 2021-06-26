# -*- coding: utf-8 -*-


# imports
from gui import *
from controller import *
from repository import *
from domain import *


m = Map(20, 20)
m.randomMap()

# we position the drone somewhere in the area
x = randint(0, 19)
y = randint(0, 19)

while m.surface[x][y] != 0:
    x = randint(0, 19)
    y = randint(0, 19)

individual_size = 10
population_size = 50
no_of_iterations = 1000

repository = Repository()
controller = Controller(repository)

# [population_size, individual_size, noOfIterations, map, starting_node]
result = controller.solver([population_size, individual_size, no_of_iterations, m, (x, y)])

path = result[0].to_path((x, y))
print("Best path = " + str(path))

best_fitness = result[0].getFitness()
print("Best fitness = " + str(best_fitness))

fitness = []
for individual in result:
    fitness.append(individual.getFitness())

average = np.average(fitness)
stddev = np.std(fitness)

print("Average fitness = " + str(average))
print("Standard deviation for fitness = " + str(stddev))

movingDrone(m, path)

# create a menu
#   1. map options:
#         a. create random map
#         b. load a map
#         c. save a map
#         d visualise map
#   2. EA options:
#         a. parameters setup
#         b. run the solver
#         c. visualise the statistics
#         d. view the drone moving on a path
#              function gui.movingDrone(currentMap, path, speed, markseen)
#              ATTENTION! the function doesn't check if the path passes trough walls

