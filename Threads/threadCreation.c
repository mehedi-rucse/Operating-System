#include<stdio.h>
#include<pthread.h>

void sum(){
	for (int i = 0; i < 50; i++)
	{
		printf("Sub Thread\n");
	
	}	
}

int main(){

	pthread_t threadID;
	pthread_create(&threadID,NULL,(void *)sum,NULL);


	for (int i = 0; i < 5; i++)
	{
		printf("Main Thread\n");
	
	}
	

	return 0;
}