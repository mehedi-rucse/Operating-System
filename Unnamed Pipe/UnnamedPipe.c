#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

char *itoa(int n){
    char *sum;
    sum = malloc(20*sizeof(char));
    
    n = abs(n);
    int i=0;
    if(n==0){
        return "0";
    }
    while(n){
        sum[i]=n%10+'0';
        n/=10;
        i++;
    }
   
    
    sum[i]='\0';
    for(int k=0;2*k<i;k++){
        char ch = sum[k];
        sum[k] = sum[i-k-1];
        sum[i-k-1] = ch;
    }
    
    return (char *)sum;
}


int main(){
	int pipeFD[2], status;
	pid_t childPID;
	
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
	else if (childPID == 0){

		char *fd0 = itoa(pipeFD[0]);
        char *fd1 = itoa(pipeFD[1]);
          
		execlp("/home/mehedi/Desktop/OS_CLASS/childPipe",fd0,fd1,NULL);
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
