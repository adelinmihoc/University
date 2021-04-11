class Address:
    def __init__(self, a_id, name, number, x, y):
        self.__a_id = a_id
        self.__name = name
        self.__number = number
        self.__x = x
        self.__y = y

    def get_id(self):
        return self.__a_id

    def get_name(self):
        return self.__name

    def get_number(self):
        return self.__number

    def get_x(self):
        return self.__x

    def get_y(self):
        return self.__y

    def __eq__(self, other):
        return self.__a_id == other.__a_id

    def __str__(self):
        return "Id: " + str(self.__a_id) +\
               "\nName: " + self.__name +\
               "\nNumber: " + str(self.__number) +\
               "\nX: " + str(self.__x) +\
               "\nY: " + str(self.__y)

    @staticmethod
    def read_address(line):
        parts = line.split(",")
        return Address(int(parts[0]), parts[1], int(parts[2]), int(parts[3]), int(parts[4]))

    @staticmethod
    def write_address(address):
        return str(address.get_id())+ "," + str(address.get_name()) +","+ str(address.get_number()) +","+ str(address.get_x())+"," +\
               str(address.get_y())
