#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath;
	char *msg,*str;

	pipePath = "/home/mehedi/Desktop/OperatingSystem/Assignment2/Problem2/1stPipe";
	msg = "Hey\n";
	fd = open(pipePath, O_WRONLY);	//writing to pipe1
	write(fd, msg, strlen(msg) + 1);
	close(fd);

	return 0;
}