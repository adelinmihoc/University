from Model import *

def validateProduct(product):
    errors = ""
    if getQuantity(product) < 0:
        errors += "Invalid quantity value! value < 0!\n"
    if getPrice(product) < 0:
        errors += "Invalid price value! value < 0!\n"
    if len(errors) > 0:
        raise Exception(errors)
