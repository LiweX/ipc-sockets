/*************************************************************************************/
/* @file    client_1.c                                                               */
/* @brief   This clients connects,                                                   */
/*          sends a text, reads what server and disconnects                          */
/*************************************************************************************/

#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define SERVER_ADDRESS  "192.168.0.148"     /* server IP */
#define PORT            8080 
#define MAX_SIZE 100

/* Test sequences */
char buf_tx[] = "Hello server. I am a client";
char buf_rx[MAX_SIZE];
 
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
    int sockfd; 
    struct sockaddr_in servaddr; 
    
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
    servaddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS ); 
    servaddr.sin_port = htons(PORT); 
  
        int n, len;
       
    sendto(sockfd, (const char *)buf_tx, strlen(buf_tx),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));
    printf("Hello message sent.\n");
           
    n = recvfrom(sockfd, (char *)buf_rx, MAX_SIZE, 
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buf_rx[n] = '\0';
    printf("Server : %s\n", buf_rx);
   
    close(sockfd);
    return 0;
} 