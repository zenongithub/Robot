import socket

def start_server():
    host = '192.168.1.11'
    port = 80

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((host, port))
    server_socket.listen(5)

    print(f"Listening on {host}:{port}...")

    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Accepted connection from {client_address}")

        data = client_socket.recv(1024).decode('utf-8')
        print(f"Received data: {data}")

        # Prepare HTML response with sensor data
        html_response = f"""\
<html>
<head>
    <title>Sensor Data</title>
</head>
<body>
    <h1>Sensor Data</h1>
    <p>Received data: {data}</p>
</body>
</html>
"""
        response = f"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n{html_response}"
        client_socket.send(response.encode('utf-8'))

        client_socket.close()

if __name__ == "__main__":
    start_server()
