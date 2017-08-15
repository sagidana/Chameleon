import socket
import time


if __name__ == '__main__':
	TCP_IP = '0.0.0.0'
	TCP_PORT = 1337
						
	shellcode_to_test = ( 
						# xor    eax,eax
						"\x31\xc0" +
						# push   eax
						"\x50" +
						# push   0x68732f2f
						"\x68\x2f\x2f\x73\x68" +
						# push   0x6e69622f
						"\x68\x2f\x62\x69\x6e" +
						# mov    ecx,esp
						"\x89\xe1" +
						# mov    edx,0x9
						"\xba\x09\x00\x00\x00" +
						# mov    eax,0x4
						"\xb8\x04\x00\x00\x00" +
						# mov    ebx,0x1
						"\xbb\x01\x00\x00\x00" +
						# int    0x80
						"\xcd\x80" +
						# add    esp,0xc
						"\x83\xc4\x0c" +
						# ret
						"\xc3"
						)


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

