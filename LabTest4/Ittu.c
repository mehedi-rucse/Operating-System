#define _GNU_SOURCE
#include<sched.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include<wait.h>
#include<semaphore.h>
#include<fcntl.h>

int create_shared_memory(char *str){
    key_t key = ftok(str,'o');
    int id = shmget(key,1024,IPC_CREAT | 0666);
    if(id < 0){
        perror("Unsuccesful!");
        exit(-1);
    }
    return id;
}


void write_to_shm(int num,int shmid){
    int *no = shmat(shmid,NULL,0);
    *no = num;
    shmdt(no);
}

int read_from_shm(int shmid){

    int *no = shmat(shmid,NULL,0);
    int num = *no;
    return num;
}

void get_sem_value(sem_t *semptr){
    int value;
    sem_getvalue(semptr,&value);
    printf("Semaphore : %d\n",value);
}


int result;
int main(int args, char **argv){

    int a = atoi(argv[0]);
    int b = atoi(argv[1]);
    int shmid =  atoi(argv[2]);

    int result = a + b;   //addition
    // sem_t *semptr;
    // semptr = sem_open("/mysem",O_CREAT,0666,1);

    int semapgore_id = create_shared_memory("Bittu.c");

    sem_t *semptr =shmat(semapgore_id,NULL,0);
    sem_t *sem_ptr;

    sem_init(sem_ptr,1,1);

    
    int value;
    get_sem_value(semptr);
    sem_wait(sem_ptr);
    get_sem_value(semptr);
    printf("Ittu PID :%d CPU :%d \n",getpid(),sched_getcpu());
    value = read_from_shm(shmid);
    printf("Value Before Addition: %d\n",value);
    write_to_shm(result,shmid);
    value = read_from_shm(shmid);
    sem_post(sem_ptr);
    get_sem_value(semptr);
    printf("Value After Addition: %d\n",value);

    
    return 0;
}