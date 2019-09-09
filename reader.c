#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct messbuff{
int type;
char data[100];
};

int main()
{
    struct messbuff message;

    key_t key;   
    int msgid;    
    int msgcount;
 
    printf("Message queue receiver process\n");
    
    // creating a key using ftok
    key = ftok("Prashanth",'a');
     
     // creating a message queue
      msgid = msgget(key, IPC_CREAT|0600 );   
   
      // send the message via msgsnd
     msgcount = msgrcv(msgid, &message, sizeof(message), 2, 0);
     //printf("The no of char is : %d\n",msgcount);    
 
     // data is recieved
     printf("The data is received successfully !:\n");
     printf("%s\n",message.data);

    // remove the message queue after receiving
     msgctl(msgid, IPC_RMID, NULL);
     return 0;
}
