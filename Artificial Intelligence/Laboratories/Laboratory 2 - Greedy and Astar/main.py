from ui import UserInterface
from controller import Controller
from domain import Map


if __name__ == "__main__":
    ctrl = Controller()
    ui = UserInterface(ctrl)
    ui.main()
