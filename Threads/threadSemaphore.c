#define _GNU_SOURCE
#include 	<pthread.h>	// For pthread_create().
#include	<stdio.h>	// For printf().
#include	<stdlib.h>	// For exit().
#include<semaphore.h>   //for semaphore


int x = 100;
sem_t key;

void sum(){
	sem_wait(&key);
	printf("[CPU: %d] Before sum: %d\n",sched_getcpu(),x);
	x = x + 1;
	printf("[CPU: %d] After sum: %d\n",sched_getcpu(),x);
	sem_post(&key);
}


void sub(){
	sem_wait(&key);
	printf("[CPU: %d] Before sub: %d\n",sched_getcpu(),x);
	x = x - 1;
	printf("[CPU: %d] After sub: %d\n",sched_getcpu(),x);
	sem_post(&key);
}


int main(){

	int i=0;
	pthread_t TID_2, TID_3;
	//
    sem_init(&key,0,1);//for betweed thread 0 ; process =1

	pthread_create(&TID_2, NULL, (void *) sum, NULL);
	pthread_create(&TID_3, NULL, (void *) sub, NULL);

	sem_wait(&key);
	printf("Main Thread,[CPU: %d], x:%d\n",sched_getcpu(),x);
	sem_post(&key);

	pthread_join(TID_2,NULL);
	pthread_join(TID_3,NULL);

	return 0;
}