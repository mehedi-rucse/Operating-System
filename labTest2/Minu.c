#include<stdio.h>
#include<string.h>
#include <fcntl.h>
#include<unistd.h>

int main(int argv,char **argc){
    char msg[100];
    char msg1[100];
    char msg2[100];
    pid_t pid,ppid;
    char *p,*pp;
    pid = getpid();
    ppid = getppid();
    
    sprintf(msg,"PID:%d Parent PID:%d\nHello\n",pid,ppid);

    char *path = argc[1];
    int fd = open(path,O_WRONLY);
    write(fd,msg,strlen(msg)+1);
    close(fd);
    while (1)
    {
        fd = open(path,O_WRONLY);
        scanf("%s",msg1);
        write(fd,msg1,strlen(msg1)+1);
        close(fd);
        if(!strcmp(msg1,"Bye")){
            int fd1 = open(path,O_RDONLY);
            read(fd1,msg2,sizeof(msg2));
            printf("%s\n",msg2);
            close(fd1);
            break;
        }
    }
      
    return 0;
}