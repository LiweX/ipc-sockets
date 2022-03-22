#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "ipv4tcpclient.h"
#include "ipv4udpclient.h"
#include "ipv6client.h"

#define N_PARAMS 6

int main(int argc, char* argv[]){

    if(argc!=N_PARAMS){
        printf("Invalid argument\n");
        exit(EXIT_FAILURE);
    }
    char *protocol= argv[1];
    int buff_size = atoi(argv[4]);
    int port = atoi(argv[3]);
    char *address = argv[2];
    char *interface = argv[5];

    if(strstr(protocol,"tcp")){
        printf("creando cliente tcp ipv4\n");
        ipv4tcpclient(port,address,buff_size);
    }
    if(strstr(protocol,"udp")){
        printf("creando cliente udp ipv4\n");
        ipv4udpclient(port,address,buff_size); 
    }
    if(strstr(protocol,"ipv6")){
        printf("creando cliente tcp ipv6\n");
        ipv6client(port,address,interface,buff_size);
    }
 
    return 0;
}