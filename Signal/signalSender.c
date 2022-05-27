
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>



int main(int argc,char **argv){
   
    pid_t signal_receiver;
    signal_receiver = atoi(argv[1]);

    kill(signal_receiver,SIGTERM);

    return 0;
}