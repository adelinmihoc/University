import socket
import select

IP = "127.0.0.1"
PORT = 7000

server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

server_sock.bind((IP,PORT))

server_sock.listen()

sockets_list = [server_sock]

clients = {}

def receive_message(sock):
    try:
        data = sock.recv(1024)
        return data
    except:
        return False

while True:
    read_socks, _, exc_socks = select.select(sockets_list, [], sockets_list)

    for notified_sock in read_socks:
        if notified_sock == server_sock:
            client_sock, client_addr = server_sock.accept()
            sockets_list.append(client_sock)
            clients[client_sock] = client_addr
            print(clients[client_sock])
        else:
            data = receive_message(notified_sock)
            if data is False:
                print("Closed connection")
                sockets_list.remove(notified_sock)
                del clients[notified_sock]
            else:
                print(data.decode('utf-8'))
                clnt = []
                for key in clients:
                    clnt.append(clients[key])
                clnt = str(clnt)
                notified_sock.send(bytes(clnt, 'utf-8'))

    for notified_sock in exc_socks:
        print(f"Connection lost with {clients[notified_sock]}")
        sockets_list.remove(notified_sock)
        del clients[notified_sock]
