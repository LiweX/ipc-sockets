#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "ipv4udpserver.h"
#include "ipv6server.h"
#include "ipv4tcpserver.h"
#include "tools.h"

#define N_PARAMS 5


int main(int argc, char* argv[]){

    //Speeds speeds;
    //reset_speeds(&speeds);

    if(argc!=N_PARAMS){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[3]);
    char *ipv4address = argv[1];
    char *ipv6address = argv[2];
    char *interface = argv[4];
   // double* ipv4tcpspeed=(double *)malloc(sizeof(double));
    int pid; 
    pid = fork();
    if(pid==0){
        printf("levantando servidor tcp ipv4\n");
        ipv4tcpserver(port,ipv4address);
        return 0;   
    }
    pid = fork();
    if(pid==0){
        printf("levantando servidor udp ipv4\n");
        ipv4udpserver(port,ipv4address);
        return 0;
    }
    pid = fork();
    if(pid==0){
        printf("levantando servidor tcp ipv6\n");
        ipv6server(port,ipv6address,interface);
        return 0;
    }    
    while (1)
    {   
        //system("clear");
       // printf("ipv4tcp speed: %.2lfMB/s\n",*ipv4tcpspeed);
        //sleep(1);
        
    }
    
    return 0;
}