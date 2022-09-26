/* 
 * udpclient.c - A simple UDP client
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

/* 
 * error - wrapper for perror
 */
static void error(char *msg) {
    perror(msg);
    exit(0);
}

int udpsend(char *hostname, int portno, char *msg){
    int sockfd, n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
	}

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
		error("ERROR, no such host\n");
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    /* send the message to the server */
    serverlen = sizeof(serveraddr);
    n = sendto(sockfd, msg, strlen(msg), 0, (const struct sockaddr *)&serveraddr, serverlen);
    if (n < 0) {
      error("ERROR in sendto");
	}
    
    return 0;
}
