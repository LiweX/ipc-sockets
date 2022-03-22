#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>



int ipv4udpclient(int port,char*address, int bytes) 
{
    int sockfd; 
    struct sockaddr_in servaddr; 
    char data[bytes];
    for(int i=0;i<bytes;i++){
        data[i] = 'a';
    }
    data[bytes-1]='\0';
    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //udp socket
    if (sockfd == -1) 
    { 
        printf("CLIENT: socket creation failed...\n"); 
        return -1;  
    } 
    else
    {
        printf("CLIENT: Socket successfully created..\n"); 
    }
    
    memset(&servaddr, 0, sizeof(servaddr));

    /* assign IP, PORT */
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(address); 
    servaddr.sin_port = htons((uint16_t)port); 

    while (1)
    {
        sendto(sockfd, (const char *)data, strlen(data),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    }
    close(sockfd);
    return 0;
} 