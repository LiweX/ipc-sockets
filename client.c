#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "ipv4tcpclient.h"

#define N_PARAMS 4

int main(int argc, char* argv[]){

    if(argc!=N_PARAMS){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    int buff_size = atoi(argv[3]);
    int port = atoi(argv[2]);
    char *address = argv[1];
    printf("puerto: %d\nip: %s\n",port,address);
    printf("creando cliente tcp ipv4\n");
    ipv4tcpclient(port,address,buff_size);
    return 0;
}