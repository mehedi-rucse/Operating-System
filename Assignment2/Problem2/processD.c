#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath2,*pipePath3;
	char *msg,*str;
	char buffer[200];

	pipePath2 = "/home/mehedi/Desktop/OperatingSystem/Assignment2/Problem2/2ndPipe";
	pipePath3 = "/home/mehedi/Desktop/OperatingSystem/Assignment2/Problem2/3rdPipe";
	
	//writing to pipe3
	msg = "Mehedi\n";
	fd = open(pipePath3, O_WRONLY);	
	write(fd, msg, strlen(msg) + 1);
	close(fd);

	//reading from pipe2
	fd = open(pipePath2, O_RDONLY);	
	read(fd, buffer, sizeof(buffer));
	close(fd);

	// Display to the monitor.
	write(STDOUT_FILENO, buffer, strlen(buffer));

	return 0;
}