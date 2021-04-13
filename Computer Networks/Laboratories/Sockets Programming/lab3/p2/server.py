# Server returns the lenght of the file and its content
# the receiver
import socket
import sys

IP = "127.0.0.1"
PORT = 5005
addr = (IP, PORT)
timeout = 3

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(addr)

data, client_addr = sock.recvfrom(1024)
if data:
    print(f"File name: {data.decode('utf-8')}")
    try:
        lines = open(data.decode('utf-8'), "r")
        content = ""
        for line in lines:
            content += line
        length = len(content)
        sock.sendto(str(length).encode('utf-8'), client_addr)
        sock.sendto(content.encode('utf-8'), client_addr)
    except FileNotFoundError:
        sock.sendto("-1".encode('utf-8'), client_addr)
else:
    print("Ce vrei ba?")
