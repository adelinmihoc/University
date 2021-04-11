from Presentation.UserInterface import Console
from Business.Services import AppService
from Infrastructure.Repositories import FileRepository
from Domain.Entities import Address
from Domain.Validators import ValidateAddress

addRepo = FileRepository("Addresses.txt", Address.read_address, Address.write_address)
addValid = ValidateAddress()

appSrv = AppService(addRepo, addValid)

ui = Console(appSrv)

ui.run()