import pygame
from pygame.locals import *


class Drone:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def move(self, detected_map):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detected_map.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detected_map.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detected_map.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detected_map.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def move_dsf(self, stack, visited, parent, detected_map):
        if (self.x, self.y) not in visited:
            visited.append((self.x, self.y))

        # up neighbour
        if self.x > 0:
            if detected_map.get_surface()[self.x - 1][self.y] == 0 and (self.x - 1, self.y) not in visited:
                parent[(self.x - 1, self.y)] = (self.x, self.y)
                stack.append((self.x - 1, self.y))
        # down neighbour
        if self.x < 19:
            if detected_map.get_surface()[self.x + 1][self.y] == 0 and (self.x + 1, self.y) not in visited:
                parent[(self.x + 1, self.y)] = (self.x, self.y)
                stack.append((self.x + 1, self.y))
        # left neighbour
        if self.y > 0:
            if detected_map.get_surface()[self.x][self.y - 1] == 0 and (self.x, self.y - 1) not in visited:
                parent[(self.x, self.y - 1)] = (self.x, self.y)
                stack.append((self.x, self.y - 1))
        # right neighbour
        if self.y < 19:
            if detected_map.get_surface()[self.x][self.y + 1] == 0 and (self.x, self.y + 1) not in visited:
                parent[(self.x, self.y + 1)] = (self.x, self.y)
                stack.append((self.x, self.y + 1))

        if len(stack):
            next_pos = stack.pop()
            if next_pos not in [(self.x - 1, self.y), (self.x + 1, self. y),
                                (self.x, self.y - 1), (self.x, self.y + 1)]:
                stack.append(next_pos)
                next_pos = parent[(self.x, self.y)]

            self.x = next_pos[0]
            self.y = next_pos[1]





