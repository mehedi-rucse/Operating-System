#define _GNU_SOURCE
#include<fcntl.h>
#include<sched.h>
#include<sys/shm.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include<wait.h>
#include<semaphore.h>
int result;

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

void checkError(pid_t pid){
    if(pid<0){
        perror("Unsuccesful");
        exit(-1);
    }
}



int main(){
    pid_t child1,child2,child3;
    int a , b;
    scanf("%d%d",&a,&b);

    char *no1,*no2,*memid;

    no1 = malloc(5*sizeof(char));
    no2 = malloc(5*sizeof(char));
    memid = malloc(5*sizeof(char));

    sprintf(no1,"%d",a);
    sprintf(no2,"%d",b);

    // sem_t *semptr;
    // semptr = sem_open("/mysem",O_CREAT,0666,1);

    int shmid = create_shared_memory("Ittu.c");

    

    write_to_shm(result,shmid);
    sprintf(memid,"%d",shmid);

    child1 = fork();
    checkError(child1);

    if (child1 == 0)
    {
       execlp("./Ittu",no1,no2,memid,NULL);
    }
    else if(child1 > 0 ){

        child2 = fork();
        checkError(child2);
        if (child2 == 0)
        {
        execlp("./Bittu",no1,no2,memid,NULL);
        }
        else if(child1 > 0 && child2 > 0){
            child3 = fork();
            checkError(child3);
            if (child3 == 0)
            {
                execlp("./Mittu",no1,no2,memid,NULL);
            }
            else if(child1 > 0 && child2 > 0 && child3 > 0){
                
                printf("Laltu PID :%d CPU :%d \n",getpid(),sched_getcpu());
                waitpid(child1,NULL,0);
                waitpid(child2,NULL,0);
                waitpid(child3,NULL,0);
                
            }
            
        }

    }
    



    return 0;
}