import socket
import time


if __name__ == '__main__':
	TCP_IP = '0.0.0.0'
	TCP_PORT = 1337

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	s.bind((TCP_IP, TCP_PORT))
	s.listen(1)
	client, addr = s.accept()
	
	while True:
		try:
			client.send('A'*10)
			time.sleep(2)
		except KeyboardInterrupt:
			break

	client.close()

