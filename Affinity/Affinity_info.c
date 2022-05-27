#define _GNU_SOURCE
#include<assert.h>
#include<sched.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<stdio.h>

void print_affinity(){
    cpu_set_t mask;
    long nproc ,  i;
    if(sched_getaffinity(0,sizeof(cpu_set_t),&mask)==-1){
        perror("sched_getaffinty");
        assert(false);
    }
    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    printf("sched_getaffinty");
    for (int i = 0; i < nproc; i++)
    {
        printf("%d ",CPU_ISSET(i, &mask));
       
    }
    printf("\n");


}

int  main(void){
    cpu_set_t mask;
    print_affinity();
    printf("sched getcpu = %d\n", sched_getcpu());

    return 0;
}