#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "ipv4tcpserver.h"
#include "ipv4udpserver.h"

#define N_PARAMS 3

int main(int argc, char* argv[]){

    if(argc>N_PARAMS||argc<=2){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[2]);
    char *address = argv[1];
    printf("puerto: %d\nip: %s\n",port,address);
    int pid; 
    pid = fork();
    if(pid==0){
        printf("levantando servidor tcp ipv4\n");
        ipv4tcpserver(port,address);
        return 0;   
    }
    pid = fork();
    if(pid==0){
        printf("levantando servidor udp ipv4\n");
        ipv4udpserver(port,address);
        return 0;
    }
    char buffer[100];
    while (1)
    {
        read(0,buffer,100);
        if(strstr(buffer,"exit")) break;
    }
    
    return 0;
}