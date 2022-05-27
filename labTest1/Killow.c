#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include<unistd.h>

int main(){
    while (1)
    {
        printf("I am child-%d running at CPU-%d.\n",getpid(),sched_getcpu());
    }
  return 0;  
}