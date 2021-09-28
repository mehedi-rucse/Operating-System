#include <stdlib.h>		// exit()
#include <sys/socket.h>		// socket(), bind()
#include <stdio.h>		// perror()
#include <netinet/in.h>		// htons(), htonl()
#include <unistd.h>		// close()
#include <string.h>		// strlen(), memset()
#include <pthread.h>    //thread

#define LOCAL_PORT 49153
#define REMOTE_PORT 49152
#define MSG_SZ 256

int get_sockfd(char bflag);
void connect_sockets(int sockfd);
void receive_msg(int sockfd);
void send_msg(int sockfd);

struct args {
      int socket;
};


void *writer(void *thread_arg){
	struct args *my_data;
    my_data = (struct args *)thread_arg;
	while (1)
	{
		
		send_msg(my_data->socket);
	}
}
void *reader(void *thread_arg){
	struct args *my_data;
    my_data = (struct args *)thread_arg;
	while (1)
	{
		receive_msg(my_data->socket);
	}
}

 
int main() {
	int sockfd;
	pthread_t thread_id1,thread_id2;
	struct args *data = (struct args *)malloc(sizeof(struct args));

	/*	1. Create a socket at first. Then bind a unique name to it (optional). */
	sockfd  = get_sockfd('n');

	/*	2. Connect client sockets with server's active socket via it's name.	*/
	connect_sockets(sockfd);

	
	data->socket = sockfd;
	pthread_create(&thread_id1,NULL,writer,(void *)data);
	pthread_create(&thread_id2,NULL,reader,(void *)data);

	pthread_join(thread_id1,NULL);
	pthread_join(thread_id2,NULL);
	
	/*	4. Close sockets by releasing any system resources acquired by sockets.	*/
	close(sockfd);

	exit(EXIT_SUCCESS);
}

void send_msg(int sockfd) {
	char msg[MSG_SZ];
	ssize_t sentStrSz;

	
	memset(msg, '\0', MSG_SZ);	//	Clear buffer before using.
	
	gets(msg);
	sentStrSz = send(sockfd, msg, strlen(msg) + 1, 0);// Extra byte for '\0'
	if(sentStrSz == -1){
		perror("Error during send()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

void receive_msg(int sockfd) {
	char msg[MSG_SZ], displayMsg[MSG_SZ];
	ssize_t recvStrSz;

	
	memset(msg, '\0', MSG_SZ);	//	Clear buffer before using.
	recvStrSz = recv(sockfd, msg, MSG_SZ, 0);
	if(recvStrSz == -1){
		perror("Error during recv()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	/*	2. Display the message. */
	memset(displayMsg, '\0', MSG_SZ);	//	Clear buffer before using.
	strcpy(displayMsg,"Server : ");
	strcat(displayMsg, msg);
	strcat(displayMsg, "\n");
	
	write(1, displayMsg, strlen(displayMsg));	
}

void connect_sockets(int sockfd) {
	int addrLen, status;
	struct sockaddr_in addr;
	struct sockaddr *sockAddrPtr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(REMOTE_PORT);	// Server's Port.
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	// Any IP of the host.
	sockAddrPtr = (struct sockaddr *) &addr;
   	addrLen = sizeof(struct sockaddr_in);

	
	status = connect(sockfd, sockAddrPtr, addrLen);
	if(status == -1){
		perror("Error during connect()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
}

int get_sockfd(char bflag) {
	int sockfd, addrLen, status;
	struct sockaddr_in addr;
	struct sockaddr *sockAddrPtr;
	
	/*	Create a socket without a name (i.e., an address.)*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("Error during socket()");
		exit(EXIT_FAILURE);
	}

	
	if(bflag == 'y'){
		addr.sin_family = AF_INET;
		addr.sin_port = htons(LOCAL_PORT);
		addr.sin_addr.s_addr = htonl(INADDR_ANY);	// Any IP of the host.
		
    		sockAddrPtr = (struct sockaddr *) &addr;
    		addrLen = sizeof(struct sockaddr_in);
		status = bind(sockfd, sockAddrPtr, addrLen);
		if(status == -1){
			perror("Error during bind()");
			close(sockfd);
			exit(EXIT_FAILURE);
		}
	}
	
	return sockfd;
}