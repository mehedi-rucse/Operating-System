#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main(int argc,char *args[]){
    char *str;
    
    int pipe0 = atoi(args[0]);
    int pipe1 = atoi(args[1]);
    int a = atoi(args[2]);
    int b = atoi(args[3]);
    float c = (float)a/b;
    
    sprintf(str, "%.3f", c);

    if(b==0){
        write(pipe1,"Not Possible",13);
    }
    else{
        close(pipe0);
        char *div = str;
        
        write(pipe1,div,strlen(div)+1);
    }
    
    
    return 0;
}