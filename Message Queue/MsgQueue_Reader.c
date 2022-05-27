#include<sys/msg.h>
#include<stdio.h>
#include<string.h>

struct msgbuf{
   long msgType;
   char buffer[100];
}msg;



int create_msgQ(char *path){

    key_t key;
	int msqID;
	key = ftok(path, 'a');
	msqID = msgget(key, IPC_CREAT | 0666);

	return msqID;   
}


int main(){
    int msqID;
    msqID = create_msgQ("MessageQueue.c");

    //Prepare data
    

    //int msgsnd(int msgid,const *msgq,size,long msgtype,..);
    msgrcv(msqID,&msg,sizeof(msg),1,0);
    printf("Data Received is : %s \n", 
                    msg.buffer);


    return 0;

}