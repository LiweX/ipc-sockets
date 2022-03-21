typedef struct
{
    double ipv4_tcp;
    double ipv4_udp;
    double ipv6_tcp;
}   Speeds;

void reset_speeds(Speeds* speeds);
void print_speeds(Speeds* speeds);
double sumar_speeds(double**speeds_buffer,int n_con);
int ipv4tcpserver(int port, char* address,Speeds* speeds);