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


int ipv4tcpserver(int port, char* address)          /* input arguments are not used */
{ 
    int sockfd;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client; 
    int* n_con = (int*)malloc(sizeof(int));
    if(n_con==NULL){
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }
    long int len_rx;                     /* received and sent length, in bytes */
    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    // long int* speeds = (long int*)malloc(sizeof(long int));
    // if(speeds == NULL){
    //     printf("Memory allocation error");
    //     exit(EXIT_FAILURE);
    // }

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
    // int pid = fork();
    // if(pid==0) while (1){
    //     printf("TCPIPV4 speed: %ld\n",sumar_speeds(speeds,n_con));
    // } 
    while(1)
    {
        int connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        n_con[0]++; 
        int pid = fork();
        if (pid==0)
        {   
            
            if (connfd < 0) 
            { 
                fprintf(stderr, "[IPV4_TCP_SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
                n_con[0]--;
                exit(EXIT_FAILURE);
                
            } 
            else
            {  
                // if(*n_con>1)
                // {
                //     speeds = (long int*)realloc(speeds,sizeof(long int)*(unsigned long int)(n_con));
                //     if(speeds==NULL)
                //     {
                //         printf("error al realocar");
                //         exit(EXIT_FAILURE);
                //     }
                // }
                int n_client=n_con[0];            
                while(1) /* read data from a client socket till it is closed */ 
                {  
                    // clock_t start = clock();
                    len_rx = recv(connfd, buff_rx, sizeof(buff_rx),0);  
                    // clock_t end = clock();
                    // double time = (double)(end - start)/CLOCKS_PER_SEC;

                    if(len_rx == -1)
                    {
                        fprintf(stderr, "[IPV4_TCP_SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                    }
                    else if(len_rx == 0) /* if length is 0 client socket closed, then exit */
                    {
                        printf("[IPV4_TCP_SERVER]: client %d socket closed \n\n",n_client);
                        //speeds[n_client-1]= 0;
                        close(connfd);
                        break; 
                    }
                    else
                    {
                        printf("[IPV4_TCP_CLIENT_%d]: %s \n", n_client, buff_rx);
                        //speeds[n_client-1] = (long int)((double)len_rx/time);
                        //printf("%ld Bytes sended in %lf seg\n",len_rx,time);
                    }            
                }  
            } 
        }
    }    
} 