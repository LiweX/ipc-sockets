CFLAGS=-Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11

all: server client

server: src/server.c tools.o ipv4tcpserver.o ipv4udpserver.o ipv6server.o tools.o
	mkdir -p ./bin
	gcc $(CFLAGS) ./src/server.c -o ./bin/server ./obj/ipv4tcpserver.o ./obj/ipv4udpserver.o ./obj/ipv6server.o ./obj/tools.o

client: src/client.c ipv4tcpclient.o ipv4udpclient.o ipv6client.o
	mkdir -p ./bin
	gcc $(CFLAGS) ./src/client.c -o ./bin/client ./obj/ipv4tcpclient.o ./obj/ipv4udpclient.o ./obj/ipv6client.o

ipv4tcpserver.o: src/ipv4tcpserver.c src/ipv4tcpserver.h
	mkdir -p ./obj
	gcc $(CFLAGS) -c ./src/ipv4tcpserver.c -o ./obj/ipv4tcpserver.o

ipv4udpserver.o: src/ipv4udpserver.c src/ipv4udpserver.h
	mkdir -p ./obj
	gcc $(CFLAGS) -c ./src/ipv4udpserver.c -o ./obj/ipv4udpserver.o

ipv6server.o: src/ipv6server.c src/ipv6server.h
	mkdir -p ./obj
	gcc $(CFLAGS) -c ./src/ipv6server.c -o ./obj/ipv6server.o

ipv6client.o: src/ipv6client.c src/ipv6client.h
	mkdir -p ./obj
	gcc $(CFLAGS) -c ./src/ipv6client.c -o ./obj/ipv6client.o

ipv4tcpclient.o: src/ipv4tcpclient.c src/ipv4tcpclient.h
	mkdir -p ./obj
	gcc $(CFLAGS) -c ./src/ipv4tcpclient.c -o ./obj/ipv4tcpclient.o

ipv4udpclient.o: src/ipv4udpclient.c src/ipv4udpclient.h
	mkdir -p ./obj 
	gcc $(CFLAGS) -c ./src/ipv4udpclient.c -o ./obj/ipv4udpclient.o

tools.o: src/tools.c src/tools.h
	mkdir -p ./obj
	gcc $(CFLAGS) -c ./src/tools.c -o ./obj/tools.o

clean:
	rm -f *.o log.txt -r ./bin ./obj