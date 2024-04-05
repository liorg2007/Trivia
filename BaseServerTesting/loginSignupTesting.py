import socket
import json

PORT = 6969
LOGIN_CODE = 0
SIGNUP_CODE = 1

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    Test3(s)



def Test1(s):
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s, LOGIN_CODE, { "username": "blahblahblahblah", "password": "1234567" })
    print("Recieved for login with non existent user:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "shimon", "password": "1234567", "email": "shimon@gmail.com" })
    print("Recieved for signup:", s.recv(1024))
    send_json(s, LOGIN_CODE, { "username": "shimon", "password": "1234567" })
    print("Recieved for login with existant user:", s.recv(1024))

    s.close()


def Test2(s):
    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "1234567", "email" : "lior@hah.com" })
    print("Recieved for signup for the first time:", s.recv(1024))

    s2.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT, "with another socket")
    send_json(s2, SIGNUP_CODE, { "username": "lior", "password": "3123123", "email" : "bbb@bruh.com" })
    print("Recieved for signup for the second time with the same username:", s.recv(1024))

    s2.close()
    s.close()


def Test3(s):
    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)

    send_json(s, LOGIN_CODE, { "username": "lior", "password": "1234567" })
    print("Recieved for signup:", s.recv(1024))

    s2.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s2, LOGIN_CODE, { "username": "lior", "password": "1234567" })
    print("Recieved for signup:", s2.recv(1024))

    s2.close()
    s.close()

def send_json(sock: socket, code: int, obj: dict):
    msg = json.dumps(obj)
    login_packet = code.to_bytes(1, 'little') + len(msg).to_bytes(4, 'little') + msg.encode('ascii')

    sock.sendall(login_packet)

if __name__ == '__main__':
    main()