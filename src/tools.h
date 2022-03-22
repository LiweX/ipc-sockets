typedef struct
{
    long int ipv4_tcp;
    long int ipv4_udp;
    long int ipv6_tcp;
    long int total;
}   Bytes;

void reset_struct(Bytes* bytes);
void sumar_bytes(Bytes* bytes);