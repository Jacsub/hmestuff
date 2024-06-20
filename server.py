
import socket

HOST = "0.0.0.0"  # Standard loopback interface address (localhost)
PORT = 5000 # Port to listen on (non-privileged ports are > 1022)

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    with conn:
        print(f"Connected by {addr}")
        while True:
           conn.sendall(bytes(96)) 


