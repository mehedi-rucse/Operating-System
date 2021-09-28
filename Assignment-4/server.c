#include <stdlib.h>		// exit()
#include <sys/socket.h>		//	socket(), bind()
#include <stdio.h>		// perror()
#include <netinet/in.h>		// htons(), htonl()
#include <unistd.h>		// close()
#include <string.h>
#include <pthread.h>		// strlen(), strcpy(), strcat(), memset()

#define LOCAL_PORT 49152
#define MSG_SZ 256

int get_sockfd(char bflag);
void turn_passive_socket(int sockfd, int backlog);
int get_active_sockfd(int sockfd);
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
	int sockfd, active_sockfd;

	pthread_t thread_id1,thread_id2;
	struct args *data = (struct args *)malloc(sizeof(struct args));
	
		
	

	sockfd  = get_sockfd('y');

	
	turn_passive_socket(sockfd, 1);

	active_sockfd = get_active_sockfd(sockfd);

	data->socket = active_sockfd;
	pthread_create(&thread_id1,NULL,writer,(void *)data);
	pthread_create(&thread_id2,NULL,reader,(void *)data);
	pthread_join(thread_id1,NULL);
	pthread_join(thread_id2,NULL);

	/*	4.	Exchange message with a client.	*/

	close(active_sockfd);
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
	strcpy(displayMsg,"\nClient: ");
	strcat(displayMsg, msg);
	strcat(displayMsg, "\n");
	
	write(1, displayMsg, strlen(displayMsg));	
}

int get_active_sockfd(int sockfd) {
	
	int active_sockfd = accept(sockfd, NULL, NULL);
	if(active_sockfd == -1){
		perror("Error during accept()");
		close(sockfd);
		exit(EXIT_FAILURE);
	}	

	return active_sockfd;
}

void turn_passive_socket(int sockfd, int backlog) {
	
	int status = listen(sockfd, backlog); 
	if(status == -1){
		perror("Error during listen()");
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
		//addr.sin_addr.s_addr = htonl(INADDR_ANY);	// Any IP of the host.
		addr.sin_addr.s_addr = INADDR_ANY;	// Any IP of the host.
	/* In order to use a specific IP, use: inet_aton("10.10.10.1", &addr.sin_addr.s_addr);
	*	It is not mandatory to use htonl() for INADDR_ANY.		
	*/
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