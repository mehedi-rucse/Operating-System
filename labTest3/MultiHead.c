#define _GNU_SOURCE
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <signal.h>

int result;
pthread_mutex_t key;

int nums[2];

void Ittu(void *numbers){
    
    int *nums =  numbers;
    pthread_mutex_lock(&key);
    result += nums[0] + nums[1];
    printf("Ittu Result : %d\n",result);
    pthread_mutex_unlock(&key);
    if(result == 100){
        pthread_kill(pthread_self(),SIGUSR1);
    }
}
void Bittu(void *numbers){
    
    int *nums =  numbers;
    pthread_mutex_lock(&key);
    result += nums[0] - nums[1];
    printf("Bittu Result : %d\n",result);
    if(result == 100){
        pthread_kill(pthread_self(),SIGUSR1);
    }
    pthread_mutex_unlock(&key);
}
void Mittu(void *numbers){    
    int *nums =  numbers;
    pthread_mutex_lock(&key);
    result += nums[0] * nums[1];
    printf("Mittu Result : %d\n",result);
    pthread_mutex_unlock(&key);
    if(result == 100){
        pthread_kill(pthread_self(),SIGUSR1);
    }
}

int main(){
    pthread_t tid1,tid2,tid3;
    printf("Enter two numbers :");
    scanf("%d %d",&nums[0],&nums[1]);

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&tid1,NULL,(void *)Ittu,&nums);
        pthread_create(&tid2,NULL,(void *)Bittu,&nums);
        pthread_create(&tid3,NULL,(void *)Mittu,&nums);

        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        pthread_join(tid3,NULL);
    }
    

    

    return 0;


}