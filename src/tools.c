#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include "tools.h"

void reset_struct(Bytes* bytes){
    bytes->ipv4_tcp=0;
    bytes->ipv4_udp=0;
    bytes->ipv6_tcp=0;
    bytes->total=0;
}
void sumar_bytes(Bytes* bytes){
    long int suma=0;
    suma+=bytes->ipv4_tcp;
    suma+=bytes->ipv4_udp;
    suma+=bytes->ipv6_tcp;
    bytes->total=suma;
}