#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath1,*pipePath2;
	char *msg,*str;
	char buffer[200];

	pipePath1 = "/home/mehedi/Desktop/OperatingSystem/Assignment2/Problem2/1stPipe";
	pipePath2 = "/home/mehedi/Desktop/OperatingSystem/Assignment2/Problem2/2ndPipe";
	
	//writing to pipe2
	msg = "Hello\n";
	fd = open(pipePath2, O_WRONLY);	
	write(fd, msg, strlen(msg) + 1);
	close(fd);

	//reading from pipe1
	fd = open(pipePath1, O_RDONLY);	
	read(fd, buffer, sizeof(buffer));
	close(fd);

	// Display to the monitor.
	write(STDOUT_FILENO, buffer, strlen(buffer));

	return 0;
}

