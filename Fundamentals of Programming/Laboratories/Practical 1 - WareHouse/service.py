from Model import *
from repository import *
from validate import *

def serviceAdd(l, name, quantity, price):
    '''
        Function that creates a product, validates the product and adds the product to a list
        input: l - a list
               name- string
               quantity - integer
               price - integer
    '''
    product = createProduct(name, quantity, price)
    if getQuantity(product) < 0:
        raise Exception("Invalid quantity")
    if getPrice(product) < 0:
        raise Exception("Invalid price!")
    repoAddProduct(l, product)

def serviceRemove(l, name):
    repoRemoveProduct(l, name)
    
def serviceListTotal(l):
    total = repoGetTotal(l)
    return total
