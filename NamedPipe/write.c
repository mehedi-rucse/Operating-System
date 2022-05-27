#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	char *pipePath;
	char *msg;

	pipePath = "/home/mehedi/Desktop/OS_CLASS/NamedPipe/2ndPipe";
	msg = "Hello\n";
	fd = open(pipePath, O_WRONLY);	
	write(fd, msg, strlen(msg) + 1);
	close(fd);

	return 0;
}