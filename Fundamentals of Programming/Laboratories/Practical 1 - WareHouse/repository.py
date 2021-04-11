from Model import *

def repoAddProduct(l, product):
    '''
        Function that adds a product to a list
        input: l - a list
               product - a product
    '''
    l.append(product)

def repoRemoveProduct(l, name):
    ok = 0
    for x in l:
        if getName(x) == name:
            l.remove(x)
            ok = 1
    if ok == 0:
        raise Exception("Item does not exist!\n")

def repoGetTotal(l):
    total = 0
    for x in l:
        total = total + getPrice(x) * getQuantity(x)
    return total