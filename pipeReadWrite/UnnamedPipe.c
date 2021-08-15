#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

char *typeConversion(int num){
    char *str;
    str = malloc(20*sizeof(char));
    num = abs(num);
    int i=0;
    if(num==0){
        return "0";
    }
    while(num){
        str[i]=num%10+'0';
        num=num/10;
        i++;
    }
    
    str[i]='\0';
    for(int k=0;2*k<i;k++){
        char ch = str[k];
        str[k] = str[i-k-1];
        str[i-k-1] = ch;
    }
    
    return (char *)str;
}


int main(){
	int pipeFD[2], status;
	pid_t childPID;
	status = pipe(pipeFD);

	if (status == -1){
		printf("Error!!!");
		exit(-1);
	}

	printf("Pipe descriptors: %d, %d\n", pipeFD[0], pipeFD[1]);

	
	childPID = fork();
	
	if (childPID == -1){ 
		printf("Error!!!");
		exit(-1);
	}	
	else if (childPID == 0){

		char *fd0 = typeConversion(pipeFD[0]);
        char *fd1 = typeConversion(pipeFD[1]);
          
		execlp("/home/mehedi/Desktop/OS_CLASS/childPipe",fd0,fd1,NULL);
	}
	else if (childPID > 0){
		
		wait(NULL);
		printf("Parent Process is reading from the pipe.\n");
		close(pipeFD[1]);

		char buffer[200];
		read(pipeFD[0], buffer, sizeof(buffer));
		printf("%s\n", buffer);		
	}
		
	return 0;

}
