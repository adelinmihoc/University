import socket
import threading
import time

IP = "127.0.0.1"
PORT = 7000

client_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_sock.connect((IP,PORT))

udp_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
udp_sock.bind(("",PORT))



def receive_messages_udp():
    while True:
        data, _ = udp_sock.recvfrom(1024)
        print(f"Received message: {data.decode('utf-8')}")

t = threading.Thread(target=receive_messages_udp)
t.start()

clients = []
while True:
    try:
        message = 'Please update clients list!'
        client_sock.send(bytes(message, 'utf-8'))
        data = client_sock.recv(4096)
        data = data.decode('utf-8')
        data = eval(data)
        if clients == []:
            for i in data:
                print(f"Client {i} has connected!")
            clients = data
        else:
            for i in data:
                if i not in clients:
                    print(f"Client {i} has connected!")
            for i in clients:
                if i not in data:
                    print(f"Client {i} has disconnected!")
        msg = input("Input a message:")
        if msg == 'QUIT':
            client_sock.close()
            udp_sock.close()
            exit(0)
        else:
            for addr in data:
                udp_sock.sendto(bytes(msg,'utf-8'), (addr[0], PORT))
        time.sleep(1)
    except:
        continue

