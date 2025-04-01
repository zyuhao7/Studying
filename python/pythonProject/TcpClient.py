import socket

def tcp_client(host="127.0.0.1", port=12345):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, port))  # 连接服务器

    while True:
        msg = input("输入消息, (输入 exit 退出):")
        if msg.lower() == "exit":
            break

        client_socket.sendall(msg.encode())
        response = client_socket.recv(1024)  # 接收服务器响应
        print(f"[服务器] {response.decode()}")

    client_socket.close()

if __name__ == "__main__":
    tcp_client()
