#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <stdlib.h>

int main(){
	 char expression[3][20]={"1stPipe","2ndPipe","3rdPipe"};
	 int pipeFlag, fd,i;

	 for (int i = 0; i < 3; i++)
	 {
	 	//common path for three pipes
	 	char pipePath[] = "/home/mehedi/Desktop/OperatingSystem/Assignment2/Problem2/";
	 	//adding the last part for each pipes
		strcat(pipePath,expression[i]);
		
		if(access(pipePath, F_OK) == 0) { // Pipe exists
			printf("%s is already created, so new pipe will not be created\n. ", pipePath);
		}
		else {// Pipe does not exists, so we can create a new pipe.
			pipeFlag = mkfifo(pipePath, 0666); // mkfifo(pipePath, permission)
			if (pipeFlag < 0){
				printf("Error in creating a named pipe.\n");
				exit(-1);	
			} 
			else{
				printf("Pipe %d has been created successfully.\n",i+1);
			}
		}
	 }
	
	return 0;
}

