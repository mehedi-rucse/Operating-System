#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd1,fd2;
	char *pipePath1,*pipePath2;
	char *msg;
	char str[80];
	char buffer[200];
	pipePath1 = "/home/mehedi/Desktop/OS_CLASS/NamedPipe/1stPipe";
	pipePath2 = "home/mehedi/Desktop/OperatingSystem/Assignment2/Problem1/2ndPipe";

	while(1){
		
		fd1 = open(pipePath1, O_RDONLY);	
		read(fd1, buffer, sizeof(buffer));
		close(fd1);

		printf("Writer: %s\n",buffer);

		fgets(str,80,stdin);
		msg = str;
		fd2 = open(pipePath1, O_WRONLY);	
		write(fd2, msg, strlen(msg) + 1);
		close(fd2);

		if(!strcmp(buffer,"-999")){
			break;
		}
		

	}

	return 0;
}