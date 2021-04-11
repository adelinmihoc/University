from Errors.Exceptions import RepoError, AddressError


class Console:
    def __init__(self, appSrv):
        self.__app_service = appSrv
        self.__parameters = None

    def __ui_add(self):
        if len(self.__parameters) != 5:
            raise ValueError("Invalid no of parameters!\n")
        parts = self.__parameters
        self.__app_service.add(int(parts[0]), parts[1], int(parts[2]), int(parts[3]), int(parts[4]))

    def __ui_display(self):
        addresses = self.__app_service.get_addresses()
        print("***")
        for address in addresses:
            print(address)
            print("***")

    def __ui_determine_addresses(self):
        if len(self.__parameters) != 3:
            raise ValueError("Invalid no of parameters!\n")
        rez = self.__app_service.determine_addresses(int(self.__parameters[0]), int(self.__parameters[1]), int(self.__parameters[2]))
        print("***")
        for item in rez:
            print(item[0])
            print("Distance: " + str(item[1]))
            print("***")

    def run(self):
        commands = {
            "add": self.__ui_add,
            "display": self.__ui_display,
            "distance": self.__ui_determine_addresses
        }
        while True:
            print("To add type 'add,name,number,x,y'")
            print("To display type 'display'")
            print("To calculate blah blah type 'distance,x,y,d'")
            print("To exit type 'exit'\n")
            cmd = input("Insert command\n>>>")
            if cmd == 'exit':
                return
            parts = cmd.split(",")
            if parts[0] not in commands:
                print("Invalid command!\n")
            else:
                self.__parameters = parts[1:]
                try:
                    commands[parts[0]]()
                except ValueError as ve:
                    print("ui error:\n" + str(ve))
                except RepoError as re:
                    print("repo error:\n" + str(re))
                except AddressError as ae:
                    print("Address error:\n" + str(ae))