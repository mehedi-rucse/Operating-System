#define _GNU_SOURCE
#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<syscall.h>

void thread1(){
    int i;
    pid_t pid,threadID,cpuNo;
     for (i = 0; i < 10; i++)
    {
        pid =getpid();
        threadID = gettid();
        cpuNo =sched_getcpu();
        printf("Thread1's PID : %d  ThreadID : %d is running at : %d\n",pid,threadID,cpuNo);
    }
    
}
void thread2(){
    int i;
    pid_t pid,threadID,cpuNo;
    for (i = 0; i < 10; i++)
    {
        pid =getpid();
        threadID = gettid();
        cpuNo =sched_getcpu();
        printf("Thread2's PID : %d  ThreadID : %d is running at : %d\n",pid,threadID,cpuNo);
    }
    
}

int main(){
    pid_t childID;
   

    childID =fork();

    if (childID==0)
    {   
        int i,cpuNo;
        pid_t pid,threadID;
        
        pid =getpid();
        threadID = gettid();
        cpuNo =sched_getcpu();

        for (i = 0; i < 10; i++)
        {
           
            printf("Child Process's PID : %d  ThreadID : %d is running at : %d\n",pid,threadID,cpuNo);
        }
        

       
    }
    else if (childID>0)
    {
        int i,cpuNo;
        pid_t pid,threadID;
        pthread_t tid1,tid2;
        pthread_create(&tid1,NULL,(void *) thread1,NULL);
        pthread_create(&tid2,NULL,(void *) thread2,NULL);

        for (i = 0; i < 10; i++)
        {
            pid =getpid();
            threadID = gettid();
            cpuNo =sched_getcpu();
            printf("Main Thread's PID : %d  ThreadID : %d is running at : %d\n",pid,threadID,cpuNo);
        }
        

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
    }

    return 0;
}