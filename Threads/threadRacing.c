#define _GNU_SOURCE
#include 	<pthread.h>	// For pthread_create().
#include	<stdio.h>	// For printf().
#include	<stdlib.h>	// For exit().

int x = 100;
pthread_mutex_t key;

void sum(){
	pthread_mutex_lock(&key);
	printf("[CPU: %d] Before sum: %d\n",sched_getcpu(),x);
	x = x + 1;
	printf("[CPU: %d] After sum: %d\n",sched_getcpu(),x);
	pthread_mutex_unlock(&key);
}


void sub(){
	pthread_mutex_lock(&key);
	printf("[CPU: %d] Before sub: %d\n",sched_getcpu(),x);
	x = x - 1;
	printf("[CPU: %d] After sub: %d\n",sched_getcpu(),x);
	pthread_mutex_unlock(&key);
}


int main(){

	int i=0;
	pthread_t TID_2, TID_3;

	pthread_create(&TID_2, NULL, (void *) sum, NULL);
	pthread_create(&TID_3, NULL, (void *) sub, NULL);
	pthread_mutex_lock(&key);
	
		printf("Main Thread,[CPU: %d], x:%d\n",sched_getcpu(),x);
	pthread_mutex_unlock(&key);
	pthread_join(TID_2,NULL);
	pthread_join(TID_3,NULL);

	return 0;
}
