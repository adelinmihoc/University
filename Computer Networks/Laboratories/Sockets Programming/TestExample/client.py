# STUDENT
# each student reads from the command line 
#   a port number group_port a
#   and an integer that states 
#       if the student is the group leader 1 or not 0
# the group leader (every 5 seconds) sends the message 
#   "leader" the port group_port using broadcast to 
#   notify the students the he is the group leader
# the other students send questions (string), randomly from 
#   3 to 3 seconds to the leader
# the group leader will forward these questions to the teacher
#   using tcp. When the teacher responds, the group leader will
#   send the original question and the teachers response
#   on the group_port using broadcast
 
import socket
import sys
import time
import threading
import string
import random


class Student:
    PORT = 0
    IP = "127.0.0.1"
    leader = False

    def __init__(self, port, l_flag, sock):
        self.PORT = port
        self.leader = l_flag
        self.sock = sock
    
    def leader_broadcast(self, message):
        while True:
            self.sock.sendto(bytes(message, 'utf-8'), ('<broadcast>', self.PORT))
            print("Message sent!")
            time.sleep(5)

    @staticmethod
    def generate_question():
        letters = string.ascii_lowercase
        result_str = ''.join(random.choice(letters) for i in range(10))
        result_str += '?'
        return result_str

    def recieve_and_send(self):
        while True:
            data, addr = self.sock.recvfrom(1024)
            print(f"Received message: {data.decode('utf-8')}")
            question = self.generate_question()
            self.sock.sendto(question.encode('utf-8'), addr)            



student_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
student_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
student_sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
student_sock.bind(("", int(sys.argv[1])))

if sys.argv[2] == '1':
    student = Student(int(sys.argv[1]), True, student_sock)
else:
    student = Student(int(sys.argv[1]), False, student_sock)

print(student.sock)

def send_leader_message():
    if (student.leader == False):
        student.recieve_and_send()
    else:
        student.leader_broadcast("Ba eu is liderul")

e = threading.Event()
t = threading.Thread(target=send_leader_message)
t.start()
    
data, _ = student.sock.recvfrom(1024)
print(data.decode('utf-8'))


e.wait()
t.join()