import socket
import time


# Replace with Arduino's IP, can be seen in the serial monitor
arduino_ip = '10.0.0.129'
arduino_port = 20983

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    client_socket.connect((arduino_ip, arduino_port))
    time.sleep(5)  # Delay to ensure Arduino setup
    print("Started")

    payload = "20,20\n"
    client_socket.sendall(payload.encode())

except KeyboardInterrupt:
    client_socket.close()
