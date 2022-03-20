
#include <unistd.h>  
#include <netdb.h> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <arpa/inet.h>
#include <net/if.h>
#include <errno.h>
#include <stdio.h> 
#include <string.h> 

/* server parameters */
#define INTERFACE "enp11s0"
#define SERV_PORT       8080              /* port */
#define SERV_HOST_ADDR "fe80::6a0:99af:bb91:fd13"  
#define BUF_SIZE        100               /* Buffer rx, tx max size  */
#define BACKLOG         5                 /* Max. client pending connections  */

int ipv6server(int port, char* address,char* interface)          /* input arguments are not used */
{ 
    int sockfd;  /* listening socket and connection socket file descriptors */
    unsigned int len;     /* length of client address */
    struct sockaddr_in6 servaddr, client; 
    
    int  len_rx;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */
    
     
    /* socket creation */
    sockfd = socket(AF_INET6, SOCK_STREAM, 0); //ipv6 tcp
    if (sockfd == -1) 
    { 
        fprintf(stderr, "[IPV6_SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV6_SERVER]: Socket successfully created..\n"); 
    }

    int flag = 1 ;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == -1) {
        fprintf(stderr, "[IPV6_SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
		return -1;
	}

    /* clear structure */
    memset(&servaddr, 0, sizeof(servaddr));
  
    /* assign IP, SERV_PORT, IPV6 */
    servaddr.sin6_family      = AF_INET6; 
    servaddr.sin6_port        = htons(port);
    inet_pton(AF_INET6, address, &servaddr.sin6_addr);
    servaddr.sin6_scope_id = if_nametoindex(interface);
    
    /* Bind socket */
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
        fprintf(stderr, "[IPV6_SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV6_SERVER]: Socket successfully binded \n");
    }
  
    /* Listen */
    if ((listen(sockfd, BACKLOG)) != 0) 
    { 
        fprintf(stderr, "[IPV6_SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    } 
    else
    {
        printf("[IPV6_SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin6_port) ); 
    }
    
    len = sizeof(client); 
    
      /* Accept the data from incoming sockets in a iterative way */
      while(1)
      {
        int connfd = accept(sockfd, (struct sockaddr *)&client, &len); 
        if (connfd < 0) 
        { 
            fprintf(stderr, "[IPV6_SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
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
                    fprintf(stderr, "[IPV6_SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                }
                else if(len_rx == 0) /* if length is 0 client socket closed, then exit */
                {
                    printf("[IPV6_SERVER]: client socket closed \n\n");
                    close(connfd);
                    break; 
                }
                else
                {
                    write(connfd, buff_tx, strlen(buff_tx));
                    printf("[IPV6_CLIENT]: %s \n", buff_rx);
                }            
            }  
        }                      
    }    
} 