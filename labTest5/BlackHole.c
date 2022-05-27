#define _GNU_SOURCE
#include<sched.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

cpu_set_t cpuset;

void X(){

    int pid = getpid();
    int tid = gettid();

    CPU_ZERO(&cpuset);
    CPU_SET(2,&cpuset);
    sched_setaffinity(0,sizeof(cpu_set_t),&cpuset);
    int cpu = sched_getcpu();
    printf("BLACKX PID : %d TID : %d  CPU: %d\n",pid,tid,cpu);

    int cpuNo = sysconf(_SC_NPROCESSORS_ONLN); 
    printf("BLACKX CPU Affinity are: ");
    sched_getaffinity(0, sizeof(cpu_set_t), &cpuset);
    for (int i = 0; i < 8; i++) {
        printf("%d ", CPU_ISSET(i, &cpuset));
    }
    printf("\n");

    printf("BLACKX Scheduling Algorithm :%s\n",sched_getscheduler(getpid()) == SCHED_FIFO ? "FIFO" : "RR");

}

void Y(){
    int pid = getpid();
    int tid = gettid();

    CPU_ZERO(&cpuset);
    CPU_SET(3,&cpuset);
    sched_setaffinity(0,sizeof(cpu_set_t),&cpuset);
    int cpu = sched_getcpu();
    printf("BLACKY PID : %d TID : %d  CPU: %d\n",pid,tid,cpu);

    int cpuNo = sysconf(_SC_NPROCESSORS_ONLN); 
    printf("BLACKY CPU Affinity are: ");
    sched_getaffinity(0, sizeof(cpu_set_t), &cpuset);
    for (int i = 0; i < 8; i++) {
        printf("%d ", CPU_ISSET(i, &cpuset));
    }
    printf("\n");
    printf("BLACKY Scheduling Algorithm :%s\n",sched_getscheduler(getpid()) == SCHED_FIFO ? "FIFO" : "RR");
}

int main(){
    pthread_t tid1,tid2;
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&tid1,NULL,(void *)X,NULL);
        pthread_create(&tid2,NULL,(void *)Y,NULL);

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
    }
    
    return 0; 

}