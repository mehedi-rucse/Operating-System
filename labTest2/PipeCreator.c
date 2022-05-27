#include<stdio.h>
#include<stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    int pipe;

    for (int i = 1; i < argc; i++)
    {
        pipe = mkfifo(argv[i],0777);
        if(pipe<0){
            printf("mkfifo Unsuccesful\n");
            exit(-1);
        }
    }
    return 0;
}