//Shared Memory
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdio.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>



int main(int argc,char **argv){

    pid_t signal_receiver;
    signal_receiver = atoi(argv[1]);
    kill(signal_receiver,SIGTERM);



    key_t shmKey;
    int shmID;
    char *str;

    /* 1. Generate a key
        key_t ftok(const char *pathname, int proj_id);
    */
    shmKey = ftok("process1",'o');
    printf("SHM Key : %d\n",shmKey);

    /*
        2.Allocate a shared memory segment.
        int shmget(key_t key,size_t size,int shmflag);
    */

    shmID = shmget(shmKey,100,0666);
    printf("SHM ID : %d\n",shmID);

    /*
        3. Attach user space with memory segment
        void *shmat(int shmid,const void *shmaddr, int shmflg);
    */

    str =(char *) shmat(shmID,NULL,0);


    /* Write data into shared memory */
    

    while (1)
    {
        //sleep(1.5) ;
        printf("%s\n",str);
    }
    
    


    return 0;
}
