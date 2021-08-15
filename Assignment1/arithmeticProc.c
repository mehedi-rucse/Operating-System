#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

char *itoa(int n){
    char *str;
    str = malloc(20*sizeof(char));
    sprintf(str,"%d",n);
    return (char *)str;
}


int main(){
    pid_t cpid;
    char expression[5][50]={"addition","subtraction","multiplication","division"};
    int pipeFD[2];

    int status = pipe(pipeFD);
    
    if(status == -1){
        printf("Error!!\n");
        exit(-1);
    }
    
    int no1,no2;
    printf("Enter two Numbers: ");
    scanf("%d %d",&no1,&no2);
   

    for(int i=0;i<4;i++){

        cpid = fork();
        if(cpid==-1){
            printf("Error in %d'th fork\n",i+1);
            exit(-1);
        }
        
        else if(cpid == 0) {

            char path[]="./";
            strcat(path,expression[i]);

            char *pipe1 = itoa(pipeFD[0]);
            char *pipe2 = itoa(pipeFD[1]);
            char *num1 = itoa(no1);
            char *num2 = itoa(no2);
            
            execlp(path,pipe1,pipe2,num1,num2,NULL);
        }
        else if(cpid>0){
            
            wait(NULL);

            char buffer[50];
            read(pipeFD[0],buffer,sizeof(buffer));
            
            printf("Child ID : %u\n",cpid);
            printf("Result of %s: %s\n",expression[i],buffer);
            
        }
    }

    return 0;
}