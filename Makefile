CFLAGS=#-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

server: server.c ipv4tcpserver.o ipv4udpserver.o
	gcc $(CFLAGS) server.c -o server ipv4tcpserver.o ipv4udpserver.o

client: client.c ipv4tcpclient.o ipv4udpclient.o
	gcc $(CFLAGS) client.c -o client ipv4tcpclient.o ipv4udpclient.o

ipv4tcpserver.o: ipv4tcpserver.c ipv4tcpserver.h
	gcc $(CFLAGS) -c ipv4tcpserver.c

ipv4udpserver.o: ipv4udpserver.c ipv4udpserver.h
	gcc $(CFLAGS) -c ipv4udpserver.c

#ipv6server: ipv6server.c
#	gcc $(CFLAGS) ipv6server.c -o ipv6server

#ipv6client: ipv6client.c
#	gcc $(CFLAGS) ipv6client.c -o ipv6client

ipv4tcpclient.o: ipv4tcpclient.c ipv4tcpclient.h
	gcc $(CFLAGS) -c ipv4tcpclient.c

ipv4udpclient.o: ipv4udpclient.c ipv4udpclient.h
	gcc $(CFLAGS) -c ipv4udpclient.c

clean:
	rm -f *.o