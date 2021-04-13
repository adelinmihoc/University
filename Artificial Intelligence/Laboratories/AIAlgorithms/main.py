from View.GUI import GUI
from Service.MapService import MapService
from Service.EA_service import EaService

from Repository.EA_repository import EaRepository
from Domain.Map import Map


def main():
    m = Map()
    map_service = MapService(m)

    ea_repo = EaRepository()
    ea_service = EaService(ea_repo)

    gui = GUI(map_service, ea_service)
    gui.run()


if __name__ == '__main__':
    main()



