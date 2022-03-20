CFLAGS=#-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

server: server.c ipv4tcpserver.o
	gcc $(CFLAGS) server.c -o server ipv4tcpserver.o

ipv4tcpserver.o: ipv4tcpserver.c ipv4tcpserver.h
	gcc $(CFLAGS) -c ipv4tcpserver.c

#ipv6server: ipv6server.c
#	gcc $(CFLAGS) ipv6server.c -o ipv6server

#ipv6client: ipv6client.c
#	gcc $(CFLAGS) ipv6client.c -o ipv6client

#ipv4tcpclient: ipv4tcpclient.c
#	gcc $(CFLAGS) ipv4tcpclient.c -o ipv4tcpclient

#ipv4udpclient: ipv4udpclient.c
#	gcc $(CFLAGS) ipv4udpclient.c -o ipv4udpclient

clean:
	rm -f *.o