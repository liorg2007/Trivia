import socket
import json

PORT = 6969
LOGIN_CODE = 0
SIGNUP_CODE = 1

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)

    send_json(s, LOGIN_CODE, { "username": "username", "password": "1234567" })
    print("Recieved for login:", s.recv(1024))

    send_json(s, SIGNUP_CODE, { "username": "username", "password": "1234567", "email": "gever@gmail.com" })
    print("Recieved for signup:", s.recv(1024))

    s.close()

def send_json(sock: socket, code: int, obj: dict):
    msg = json.dumps(obj)
    login_packet = code.to_bytes(1, 'little') + len(msg).to_bytes(4, 'little') + msg.encode('ascii')

    sock.sendall(login_packet)

if __name__ == '__main__':
    main()