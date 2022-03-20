#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "ipv4tcpclient.h"
#include "ipv4udpclient.h"

#define N_PARAMS 5

int main(int argc, char* argv[]){

    if(argc!=N_PARAMS){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    char *protocol= argv[1];
    int buff_size = atoi(argv[4]);
    int port = atoi(argv[3]);
    char *address = argv[2];

    printf("puerto: %d\nip: %s\n",port,address);

    if(strstr(protocol,"tcp")){
        printf("creando cliente tcp ipv4\n");
        ipv4tcpclient(port,address,buff_size);
    }
    if(strstr(protocol,"udp")){
        printf("creando cliente udp ipv4\n");
        ipv4udpclient(port,address,buff_size); 
    }
 
    return 0;
}