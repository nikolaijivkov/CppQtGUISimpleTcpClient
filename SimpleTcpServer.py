#!python

import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 5005

try:
    print("opening socket address %s : %d" % (TCP_IP, TCP_PORT))
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(2)
    s.bind((TCP_IP, TCP_PORT))
    s.listen(1)
    print("socked opened and binded, now listening...")
    counter = 0
    while(True):
        try:
            conn, addr = s.accept()  # blocking until client is connected
            counter += 1
            conn.send("Hello from python %d\n" % counter)
            conn.send("connected peer: %s : %d\n\n" % (addr[0], addr[1]))
            conn.close()
        except socket.timeout:
            pass
except KeyboardInterrupt:
    s.close()
