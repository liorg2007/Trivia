import socket
import json

PORT = 6969

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", PORT))
    print("Connected successfully to port", PORT)

    msg = json.dumps({ "username": "username", "password": "1234567" })
    packet = b'\x00' + len(msg).to_bytes(4, 'big') + msg.encode('ascii')

    s.sendall(packet)
    print("Recieved:", s.recv(1024))
    s.close()


if __name__ == '__main__':
    main()