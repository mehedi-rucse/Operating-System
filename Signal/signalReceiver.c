#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void signal_handler(int c){
    printf("Hello, I am fine\n");
}

int main(){
    int i;
    pid_t pid;
    pid =getpid();

    signal(SIGTERM, signal_handler);

    for ( i = 0; i < 100000000; i++)
    {
        printf("%d. PID : %d\n",i,pid);
        sleep(5);
    }
}
