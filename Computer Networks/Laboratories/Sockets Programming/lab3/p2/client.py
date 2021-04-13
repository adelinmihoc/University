# client sends path to file
# the sender
import socket
import time
import sys

IP = "127.0.0.1"
PORT = 5005
addr = (IP, PORT)
buf = 1024
file_name = sys.argv[1]

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(file_name.encode('utf-8'), addr)
print(f"Sending {file_name}")
try:
    data, _ = sock.recvfrom(1024)
    print(f"Data length: {data.decode('utf-8')}")
    sock.settimeout(2)
    if int(data) != -1:
        data, _ = sock.recvfrom(1024)
        print("File content:")
        print(data.decode('utf-8'))
    else:
        print("ba cica nu exista")
except timeout:
    sock.close()
    print("Nu i bine ba")
