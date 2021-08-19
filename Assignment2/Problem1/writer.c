#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


int main(){
	int fd;
	char *pipePath;
	char *msg,*str;
	pipePath = "/home/mehedi/Desktop/OS_CLASS/NamedPipe/1stPipe";

	while(1){
		gets(str);
		msg = str;
		fd = open(pipePath, O_WRONLY);	
		write(fd, msg, strlen(msg) + 1);
		close(fd);
		if(!strcmp(str,"-999")){
			break;
		}
	}

	return 0;
}