#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


int main(){
	int fd1,fd2;
	char *pipePath1,*pipePath2;
	char *msg;
	char str[80];
	char buffer[200];
	pipePath1 = "/home/mehedi/Desktop/OS_CLASS/NamedPipe/1stPipe";




	while(1){
		fgets(str,80,stdin);
		msg = str;
		fd1 = open(pipePath1, O_WRONLY);	
		write(fd1, msg, strlen(msg) + 1);
		close(fd1);

		fd2 = open(pipePath1, O_RDONLY);	
		read(fd2, buffer, sizeof(buffer));
		close(fd2);
		
		printf("Reader: %s\n",buffer);
	}
	
	return 0;
}