#include<stdio.h>
#include<string.h>
#include <fcntl.h>
#include<unistd.h>


int main(int argv,char **argc){
    char msg[100] ;
    char *msg1 = "Bye";
    char *path = argc[1];
    int fd = open(path,O_RDONLY); 
    read(fd,msg,sizeof(msg));
    printf("%s",msg);
    close(fd);
    while (1)
    {
        fd = open(path,O_RDONLY); 
        char msg2[100] ;
        read(fd,msg2,sizeof(msg2));
        printf("%s\n",msg2);
        close(fd);
        if(!strcmp(msg2,"Bye")){
            int fd1 = open(path,O_WRONLY);
            write(fd1,msg1,sizeof(msg1));
            close(fd1);
            break;
        }
    }
    return 0;
}