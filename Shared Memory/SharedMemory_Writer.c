//Shared Memory
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int shmID;
char *str;

void signal_handler(int c){
    shmdt(str);
    shmctl(shmID, IPC_RMID,NULL);
}


int main(){
    int i = 1;
    key_t shmKey;
    
    pid_t pid;
    pid =getpid();

    signal(SIGTERM, signal_handler);

    /* 1. Generate a key
        key_t ftok(const char *pathname, int proj_id);
    */
    shmKey = ftok("process1", 'o');
    printf("SHM Key : %d\n",shmKey);

    /*
        2.Allocate a shared memory segment.
        int shmget(key_t key,size_t size,int shmflag);
    */

    shmID = shmget(shmKey, 100, IPC_CREAT | 0666);
    printf("SHM ID : %d\n",shmID);

    /*
        3. Attach user space with memory segment
        void *shmat(int shmid,const void *shmaddr, int shmflg);
    */

    str =(char *) shmat(shmID,NULL,0);


    /* Write data into shared memory */
    while(1)
    {
        
        sprintf(str,"%d",i);
        printf("%s PID : %d\n",str,pid);
        i++; 
    }

    return 0;
}