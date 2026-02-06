import socket

srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
srv.bind(('127.0.0.1', 8080))
srv.listen(5)

conn, addr = srv.accept()
data = conn.recv(1025)
conn.sendall(b'hello client')
print(data)
conn.close()