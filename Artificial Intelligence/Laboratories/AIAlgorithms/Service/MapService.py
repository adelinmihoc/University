from random import *
import pygame
from Utils import *
import numpy as np


class MapService:
    def __init__(self, d_map):
        self.d_map = d_map
        self.random_map()

    def load_map(self):
        pass

    def save_map(self):
        pass

    def random_map(self, fill=0.2):
        self.d_map.surface = np.zeros((self.d_map.n, self.d_map.m))
        for i in range(self.d_map.n):
            for j in range(self.d_map.m):
                if random() <= fill:
                    self.d_map.surface[i][j] = 1

    def reset_map(self):
        for i in range(self.d_map.n):
            for j in range(self.d_map.m):
                if self.d_map.surface[i][j] != 1:
                    self.d_map.surface[i][j] = 0

    def get_map(self):
        return self.d_map

    def map_image(self, color=BLUE, background=WHITE):
        imagine = pygame.Surface((self.d_map.n * 20, self.d_map.m * 20))
        brick = pygame.Surface((20, 20))
        brick.fill(color)
        imagine.fill(background)
        for i in range(self.d_map.n):
            for j in range(self.d_map.m):
                if self.d_map.surface[i][j] == 1:
                    imagine.blit(brick, (j * 20, i * 20))

        return imagine
