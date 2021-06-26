import pygame
import timeit
from queue import PriorityQueue
import heapq

# Creating some colors
BLUE = (0, 0, 255)
GRAYBLUE = (50, 120, 120)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)


class Controller:
    @staticmethod
    def calculateManhattan(source, dest):
        return abs(source[0] - dest[0]) + abs(source[1] - dest[0])

    def searchGreedy(self, mapM, drone, initialX, initialY, finalX, finalY):
        start = timeit.default_timer()

        visited = []
        to_visit = PriorityQueue()
        to_visit.put((0, (initialX, initialY)))
        came_from = {(initialX, initialY): None}

        while not to_visit.empty():
            current = to_visit.get()
            current = current[1]
            visited.append(current)

            if current == (finalX, finalY):
                break

            if current[0] > 0:
                next_node = (current[0] - 1, current[1])
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    if next_node not in visited:
                        priority = self.calculateManhattan(next_node, (finalX, finalY))
                        to_visit.put((priority, next_node))
                        came_from[next_node] = current
            if current[0] < 19:
                next_node = (current[0] + 1, current[1])
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    if next_node not in visited:
                        priority = self.calculateManhattan(next_node, (finalX, finalY))
                        to_visit.put((priority, next_node))
                        came_from[next_node] = current
            if current[1] > 0:
                next_node = (current[0], current[1] - 1)
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    if next_node not in visited:
                        priority = self.calculateManhattan(next_node, (finalX, finalY))
                        to_visit.put((priority, next_node))
                        came_from[next_node] = current
            if current[1] < 19:
                next_node = (current[0], current[1] + 1)
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    if next_node not in visited:
                        priority = self.calculateManhattan(next_node, (finalX, finalY))
                        to_visit.put((priority, next_node))
                        came_from[next_node] = current

        stop = timeit.default_timer()
        print('Time: ', stop - start)
        return self.construct_path(came_from, (initialX, initialY), (finalX, finalY))

    @staticmethod
    def construct_path(came_from, source, dest):
        path = []
        if dest not in came_from:
            return None

        current = came_from[dest]
        while current != source:
            path.insert(0, current)
            current = came_from[current]
        return path

    def searchAStar(self, mapM, droneD, initialX, initialY, finalX, finalY):
        start = timeit.default_timer()

        to_visit = []
        heapq.heappush(to_visit, (0, (initialX, initialY)))
        # to_visit.put((0, (initialX, initialY)))
        came_from = {}
        cost_so_far = {(initialX, initialY): 0}
        came_from[(initialX, initialY)] = None

        while to_visit:
            current = heapq.heappop(to_visit)
            # current = to_visit.get()
            current = current[1]

            if current == (finalX, finalY):
                break

            if current[0] > 0:
                next_node = (current[0] - 1, current[1])
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    new_cost = cost_so_far[current] + 1
                    if next_node not in cost_so_far \
                            or new_cost < cost_so_far[next_node]:
                        cost_so_far[next_node] = new_cost
                        priority = new_cost + self.calculateManhattan(next_node, (finalX, finalY))
                        # to_visit.put((priority, next_node))

                        if next_node not in to_visit:
                            heapq.heappush(to_visit, (priority, next_node))
                        elif next_node in to_visit:
                            for x in to_visit:
                                if x[1] == next_node:
                                    x[0] = priority
                                    break
                            heapq.heapify(to_visit)

                        came_from[next_node] = current
            if current[0] < 19:
                next_node = (current[0] + 1, current[1])
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    new_cost = cost_so_far[current] + 1
                    if next_node not in cost_so_far \
                            or new_cost < cost_so_far[next_node]:
                        cost_so_far[next_node] = new_cost
                        priority = new_cost + self.calculateManhattan(next_node, (finalX, finalY))

                        if next_node not in to_visit:
                            heapq.heappush(to_visit, (priority, next_node))
                        elif next_node in to_visit:
                            for x in to_visit:
                                if x[1] == next_node:
                                    x[0] = priority
                                    break
                            heapq.heapify(to_visit)
                        # to_visit.put((priority, next_node))
                        came_from[next_node] = current
            if current[1] > 0:
                next_node = (current[0], current[1] - 1)
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    new_cost = cost_so_far[current] + 1
                    if next_node not in cost_so_far \
                            or new_cost < cost_so_far[next_node]:
                        cost_so_far[next_node] = new_cost
                        priority = new_cost + self.calculateManhattan(next_node, (finalX, finalY))

                        if next_node not in to_visit:
                            heapq.heappush(to_visit, (priority, next_node))
                        elif next_node in to_visit:
                            for x in to_visit:
                                if x[1] == next_node:
                                    x[0] = priority
                                    break
                            heapq.heapify(to_visit)
                        # to_visit.put((priority, next_node))
                        came_from[next_node] = current
            if current[1] < 19:
                next_node = (current[0], current[1] + 1)
                if mapM.surface[next_node[0]][next_node[1]] in [0, 2, 3]:
                    new_cost = cost_so_far[current] + 1
                    if next_node not in cost_so_far \
                            or new_cost < cost_so_far[next_node]:
                        cost_so_far[next_node] = new_cost
                        priority = new_cost + self.calculateManhattan(next_node, (finalX, finalY))

                        if next_node not in to_visit:
                            heapq.heappush(to_visit, (priority, next_node))
                        elif next_node in to_visit:
                            for x in to_visit:
                                if x[1] == next_node:
                                    x[0] = priority
                                    break
                            heapq.heapify(to_visit)
                        # to_visit.put((priority, next_node))
                        came_from[next_node] = current

        stop = timeit.default_timer()
        print('Time: ', stop - start)
        return self.construct_path(came_from, (initialX, initialY), (finalX, finalY))

    @staticmethod
    def dummysearch():
        # example of some path in test1.map from [5,7] to [7,11]
        return [[5, 7], [5, 8], [5, 9], [5, 10], [5, 11], [6, 11], [7, 11]]

    @staticmethod
    def displayWithPath(image, path):
        mark = pygame.Surface((20, 20))
        mark.fill(GREEN)
        for move in path:
            image.blit(mark, (move[1] * 20, move[0] * 20))

        return image
