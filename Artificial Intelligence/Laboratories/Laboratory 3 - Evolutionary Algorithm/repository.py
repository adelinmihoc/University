# -*- coding: utf-8 -*-

import pickle
from domain import *


class Repository:
    def __init__(self):
         
        self.__populations = []
        self.cmap = Map()
        
    def createPopulation(self, args):
        # args = [populationSize, individualSize] -- you can add more args
        population = Population(args[0], args[1])
        self.__populations.append(population)
        return population
        
    # TO DO : add the other components for the repository: 
    #    load and save from file, etc
