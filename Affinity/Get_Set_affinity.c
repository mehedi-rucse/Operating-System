#define _GNU_SOURCE
#include<stdio.h>
#include<sched.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc , char *argv[]){
    int cpuID;
    long cpuN;
    cpu_set_t mask;

    cpuID = sched_getcpu();
    printf("CPU ID %d\n",cpuID);

    cpuN = sysconf(_SC_NPROCESSORS_ONLN);
    printf("No of CPUs %ld\n:",cpuN);
    sched_getaffinity(0,sizeof(cpu_set_t),&mask);
    for (int i = 0; i < cpuN; i++)
    {
        printf("%d ",CPU_ISSET(i, &mask));
       
    }
    printf("\n");

    CPU_ZERO(&mask);
    CPU_SET(2, &mask);
    sched_setaffinity(0,sizeof(cpu_set_t),&mask);

    
    cpuID = sched_getcpu();
    printf("CPU ID %d\n",cpuID);

    return 0;
}