#define _GNU_SOURCE
#include<sched.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include<semaphore.h>
#include<string.h>
#include <stdlib.h>
sem_t * mutex;

int create_shared_memory(){
	key_t key;
	int shmID;
	key = ftok("threadSemaphore.c", 'a');
	shmID = shmget(key, 1024, IPC_CREAT | 0666);

	return shmID;
}


void write_to_shm(int x){

    int shmID = create_shared_memory();
    char *str = shmat(shmID, NULL, 0);
    char num[100];
	sprintf(num,"%d",x);
	strcpy(str,num);
    shmdt(str);
}
int read_from_shm(){
    int shmID = create_shared_memory();
    char *str = shmat(shmID, NULL, 0);
	int num = (int) strtol(str,(char **)NULL,10);
    return num;
    shmdt(str);
	
}

int main(){
    pid_t childPID;
    int x= 10,r;
    int shmid=0;

    write_to_shm(10);
    read_from_shm();

    sem_t key;
    //sem_init(&key,1,1);
    shmid=shmget(0,sizeof(mutex)*2 + SHMLBA, IPC_CREAT | SHM_R | SHM_W);
    mutex=shmat(shmid, NULL, 0);
    r=sem_init(&mutex[0],1,1);
    r=sem_init(&mutex[1],1,0);

    childPID =fork();
    if(childPID==0){
        int a,b;
        sem_wait(&mutex[0]);
        printf("%d",mutex[1]);
        
        a =read_from_shm();
        printf("x: %d  in child core %d before Addition\n",a,sched_getcpu());
        a=a+1;
        write_to_shm(a);
        b =read_from_shm();
        printf("x: %d  in child core %d after Addition\n",b,sched_getcpu());
        
        sem_post(&mutex[1]);
        printf("%d",mutex[1]);
    }
    else{
       
        int a,b;
        sem_wait(&mutex[1]);
       
        a =read_from_shm();
        printf("x: %d  in parent core %d before subtraction\n",a,sched_getcpu());
        a=a-1;
        write_to_shm(a);
        b =read_from_shm();
        printf("x: %d  in parent core %d after subtraction\n",b,sched_getcpu());
       
        sem_post(&mutex[0]);
    }

    return 0;


}