#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

char *typeConversion(int num){
    char *str;
    str = malloc(20*sizeof(char));
    num = abs(num);
    int i=0;
    if(num==0){
        return "0";
    }
    while(num){
        str[i]=num%10+'0';
        num=num/10;
        i++;
    }
    
    str[i]='\0';
    for(int k=0;2*k<i;k++){
        char ch = str[k];
        str[k] = str[i-k-1];
        str[i-k-1] = ch;
    }
    
    return (char *)str;
}


int main(int argc,char *args[]){

	char msg[20];
    gets(msg);

    int fd0 = atoi(args[0]);
    int fd1 = atoi(args[1]);
	printf("Child Process is writing to the pipe.\n");

	close(fd0);
	write(fd1, msg, strlen(msg) + 1);
    
	return 0;
}
