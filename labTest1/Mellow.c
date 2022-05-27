#define _GNU_SOURCE
#include<stdio.h>
#include <sched.h>
#include<unistd.h>
#include<wait.h>
#include<stdlib.h>
 
void error_check(pid_t pid){
    if(pid < 0){
        printf("Unsuccessful!");
        exit(-1);
    }
}

int main(){
    pid_t child1,child2;

    child1 = fork();
    error_check(child1);
    
    if(child1 == 0){
        
        execlp("./Pillow","Pillow",NULL);
    }
    else if(child1>0){

        child2 = fork();
        error_check(child2);

        if(child2 == 0){
            execlp("./Killow","Killow",NULL);
        }
        else if(child1 > 0 && child2 > 0){
             while (1)
            {
                printf("I am parent process pid: %d Pillow %d,running at CPU-%d. \n",getpid(),child1,sched_getcpu());
            }
        }
    }
    return 0;

}