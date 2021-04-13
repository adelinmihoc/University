import pygame

from Service.ACO_service import AcoService
from Utils import *
from Domain.Button import Button
from random import *
from Domain.InputBox import InputBox
import time


class GUI:
    def __init__(self, map_service, ea_service):
        pygame.init()
        self.screen = pygame.display.set_mode((WIDTH, HEIGHT))
        pygame.display.set_caption("AI Algorithms")
        pygame.display.set_icon(pygame.image.load("Assets/logo32x32.png"))
        self.clock = pygame.time.Clock()
        self.running = True
        self.buttons = None
        self.surfaces = []
        self.input_boxes = []
        self.create_main_menu_buttons()

        self.map_service = map_service
        self.ea_service = ea_service

    def processInput(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
                break
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:
                    pos = pygame.mouse.get_pos()
                    for button in self.buttons:
                        if button.rect.collidepoint(pos):
                            button.call_back()
            for box in self.input_boxes:
                box.handle_event(event)

    def render(self):
        self.screen.fill(WHITE)

        img = pygame.image.load("Assets/menu_img.png")
        self.screen.blit(img, (0, 0))

        for button in self.buttons:
            button.draw(self.screen)

        for surface in self.surfaces:
            self.screen.blit(surface[0], surface[1])

        for box in self.input_boxes:
            box.update()

        for box in self.input_boxes:
            box.draw(self.screen)

        pygame.display.update()

    def run(self):
        while self.running:
            self.processInput()
            self.render()
            self.clock.tick(FPS)
        pygame.quit()

    def moving_drone(self, path, speed=1, markSeen=True):
        # animation of a drone on a path

        drona = pygame.image.load("Assets/drona.png")
        self.screen.blit(self.map_service.map_image(), (0, 0))
        self.screen.blit(drona, (path[0][1] * 20, path[0][0] * 20))
        pygame.display.flip()

        self.key_pressed_waiting()

        for i in range(len(path)):
            self.screen.blit(self.map_service.map_image(), (0, 0))

            if markSeen:
                brick = pygame.Surface((20, 20))
                brick.fill(GREEN)
                for j in range(i + 1):
                    for var in v:
                        x = path[j][0]
                        y = path[j][1]
                        while ((0 <= x + var[0] < self.map_service.get_map().n and
                                0 <= y + var[1] < self.map_service.get_map().m) and
                               self.map_service.get_map().surface[x + var[0]][y + var[1]] != 1):
                            x = x + var[0]
                            y = y + var[1]
                            self.screen.blit(brick, (y * 20, x * 20))

            self.screen.blit(drona, (path[i][1] * 20, path[i][0] * 20))
            pygame.display.flip()
            time.sleep(0.5 * speed)
        self.key_pressed_waiting()

    def display_map(self, position=(0, 0)):
        self.surfaces.append([self.map_service.map_image(), position])

    def key_pressed_waiting(self):
        while self.running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.running = False
                    break
                elif event.type == pygame.KEYDOWN:
                    return

    # main menu button handlers

    def algorithms_button(self):
        self.create_algorithms_buttons()

    def settings_button(self):
        self.display_map((0, 200))
        self.create_settings_buttons()

    def quit_button(self):
        self.running = False

    # algorithms button handlers

    def dfs_button(self):
        print("DFS clicked")

    def astar_button(self):
        print("A* clicked")

    def greedy_button(self):
        print("Greedy clicked")

    def ea_button(self):
        self.create_ea_buttons()

    def aco_button(self):
        print("ACO pressed")
        sensor1 = pygame.image.load("Assets/sensor.png")
        drona = pygame.image.load("Assets/drona.png")

        aco_service = AcoService(d_map=self.map_service.get_map())
        sensors = aco_service.get_sensors()

        markSeen = False
        speed = 0.3
        for path in aco_service.get_sensors_paths():
            for i in range(len(path)):
                self.screen.blit(self.map_service.map_image(), (0, 0))
                for sensor in sensors:
                    self.screen.blit(sensor1, (sensor[1] * 20, sensor[0] * 20))
                if markSeen:
                    brick = pygame.Surface((20, 20))
                    brick.fill(GREEN)
                    for j in range(i + 1):
                        for var in v:
                            x = path[j][0]
                            y = path[j][1]
                            while ((0 <= x + var[0] < self.map_service.get_map().n and
                                    0 <= y + var[1] < self.map_service.get_map().m) and
                                   self.map_service.get_map().surface[x + var[0]][y + var[1]] != 1):
                                x = x + var[0]
                                y = y + var[1]
                                self.screen.blit(brick, (y * 20, x * 20))

                self.screen.blit(drona, (path[i][1] * 20, path[i][0] * 20))

                pygame.display.flip()
                time.sleep(0.5 * speed)

    # other button handlers

    def main_menu_button(self):
        self.create_main_menu_buttons()
        self.surfaces = []
        self.input_boxes = []

    # settings button handlers

    def random_map_button(self):
        self.map_service.random_map()
        self.display_map((0, 200))

    def load_map_button(self):
        pass

    def save_map_button(self):
        pass

    # EA button handlers

    def run_all_populations_button(self):
        try:
            print("loading")
            pygame.display.flip()
            m = self.map_service.get_map()
            x = randint(0, 19)
            y = randint(0, 19)

            while m.surface[x][y] != 0:
                x = randint(0, 19)
                y = randint(0, 19)

            self.ea_service.set_starting_node((x, y))

            best_individuals, fitness_list, average, stddev, seeds = self.ea_service.run(self.map_service.get_map())
            # print("Seeds: " + str(seeds))
            print("Best path: " + str(best_individuals[0].to_path((x, y))))
            for i in range(len(seeds)):
                print("No. run: " + str(i) + "| Seed: " + str(seeds[i]) + "| Fitness: " + str(fitness_list[i]))
            # print("Fitness list:" + str(fitness_list))
            print("Average: " + str(average))
            print("Std deviation: " + str(stddev))
            path = best_individuals[0].to_path((x, y))
            self.moving_drone(path)
        except ValueError:
            print("error")

    # EA text input handlers

    def set_individual_size(self, text):
        self.ea_service.set_individual_size(int(text))
        print("Individual size = " + str(self.ea_service.get_individual_size()))

    def set_population_size(self, text):
        self.ea_service.set_population_size(int(text))
        print("Population size = " + str(self.ea_service.get_population_size()))

    def set_no_of_iteration(self, text):
        self.ea_service.set_no_of_iterations(int(text))
        print("# iterations = " + str(self.ea_service.get_no_of_iterations()))

    def set_no_of_populations(self, text):
        self.ea_service.set_no_of_populations(int(text))
        print("# populations = " + str(self.ea_service.get_no_of_populations()))

    # buttons to be displayed

    def create_main_menu_buttons(self):
        button1 = Button(position=(300, 230), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.algorithms_button, text="Algorithms")
        button2 = Button(position=(300, 330), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.settings_button, text="Map settings")
        button3 = Button(position=(300, 430), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.quit_button, text="Quit")
        self.buttons = [button1, button2, button3]

    def create_algorithms_buttons(self):
        button1 = Button(position=(300, 230), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.dfs_button, text="DFS")
        button2 = Button(position=(300, 290), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.astar_button, text="A*")
        button3 = Button(position=(300, 350), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.greedy_button, text="Greedy")
        button4 = Button(position=(300, 410), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.ea_button, text="EA")
        button5 = Button(position=(300, 470), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.aco_button, text="ACO")
        button6 = Button(position=(300, 530), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.main_menu_button, text="Main menu")
        self.buttons = [button1, button2, button3, button4, button5, button6]

    def create_settings_buttons(self):
        button1 = Button(position=(500, 230), size=(150, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.random_map_button, text="Random map")
        button2 = Button(position=(500, 290), size=(150, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.astar_button, text="Load map")
        button3 = Button(position=(500, 350), size=(150, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.greedy_button, text="Save map")
        button4 = Button(position=(500, 410), size=(150, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.main_menu_button, text="Main menu")
        self.buttons = [button1, button2, button3, button4]

    def create_ea_buttons(self):
        button1 = Button(position=(85, 230), size=(150, 50), color=WHITE, text="Individual size:")
        button2 = Button(position=(85, 330), size=(150, 50), color=WHITE, text="Population size:")
        button3 = Button(position=(385, 230), size=(150, 50), color=WHITE, text="# iterations:")
        button4 = Button(position=(385, 330), size=(150, 50), color=WHITE, text="# populations:")

        input_box1 = InputBox(position=(208, 230), size=(100, 40), func=self.set_individual_size)
        input_box2 = InputBox(position=(208, 330), size=(100, 40), func=self.set_population_size)
        input_box3 = InputBox(position=(535, 230), size=(100, 40), func=self.set_no_of_iteration)
        input_box4 = InputBox(position=(535, 330), size=(100, 40), func=self.set_no_of_populations)

        self.input_boxes = [input_box1, input_box2, input_box3, input_box4]

        button5 = Button(position=(300, 430), size=(200, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.run_all_populations_button, text="Run")
        button6 = Button(position=(300, 530), size=(300, 50), color=LIGHT_GREY, change_color=DARK_GREY,
                         func=self.main_menu_button, text="Main Menu")
        self.buttons = [button1, button2, button3, button4, button5, button6]



