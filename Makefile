CFLAGS=#-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

all: server client

server: server.c ipv4tcpserver.o ipv4udpserver.o ipv6server.o
	gcc $(CFLAGS) server.c -o server ipv4tcpserver.o ipv4udpserver.o ipv6server.o

client: client.c ipv4tcpclient.o ipv4udpclient.o ipv6client.o
	gcc $(CFLAGS) client.c -o client ipv4tcpclient.o ipv4udpclient.o ipv6client.o

ipv4tcpserver.o: ipv4tcpserver.c ipv4tcpserver.h
	gcc $(CFLAGS) -c ipv4tcpserver.c

ipv4udpserver.o: ipv4udpserver.c ipv4udpserver.h
	gcc $(CFLAGS) -c ipv4udpserver.c

ipv6server.o: ipv6server.c ipv6server.h
	gcc $(CFLAGS) -c ipv6server.c

ipv6client.o: ipv6client.c ipv6client.h
	gcc $(CFLAGS) -c ipv6client.c

ipv4tcpclient.o: ipv4tcpclient.c ipv4tcpclient.h
	gcc $(CFLAGS) -c ipv4tcpclient.c

ipv4udpclient.o: ipv4udpclient.c ipv4udpclient.h
	gcc $(CFLAGS) -c ipv4udpclient.c

clean:
	rm -f *.o client server