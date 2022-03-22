#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

int ipv4tcpclient(int port, char* address,int bytes) 
{ 
 //   char buf_tx[bytes];
    int sockfd; 
    struct sockaddr_in servaddr;
    char data[bytes];
    for(int i=0;i<bytes;i++){
        data[i] = 'a';
    }
    data[bytes-1]='\0';
    
    /* Socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //tpc socket
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
    servaddr.sin_addr.s_addr = inet_addr( address ); 
    servaddr.sin_port = htons((uint16_t)port); 
  
    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) 
    { 
        printf("connection with the server failed...\n");  
        return -1;
    } 
    
    printf("connected to the server..\n"); 
  
    /* send test sequences*/
    while(1){
        //read(0,buf_tx,bytes);
        //if(strstr(buf_tx,"exit")) break;
        //write(sockfd, buf_tx, sizeof(buf_tx));
        send(sockfd,data,strlen(data),0);
    }
   
    /* close the socket */
    close(sockfd); 
    return 0;
} 