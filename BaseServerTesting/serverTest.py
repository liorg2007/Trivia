import socket


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("127.0.0.1", 6969))

    s.sendall("Hello".encode())

    s.close()


if __name__ == '__main__':
    main()