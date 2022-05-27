#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath;
	char buffer[200];

	pipePath = "/home/mehedi/Desktop/OS_CLASS/NamedPipe/2ndPipe";
	fd = open(pipePath, O_RDONLY);	
	read(fd, buffer, sizeof(buffer));
	close(fd);

	// Display to the monitor.
	write(STDOUT_FILENO, buffer, strlen(buffer));

	return 0;
}
