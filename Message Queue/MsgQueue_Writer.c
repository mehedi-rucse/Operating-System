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
    msg.msgType =1;
    strcpy(msg.buffer,"Operating System\n");

    //int msgsnd(int msgid,const *msgq,size,long msgtype,..);
    msgsnd(msqID,&msg,sizeof(msg),0);


    return 0;

}