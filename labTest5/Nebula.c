#define _GNU_SOURCE
#include<sched.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

cpu_set_t cpuset;

void X(){
    int pid = getpid();
    int tid = gettid();
    int cpu = sched_getcpu();
    printf("NEBULAX PID : %d TID : %d  CPU: %d\n",pid,tid,cpu);

    int cpuNo = sysconf(_SC_NPROCESSORS_ONLN); 
    printf("NEBULAX CPU Affinity are: ");
    sched_getaffinity(0, sizeof(cpu_set_t), &cpuset);
    for (int i = 0; i < 8; i++) {
        printf("%d ", CPU_ISSET(i, &cpuset));
    }
    printf("\n");

    printf("NEBULAX Scheduling Algorithm :%s\n",sched_getscheduler(pid) == SCHED_FIFO ? "FIFO" : "RR");

}

void Y(){
    int pid = getpid();
    int tid = gettid();
    int cpu = sched_getcpu();
    printf("NEBULAY PID : %d TID : %d  CPU: %d\n",pid,tid,cpu);

    int cpuNo = sysconf(_SC_NPROCESSORS_ONLN); 
    printf("NEBULAY CPU Affinity are: ");
    sched_getaffinity(0, sizeof(cpu_set_t), &cpuset);
    for (int i = 0; i < 8; i++) {
        printf("%d ", CPU_ISSET(i, &cpuset));
    }
    printf("\n");

    printf("NEBULAY Scheduling Algorithm :%s\n",sched_getscheduler(pid) == SCHED_FIFO ? "FIFO" : "RR");
}

int main(){
    pthread_t tid1,tid2;
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&tid1,NULL,(void *)X,NULL);
        pthread_create(&tid2,NULL,(void *)Y,NULL);

        struct sched_param sp = {.sched_priority = 80};
        int res = sched_setscheduler(0,SCHED_FIFO,&sp);

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
    }
    
    return 0;  

}