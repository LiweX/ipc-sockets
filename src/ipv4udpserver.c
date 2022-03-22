#include <unistd.h>  
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h> 
#include <string.h> 

/* server parameters */
#define BUF_SIZE        1000000               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */

int ipv4udpserver(int port, char* address,long int* bytes)          /* input arguments are not used */
{ 
    int sockfd;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    
    struct sockaddr_in servaddr, client;

    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    
     
    /* socket creation */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if (sockfd == -1) 
    { 
        fprintf(stderr, "[IPV4_UDP_SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV4_UDP_SERVER]: Socket successfully created..\n"); 
    }
    
    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(address); 
    servaddr.sin_port        = htons((uint16_t)port);
    
    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        fprintf(stderr, "[IPV4_UDP_SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV4_UDP_SERVER]: Socket successfully binded \n");
    }
  
    len = sizeof(client);
    
    while(1){
        long int n = recvfrom(sockfd, (char *)buff_rx, sizeof(buff_rx), 
                MSG_WAITALL, ( struct sockaddr *) &client,
                &len);
        *bytes+=n;
    } 
    return 0;
}                      
        
 