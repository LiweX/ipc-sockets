#include <unistd.h>  
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "tools.h"
#include <time.h>

/* server parameters */
#define BUF_SIZE        1000000              /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */


int ipv4tcpserver(int port, char* address,long int* bytes)          /* input arguments are not used */
{ 
    int sockfd;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    int n_con=0;
    struct sockaddr_in servaddr, client; 
    long int len_rx;                     /* received and sent length, in bytes */
    char buff_rx[BUF_SIZE];   /* buffers for reception  */

    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        fprintf(stderr, "[IPV4_TCP_SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        exit(EXIT_FAILURE);
    } 
    else
    {
        printf("[IPV4_TCP_SERVER]: Socket successfully created..\n"); 
    }
    int flag = 1 ;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1) {
        fprintf(stderr, "[IPV4_TCP_SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
		exit(EXIT_FAILURE);
	}
    
    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, port, IPV4 */
    servaddr.sin_family      = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(address); 
    servaddr.sin_port        = htons((uint16_t)port);

    
    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        fprintf(stderr, "[IPV4_TCP_SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        exit(EXIT_FAILURE);
    } 
    else
    {
        printf("[IPV4_TCP_SERVER]: Socket successfully binded \n");
    }
  
    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        fprintf(stderr, "[IPV4_TCP_SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        exit(EXIT_FAILURE);
    } 
    else
    {
        printf("[IPV4_TCP_SERVER]: Listening on port %d \n\n", ntohs(servaddr.sin_port) ); 
    }
    len = sizeof(client);
    while(1)
    {
        int connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        n_con++;
        int pid = fork();
        if (pid==0)
        {   
             
            if (connfd < 0) 
            { 
                fprintf(stderr, "[IPV4_TCP_SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
                n_con--;
                exit(EXIT_FAILURE);       
            } 
            else
            {  
                                            
                while(1) /* read data from a client socket till it is closed */ 
                {  

                    len_rx = recv(connfd, buff_rx, BUF_SIZE,0);

                    if(len_rx == -1)
                    {
                        fprintf(stderr, "[IPV4_TCP_SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                    }
                    else if(len_rx == 0) /* if length is 0 client socket closed, then exit */
                    {
                        printf("[IPV4_TCP_SERVER]: client %d socket closed \n\n",n_con);
                        close(connfd);
                        exit(EXIT_SUCCESS);
                    }
                    else
                    {
                        //printf("[IPV4_TCP_CLIENT_%d]: %s \n", n_con, buff_rx);
                        *bytes+=len_rx;
                    }            
                }  
            } 
        }
    }    
} 