#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "tools.h"

void reset_speeds(Speeds* speeds){
    speeds->ipv4_tcp=0;
    speeds->ipv4_udp=0;
    speeds->ipv6_tcp=0;
}
void print_speeds(Speeds* speeds){
    printf("ipv4 tcp %fBytes/s\nipv4 udp %fBytes/s\nipv6 tcp %fBytes/s\n",speeds->ipv4_tcp,speeds->ipv4_udp,speeds->ipv6_tcp);
}
double sumar_speeds(double**speeds_buffer,int n_con){
    double suma=0;
    for(int i=0;i>n_con;i++){
        suma=suma+*speeds_buffer[i];
    }
    return suma;
}