
from repository import *
from Model import *
from service import *

def testRepoAdd():
    l = []
    product = createProduct("Napkins", 120, 5)
    repoAddProduct(l, product)
    assert len(l) == 1
    assert l == [product]

def testServiceAdd():
    l = []
    name = "Napkins"
    quantity = 120
    price = 5
    serviceAdd(l, name, quantity, price)
    assert len(l) == 1
    assert getName(l[0]) == "Napkins"
    assert getQuantity(l[0]) == 120
    assert getPrice(l[0]) == 5

