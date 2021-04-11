from service import *
from Model import *
from tests import *

def addProduct(l, cmd):
    parts = cmd.split(" ")
    try:
        name = parts[1]
        quantity = parts[2]
        price = parts[3]
    except Exception:
        print("Command needs 3 parameters!")
        return
    try:
        quantity = int(quantity)
        price = int(quantity)
    except ValueError:
        print("Invalid quantity or price!")
        return
    try:
        serviceAdd(l, name, quantity, price)
    except Exception as ex:
        print(str(ex))
        return

def removeProduct(l, cmd):
    parts = cmd.split(" ")
    try:
        name = parts[1]
    except Exception:
        print("Command needs 1 parameter!")
        return
    try:
        serviceRemove(l, name)
    except Exception as ex:
        print(str(ex))
        return

def listProducts(l):
    i = 1
    for x in l:
        print("Product number", i, ":")
        print("name:", getName(x))
        print("quantity:", getQuantity(x))
        print("price:", getPrice(x))
        i += 1
    
def listTotal(l):
    total = serviceListTotal(l)
    print("Total value of the products:", total)

def checkListCmd(l, cmd):
    if cmd == "list all":
        listProducts(l)
    elif cmd == "list total":
        listTotal(l)
    else:
        raise Exception("Invalid list command")
        

def checkCommand(l, cmd):
    if 'add' in cmd:
        addProduct(l, cmd)
    elif 'remove' in cmd:
        removeProduct(l, cmd)
    elif 'list' in cmd:
        try:
            checkListCmd(l, cmd)
        except Exception as ex:
            print(str(ex))
    else:
        print("Invalid command!")

def ui():
    l = []
    while True:
        cmd = input("Input command: ")
        if cmd == 'exit':
            return
        checkCommand(l, cmd)

ui()
testRepoAdd()
#testServiceAdd()