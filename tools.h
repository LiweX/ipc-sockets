typedef struct
{
    double ipv4_tcp;
    double ipv4_udp;
    double ipv6_tcp;
}   Speeds;

void reset_speeds(Speeds* speeds);
void print_speeds(Speeds* speeds);
long int sumar_speeds(long int*speeds_buffer,int* n_clients);
