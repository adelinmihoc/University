import unittest
from Business.Services import AppService
from Infrastructure.Repositories import FileRepository
from Domain.Entities import Address
from Domain.Validators import ValidateAddress


class Test(unittest.TestCase):
    def test_third(self):
        addRepo = FileRepository("Addresses.txt", Address.read_address, Address.write_address)
        addValid = ValidateAddress()
        appSrv = AppService(addRepo, addValid)
        rez = appSrv.determine_addresses(1, 1, 1000)
        self.assertEqual(rez[0][1], 21.95449840010015)
        self.assertEqual(rez[1][1], 110.46266337545913)
