#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath;
	char buffer[200];
	while(1){
		pipePath = "/home/mehedi/Desktop/OS_CLASS/NamedPipe/1stPipe";
		fd = open(pipePath, O_RDONLY);	
		read(fd, buffer, sizeof(buffer));
		close(fd);
		if(!strcmp(buffer,"-999")){
			break;
		}
		// Display to the monitor.
		write(STDOUT_FILENO, buffer, strlen(buffer));
		write(STDOUT_FILENO,"\n",1);

	}

	return 0;
}