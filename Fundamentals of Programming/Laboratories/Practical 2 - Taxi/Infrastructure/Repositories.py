from Errors.Exceptions import RepoError


class Repository:
    def __init__(self):
        self._entities = []

    def add(self, elem):
        if elem in self._entities:
            raise RepoError("Id already exists!\n")
        self._entities.append(elem)

    def get_all(self):
        return self._entities[:]


class FileRepository(Repository):
    def __init__(self, filename, read_object, write_object):
        self.__filename = filename
        self.__read_object = read_object
        self.__write_object = write_object
        Repository.__init__(self)

    def __read_all_from_file(self):
        self._entities = []
        with open(self.__filename, "r") as f:
            lines = f.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    obj = self.__read_object(line)
                    self._entities.append(obj)

    def __write_all_to_file(self):
        with open(self.__filename, "w") as f:
            for obj in self._entities:
                line = self.__write_object(obj)
                f.write(line + "\n")

    def add(self, elem):
        self.__read_all_from_file()
        Repository.add(self, elem)
        self.__write_all_to_file()

    def get_all(self):
        self.__read_all_from_file()
        return Repository.get_all(self)
