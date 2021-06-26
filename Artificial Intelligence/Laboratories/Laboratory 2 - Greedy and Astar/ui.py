from random import randint

import pygame
import time

from domain import Drone, Map

# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3


class UserInterface:
    def __init__(self, controller):
        self.controller = controller
        self.m = Map()
        self.drone = Drone(0, 0)

    @staticmethod
    def menu():
        print("Pathfinding algorithms:\n"
              " 1. A*\n"
              " 2. Greedy\n")
        option = input("Input option:\n>>>")
        return option

    def main(self):
        option = self.menu()

        # m.randomMap()
        # m.saveMap("test2.map")
        self.m.loadMap("test1.map")

        # initialize the pygame module
        pygame.init()
        # load and set the logo
        logo = pygame.image.load("logo32x32.png")
        pygame.display.set_icon(logo)
        pygame.display.set_caption("Path in simple environment")

        # we position the drone somewhere in the area
        x = randint(0, 19)
        y = randint(0, 19)

        while self.m.surface[x][y] != 0:
            x = randint(0, 19)
            y = randint(0, 19)

        # x = 14
        # y = 18

        # create drona
        self.drone = Drone(x, y)

        # destination
        x_d = randint(0, 19)
        y_d = randint(0, 19)

        while self.m.surface[x_d][y_d] != 0:
            x_d = randint(0, 19)
            y_d = randint(0, 19)

        # x_d = 1
        # y_d = 7
        #
        # print((x,y))
        # print((x_d, y_d))
        # print("Old Time:  0.0005340000000018108")

        self.m.surface[x][y] = 2  # mark start
        self.m.surface[x_d][y_d] = 3  # mark destination

        # create a surface on screen that has the size of 400 x 480
        screen = pygame.display.set_mode((400, 400))
        screen.fill(WHITE)

        # define a variable to control the main loop
        running = True

        # main loop
        while running:
            # event handling, gets all event from the event queue
            for event in pygame.event.get():
                # only do something if the event is of type QUIT
                if event.type == pygame.QUIT:
                    # change the value to False, to exit the main loop
                    running = False

                # if event.type == KEYDOWN:
                #     self.drone.move(self.m)  # this call will be erased

            screen.blit(self.drone.mapWithDrone(self.m.image()), (0, 0))
            pygame.display.flip()

        if option == "1":
            path = self.controller.searchAStar(self.m, self.drone, x, y, x_d, y_d)
        else:
            path = self.controller.searchGreedy(self.m, self.drone, x, y, x_d, y_d)

        if path is not None:
            screen.blit(self.controller.displayWithPath(self.m.image(), path), (0, 0))
        else:
            print("No path")

        pygame.display.flip()
        time.sleep(3)
        pygame.quit()
