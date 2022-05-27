#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

cpu_set_t cpuset;

int main(int argc, char const *argv[])
{
    int i;
    pid_t pid, pid1;
    pid = fork();

    if (pid < 0) {
        perror("Child process creation failed");
        exit(1);
    } 

    else if (pid == 0) {
        for(int i =0;i<2;i++)
            execlp("./Nebula", "Nebula", NULL);
    }
    else if (pid > 0) {
        pid1 = fork();
        if (pid1 < 0) {
            perror("Child process creation failed");
            exit(1);
        } 
        else if (pid1 == 0) {
            for(int i =0;i<2;i++)
                execlp("./BlackHole", "BlackHole", NULL);
        } 
        else if(pid1 > 0) {
            for(int i =0;i<3;i++){
                wait(NULL);
                int pid = getpid();
                int tid = gettid();
                int cpu = sched_getcpu();

                printf("GALAXY PID : %d TID : %d  CPU: %d\n",pid,tid,cpu);

                int cpuNo = sysconf(_SC_NPROCESSORS_ONLN); 
                printf("GALAXY CPU Affinity are: ");
                sched_getaffinity(0, sizeof(cpu_set_t), &cpuset);
                for (int i = 0; i < 8; i++) {
                    printf("%d ", CPU_ISSET(i, &cpuset));
                }
                printf("\n");
                printf("GALAXY Scheduling Algorithm :%s\n",sched_getscheduler(getpid()) == SCHED_FIFO ? "FIFO" : "RR");

            }
           
        }
    }

    return 0;
}
