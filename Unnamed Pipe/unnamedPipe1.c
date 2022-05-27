#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>


int main(){
	int pipeFD[2], status;
	char str[20];
	pid_t childPID;
	
	// Create a pipe. pipeFD[0]: Read purpose & pipeFD[1]: Write purpose
	status = pipe(pipeFD);
	if (status == -1){// Failure case.
		printf("Error!!!");
		exit(-1);
	}
	printf("Pipe descriptors: %d, %d\n", pipeFD[0], pipeFD[1]);

	// Create a child
	childPID = fork();
	
	if (childPID == -1){ // Failure case.
		printf("Error!!!");
		exit(-1);
	}	
	else if (childPID == 0){ // Child will execute this part.
		char str[20];
    	fgets(str,20,stdin);
		printf("Child Process is writing to the pipe.\n");
		close(pipeFD[0]);
		char *msg = str;
		write(pipeFD[1], msg, strlen(msg) + 1);
	}
	else if (childPID > 0){// Parent will execute this part.
		wait(NULL);

		printf("Parent Process is reading from the pipe.\n");
		close(pipeFD[1]);

		char buffer[200];
		read(pipeFD[0], buffer, sizeof(buffer));
		printf("%s\n", buffer);		
	}
		
	return 0;

}
