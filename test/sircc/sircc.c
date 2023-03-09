/***************************************************************************
                           sircc.c  - description
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This simple irc client takes input from stdin as client commands to   *
 *   send to the server. The server reply is echoed on the screen without  *
 *   being processed                                                       *
 *                                                                         *
 ***************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "csapp.h"

#ifndef SHUT_WR
#define SHUT_WR 1
#endif	

#define MAX_MSG_LEN 512
#define  MAX(a,b) (((a > b)) ? (a) : (b))

/*
 * initialize with local server and default irc server port
 */
static char  server_ip[MAX_MSG_LEN] = "127.0.0.1";
int          server_port = 6667;

/*
 * usage(): display usage info about the client
 */
void usage(char *name)
{
	printf("Usage: name <ip address> <port>\n");
	exit(0);
}

/*
 * socket_connect(): set up a connection to the server
 *                   return the sockfd if success
 */
int socket_connect()
{
	int sockfd;
	struct sockaddr_in servaddr;

	// create a socket and then connect to the server
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(server_port);
	inet_aton(server_ip, &servaddr.sin_addr);

	printf( "SERVER IP %d\n", servaddr.sin_addr.s_addr );

	Connect(sockfd, (struct sockaddr* )&servaddr, sizeof(servaddr));

	// should set sock to be non-blocking
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) < 0){
		perror("fcntl (set non-blocking)");
		exit(1);
	}	

	return sockfd;			
}

/*
 * main function of the simple client
 */
int main(int argc, char *argv[])
{
	char  sendbuf[MAX_MSG_LEN+1], recvbuf[MAX_MSG_LEN+1];
	int   server_sock, max_fd, ready, byte_read;
	int   stdineof = 0;
	char  *end;
	fd_set read_fds;

	/* display usage information */
	if (argc > 1){
		if ((strcmp(argv[1], "--help") == 0) || 
		    (strcmp(argv[1], "-h") == 0)){
			usage(argv[0]);
			return -1;
		}

		if (argc == 2){
			/* parse options if there are */
			if (strchr(argv[1], '.')){
				/* consider it to be an IP with ".", 
				   buggy with no further checking though */
				strcpy(server_ip, argv[1]);
			}else{
				server_port = atoi(argv[1]);
			}
		}else{
			strcpy(server_ip, argv[1]);
			server_port = atoi(argv[2]);
		}
	}

	printf("Connecting to server %s at port %d ...\n", server_ip, server_port);

	// connect to the server
	server_sock = socket_connect();

	printf("Connected, ready for commands:\n");

	// init read_fds
	FD_ZERO(&read_fds);

	while (1){

		// check which is ready, stdin or server_sock
		FD_SET(server_sock, &read_fds);
		FD_SET(fileno(stdin), &read_fds);
		max_fd = MAX(server_sock, fileno(stdin)) + 1;
		ready = Select(max_fd, &read_fds, 0, 0, 0);
		if (ready == 0)
			continue;

		// display server message first 
		if (FD_ISSET(server_sock, &read_fds)){
			do {
				bzero(recvbuf, MAX_MSG_LEN+1);
				byte_read = read(server_sock, recvbuf, MAX_MSG_LEN);
				if (byte_read > 0){
					recvbuf[byte_read] = '\0';
					printf("%s", recvbuf);

				}else if (byte_read == 0){

					// server send EOF
					if (stdineof == 1)
						return 0;
					printf("Server EOF, exit\n");
					exit(0);
				}else{
					if ((errno == EAGAIN) || (errno == EINTR))
						break;

					// error read
					printf("Error read, exit\n");
					close(server_sock);
					exit(0);
				}
			}while (byte_read > 0);
		}
	    
		// get a line from screen
		if (FD_ISSET(fileno(stdin), &read_fds)){
			if (!fgets(sendbuf, MAX_MSG_LEN, stdin)){
				// stdin EOF
				stdineof = 1;
				shutdown(server_sock, SHUT_WR);
				FD_CLR(fileno(stdin), &read_fds);
				continue;
			}

			// add \r\n if not
			if (!(end = strstr(sendbuf, "\r\n"))){
				end = strchr(sendbuf, '\n');
			}
			if (!end){
				printf("Error finding \\n\n");
				close(server_sock);
				exit(1);
			}
			strcpy(end, "\r\n");
			
			// send the line to the server
			Rio_writen(server_sock, sendbuf, strlen(sendbuf));
		}
	}

	close(server_sock);
	return 0;
}
