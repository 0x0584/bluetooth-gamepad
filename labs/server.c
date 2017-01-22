/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>		/* socket(), bind() */
#include <netinet/in.h>

void
error(const char *msg)
{
  perror(msg);
  exit(1);
}

int
main(int argc, char *argv[])
{
  int sockfd, newsockfd,	/* socket file describtor */ 
    portno;			/* port number */
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr; /* server details */
  int n;

  /* port checking */
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }

  /* 1. opening the socket */
  sockfd = socket(AF_INET,	/* domain (protocol familly): IPv4 */
		  SOCK_STREAM, 	/* protocol type: TCP  */
		  0);		/* protocol number: TCP is the only protocol */
  if (sockfd < 0) error("ERROR opening socket");

  bzero((char *) &serv_addr, sizeof(serv_addr)); /* ??? */
  portno = atoi(argv[1]);

  /* --- init server details --- */
  /* protocol family */
  serv_addr.sin_family = AF_INET;			
  /* accept all incomming messages (set ip address to 0.0.0.0) */
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  /* convert the port to network byte order */
  serv_addr.sin_port = htons(portno);			
  /* --- init server details --- */
  
  /* 2. binding the socket */
  if (bind(sockfd,			   /* socket file describtor */
	   (struct sockaddr *) &serv_addr, /* reffrence to the socket address */
	   sizeof(serv_addr)) < 0) error("ERROR on binding");

  listen(sockfd,5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, 
		     (struct sockaddr *) &cli_addr, 
		     &clilen);

  /* 3. accept the socket */
  if (newsockfd < 0) error("ERROR on accept");

  bzero(buffer,256);
  n = read(newsockfd,buffer,255);

  /* 4. read the socket */
  if (n < 0) error("ERROR reading from socket");

  printf("Here is the message: %s\n",buffer);
  n = write(newsockfd,"I got your message",18);

  /* 5. write to the socket */
  if (n < 0) error("ERROR writing to socket");

  close(newsockfd); close(sockfd);
  return 0; 
}
