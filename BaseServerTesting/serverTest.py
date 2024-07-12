import socket
import json

PORT = 6969
LOGIN_CODE = 1
SIGNUP_CODE = 2

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)

    send_json(s, SIGNUP_CODE, { "username": "mrBruh", "password": "#Aa1234567", "email": "gever@gmail.com", "address": "abc,1,ff", "phoneNumber": "0523411223", "birthDate": "14/03/2006" })
    print("Recieved for signup:", s.recv(1024))
    
    send_json(s, LOGIN_CODE, { "username": "mrBruh", "password": "#Aa1234567" })
    print("Recieved for login:", s.recv(1024))


    s.close()

def send_json(sock: socket, code: int, obj: dict):
    msg = json.dumps(obj)
    login_packet = code.to_bytes(1, 'little') + len(msg).to_bytes(4, 'little') + msg.encode('ascii')

    sock.sendall(login_packet)

if __name__ == '__main__':
    main()