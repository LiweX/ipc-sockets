#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include "ipv4tcpserver.h"
#include "ipv4udpserver.h"
#include "ipv6server.h"
#include "tools.h"

#define N_PARAMS 5


int main(int argc, char* argv[]){

    Bytes *bytes;
    int memoria_compartida = shmget(ftok(".", 'S'),sizeof(bytes),
            (IPC_CREAT | 0660));
    if(memoria_compartida < 0){
        fprintf(stderr, "memoria compartida. %d: %s \n", errno, strerror( errno ));
        exit(EXIT_FAILURE);
    }

    bytes = shmat(memoria_compartida, 0, 0);
    if(bytes == (void* )-1){
        perror("No se asigno el segmento");
        exit(EXIT_FAILURE);
    }


    if(argc!=N_PARAMS){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[3]);
    char *ipv4address = argv[1];
    char *ipv6address = argv[2];
    char *interface = argv[4];
    set_struct(bytes);
    int pid;
    pid = fork();
    if(pid==0){
        printf("levantando servidor tcp ipv4\n");
        ipv4tcpserver(port,ipv4address,&bytes->ipv4_tcp);
        exit(EXIT_SUCCESS);   
    }
    pid = fork();
    if(pid==0){
        printf("levantando servidor udp ipv4\n");
        ipv4udpserver(port,ipv4address,&bytes->ipv4_udp);
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    if(pid==0){
        printf("levantando servidor tcp ipv6\n");
        ipv6server(port,ipv6address,interface,&bytes->ipv6_tcp);
        exit(EXIT_SUCCESS);
    }
    int seconds=0;    
    while (1)
    {   
        seconds++;
        printf("IPV4 TCP SPEED: %ld Mbits/s\n",((bytes->ipv4_tcp)/seconds)*8/1000000);
        printf("IPV4 UDP SPEED: %ld Mbits/s\n",((bytes->ipv4_udp)/seconds)*8/1000000);
        printf("IPV6 TCP SPEED: %ld Mbits/s\n",((bytes->ipv6_tcp)/seconds)*8/1000000);
        sumar_bytes(bytes);
        printf("TOTAL SPEED: %ld Mbits/s\n",((bytes->total)/seconds)*8/1000000);
        sleep(1);
        system("clear");
           
    }
    return 0;
}