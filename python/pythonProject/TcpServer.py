import socket

def tcp_server(host="127.0.0.1", port=12345):
    server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_socket.bind((host,port))
    server_socket.listen(5)
    print(f"[*] 服务器启动, 监听 {host}:{port}")

    while True:
        client_socket, addr = server_socket.accept() # return sock 和 addr
        print(f"[+] 连接来自 {addr}")

        while True:
            data = client_socket.recv(1024)
            if not data:
                break

            print(f"[客户端] {data.decode()}")
            client_socket.sendall(b"Message received")

        client_socket.close()
        print(f"[-] 连接断开 {addr}")

if __name__ == "__main__":
    tcp_server()