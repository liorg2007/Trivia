import socket
import json

PORT = 6969
LOGIN_CODE = 1
SIGNUP_CODE = 2

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    Test4(s)



def Test1(s):
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s, LOGIN_CODE, { "username": "lior", "password": "#Ahalan30" })
    print("Recieved for login with non existent user:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "shimon", "password": "1234567", "email": "shimon@gmail.com", "address" : "Shimon 12", "phoneNumber" : "0501231234", "birthDate" : "1/2/2007"  })
    print("Recieved for signup:", s.recv(1024))

    s.close()


def Test2(s):
    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "1234567", "email" : "lior@hah.com", "address" : "Shimon 12", "phoneNumber" : "0501231234", "birthDate" : "1/2/2007" })
    print("Recieved for signup for the first time:", s.recv(1024))

    s2.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT, "with another socket")
    send_json(s2, SIGNUP_CODE, { "username": "lior", "password": "3123123", "email" : "bbb@bruh.com", "address" : "Shimon 12", "phoneNumber" : "0501231234", "birthDate" : "1/2/2007"  })
    print("Recieved for signup for the second time with the same username:", s2.recv(1024))

    s2.close()
    s.close()


def Test3(s):
    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)

    send_json(s, LOGIN_CODE, { "username": "lior", "password": "1234567" })
    print("Recieved for login:", s.recv(1024))

    s2.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s2, LOGIN_CODE, { "username": "lior", "password": "1234567" })
    print("Recieved for login with same user:", s2.recv(1024))

    s2.close()
    s.close()

def Test4(s):
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)
    
    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "1234567", "email" : "lior@hah.com", "address" : "Shimon,12,Israel", "phoneNumber" : "0501231234", "birthDate" : "10/02/2007" })
    print("Recieved for bad password:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "#Ahalan30", "email" : "lior2hah.com", "address" : "Shimon,12,Israel", "phoneNumber" : "0501231234", "birthDate" : "10/02/2007" })
    print("Recieved for bad email:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "#Ahalan30", "email" : "lior@hah.com", "address" : "Shimon,1a2,Israel", "phoneNumber" : "0501231234", "birthDate" : "10/02/2007" })
    print("Recieved for bad address:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "#Ahalan30", "email" : "lior@hah.com", "address" : "Shimon,12,Israel", "phoneNumber" : "0501231234123123123", "birthDate" : "10/02/2007" })
    print("Recieved for bad phone number:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "lior", "password": "#Ahalan30", "email" : "lior@hah.com", "address" : "Shimon,12,Israel", "phoneNumber" : "0501231234", "birthDate" : "32/02/2007" })
    print("Recieved for bad birthdate:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "lior2", "password": "#Ahalan30", "email" : "lior@hah.com", "address" : "Shimon,12,Israel", "phoneNumber" : "0501231234", "birthDate" : "10/02/2007" })
    print("Recieved for good data:", s.recv(1024))

    s.close()


def send_json(sock: socket, code: int, obj: dict):
    msg = json.dumps(obj)
    login_packet = code.to_bytes(1, 'little') + len(msg).to_bytes(4, 'little') + msg.encode('ascii')

    sock.sendall(login_packet)

if __name__ == '__main__':
    main()