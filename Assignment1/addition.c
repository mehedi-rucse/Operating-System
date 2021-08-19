#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argn,char *args[]){
    char *str;
    int pipe0 = atoi(args[0]);
    int pipe1 = atoi(args[1]);
    int a = atoi(args[2]);
    int b = atoi(args[3]);
    sprintf(str, "%d", a+b);
    
    close(pipe0);
    char *sum = str;
    write(pipe1,sum,strlen(sum)+1);
    
    return 0;
}