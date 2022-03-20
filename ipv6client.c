#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <net/if.h>

#define SERVER_ADDRESS  "fe80::6a0:99af:bb91:fd13"     /* server IP */
#define PORT            8080 
 
 
/* This clients connects, sends a text and disconnects */
int ipv6client(int port,char*address,char*iterface,int buff_size) 
{ 
    char buf_tx[buff_size];
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
    inet_pton(AF_INET6, address, &servaddr.sin6_addr);
    servaddr.sin6_scope_id = if_nametoindex(iterface);
  
    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n");  
        return -1;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    while(1){
        read(0,buf_tx,buff_size);
        if(strstr(buf_tx,"exit")) break;
        write(sockfd, buf_tx, sizeof(buf_tx));
    }
   
       
    /* close the socket */
    close(sockfd); 
} 