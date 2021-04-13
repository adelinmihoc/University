import socket
import sys
import time
import threading
import string
import random


IP = "127.0.0.1"
PORT = int(sys.argv[1])
if sys.argv[2] == '1':
    LEADER = True
else:
    LEADER = False

broadcast_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
broadcast_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
broadcast_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
broadcast_sock.bind(("", int(sys.argv[1])))


def generate_question():
        letters = string.ascii_lowercase
        result_str = ''.join(random.choice(letters) for i in range(10))
        result_str += '?'
        return result_str

def send_msg_broadcast(message): #UDP
    broadcast_sock.sendto(bytes(message, 'utf-8'), ('<broadcast>', PORT))
    print("Message in broadcast sent!")

def receive_msg_broadcast(): #UDP
    data, _ = broadcast_sock.recvfrom(1024)
    print(f"Received message: {data.decode('utf-8')}")


def task1():
    if LEADER == True:
        while True:
            send_msg_broadcast("I am your leader!")
            time.sleep(5)
    else:
        while True:
            receive_msg_broadcast()

mylock = threading.Lock() 
questions = []

def task2():
    global mylock, questions

    if LEADER == True: # receives questions
        question_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        question_sock.bind(("0.0.0.0", PORT))
        question_sock.listen(5)
        while True:
            peer_sock, _ = question_sock.accept()
            data = peer_sock.recv(1024)
            print(f"Received question: {data.decode('utf-8')}")
            mylock.acquire()
            questions.append(data.decode('utf-8'))
            mylock.release()
            peer_sock.close()
    else:
        while True:
            try:
                s = socket.create_connection((IP, PORT))
                message = generate_question()
                s.send(bytes(message, 'utf-8'))
                s.close()
                time.sleep(3)
            except:
                continue

def task3():
    if LEADER == True:
        leader_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        leader_sock.connect((IP, 9999))
        leader_sock.setblocking(False)
        while True:
            try:
                if questions:
                    mylock.acquire()
                    question = questions.pop()
                    mylock.release()
                    leader_sock.send(bytes(question, 'utf-8'))
                    time.sleep(1)
                    response = leader_sock.recv(1024)
                    send_msg_broadcast(response.decode('utf-8'))
            except:
                continue

t1 = threading.Thread(target=task1)
t2 = threading.Thread(target=task2)
t3 = threading.Thread(target=task3)
t1.start()
t2.start()
t3.start()
