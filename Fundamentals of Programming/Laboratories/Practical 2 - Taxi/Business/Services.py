from Domain.Entities import Address
import math


class AppService:
    def __init__(self, addRepo, addValid):
        self.__repository = addRepo
        self.__validator = addValid

    def add(self, a_id, name, number, x, y):
        address = Address(a_id, name, number, x, y)
        self.__validator.validate_address(address)
        self.__repository.add(address)

    def get_addresses(self):
        return self.__repository.get_all()

    def determine_addresses(self, x1, y1, d):
        """
        Function that calculates the distance between all addresses and a given point(x,y) and determines the
        ones that are lesser then a given distance
        :param x1: int
        :param y1: int
        :param d: int
        :return: rez[] - a list containing the addresses and the distances
        """
        rez = []
        addresses = self.__repository.get_all()
        for address in addresses:
            x2 = address.get_x()
            y2 = address.get_y()
            distance = math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)
            if distance < d:
                rez.append([address, distance])
        return rez
