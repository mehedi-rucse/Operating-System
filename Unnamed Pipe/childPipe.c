#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

char *itoa(int n){
    char *sum;
    sum = malloc(20*sizeof(char));
    n = abs(n);
    int i=0;
    if(n==0){
        return "0";
    }
    while(n){
        sum[i]=n%10+'0';
        n/=10;
        i++;
    }
    
    sum[i]='\0';
    for(int k=0;2*k<i;k++){
        char ch = sum[k];
        sum[k] = sum[i-k-1];
        sum[i-k-1] = ch;
    }
    
    return (char *)sum;
}


int main(int argn,char *argv[]){

	char msg[20];
    gets(msg);
    printf("%s \n",msg);

    int fd0 = atoi(argv[0]);
    int fd1 = atoi(argv[1]);
  

	printf("Child Process is writing to the pipe.\n");
	close(fd0);

	
	write(fd1, msg, strlen(msg) + 1);
	return 0;
}
