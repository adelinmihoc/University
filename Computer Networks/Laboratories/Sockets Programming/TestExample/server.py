# TEACHER
#  the teacher using select and TCP it waits for questions
#   from the group leaders. 
# the group leaders know the IP and the port that the teacher 
#   listens on
# when a question is received, the server generates the 
#   response (string and array of integers) (random)
#   and sends back the response to the group leader

import socket
import select
import random 
import string


IP = "127.0.0.1"
PORT = 9999

teacher_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

teacher_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

teacher_sock.bind((IP, PORT))

teacher_sock.listen()

sockets_list = [teacher_sock]


print(f"Teacher listening to incomming questions on {IP}:{PORT}...")

def generate_answer():
    letters = string.ascii_lowercase
    result = ''.join(random.choice(letters) for i in range(10))
    result += '.'
    return result

def receive_message(student_socket):
    try:
        question = student_socket.recv(1024)
        return question
    except:
        return False

while True:
    read_sockets, _, exception_sockets = select.select(sockets_list, [], sockets_list)

    for notified_socket in read_sockets:
        if notified_socket == teacher_sock:
            student_sock, student_addr = teacher_sock.accept()
            sockets_list.append(student_sock)
        else:
            question = receive_message(notified_socket)
            if question is False:
                print("Close connection with the student")
                sockets_list.remove(notified_socket)
                continue
            print(f"Received a question: {question.decode('utf-8')}")
            for sock in sockets_list:
                if sock == notified_socket:
                    answer = ""
                    answer += question.decode('utf-8')
                    answer += " -> "
                    answer += generate_answer()
                    sock.send(bytes(answer, 'utf-8'))
                    print("Answer sent!")

    for notified_socket in exception_sockets:
        sockets_list.remove(notified_socket)

