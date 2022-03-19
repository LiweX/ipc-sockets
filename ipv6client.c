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

#define SERVER_ADDRESS  "fe80::6a0:99af:bb91:fd13"     /* server IP */
#define PORT            8080 

/* Test sequences */
char buf_tx[] = "Hello server. I am a client";      
char buf_rx[100];                     /* receive buffer */
 
 
/* This clients connects, sends a text and disconnects */
int main() 
{ 
    int sockfd; 
    struct sockaddr_in6 servaddr; 
    
    /* Socket creation */
    sockfd = socket(PF_INET6, SOCK_STREAM, 0); 
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
    servaddr.sin6_family = AF_INET6; 
    servaddr.sin6_port = htons(PORT);
    inet_pton(AF_INET6, "fe80::6a0:99af:bb91:fd13" , &servaddr.sin6_addr);
    servaddr.sin6_scope_id = if_nametoindex("enp11s0");
  
    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n");  
        return -1;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    write(sockfd, buf_tx, sizeof(buf_tx));     
    read(sockfd, buf_rx, sizeof(buf_rx));
    printf("CLIENT:Received: %s \n", buf_rx);
   
       
    /* close the socket */
    close(sockfd); 
} 