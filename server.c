#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "ipv4tcpserver.h"

#define N_PARAMS 3

int main(int argc, char* argv[]){

    if(argc>N_PARAMS||argc<=2){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[2]);
    char *address = argv[1];
    printf("puerto: %d\nip: %s\n",port,address);
    printf("levantando servidor tcp ipv4\n");
    ipv4tcpserver(port,address);
    return 0;
}