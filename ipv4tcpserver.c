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
#define BUF_SIZE        100               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */

int ipv4tcpserver(int port, char* address)          /* input arguments are not used */
{ 
    int sockfd;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in servaddr, client; 
    
    long int len_rx;                     /* received and sent length, in bytes */
    //char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    
     
    /* socket creation */
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) 
    { 
        fprintf(stderr, "[IPV4_TCP_SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV4_TCP_SERVER]: Socket successfully created..\n"); 
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
        return -1;
    } 
    else
    {
        printf("[IPV4_TCP_SERVER]: Socket successfully binded \n");
    }
  
    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        fprintf(stderr, "[IPV4_TCP_SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV4_TCP_SERVER]: Listening on port %d \n\n", ntohs(servaddr.sin_port) ); 
    }
    int n_con = 0;
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
                return -1;
            } 
            else
            {              
                while(1) /* read data from a client socket till it is closed */ 
                {  
                    /* read client message, copy it into buffer */
                    len_rx = read(connfd, buff_rx, sizeof(buff_rx));  
                
                    if(len_rx == -1)
                    {
                        fprintf(stderr, "[IPV4_TCP_SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                    }
                    else if(len_rx == 0) /* if length is 0 client socket closed, then exit */
                    {
                        printf("[IPV4_TCP_SERVER]: client %d socket closed \n\n",n_con);
                        close(connfd);
                        break; 
                    }
                    else
                    {
                        printf("[IPV4_TCP_CLIENT_%d]: %s \n", n_con, buff_rx);
                    }            
                }  
            } 
        }                        
    }    
} 