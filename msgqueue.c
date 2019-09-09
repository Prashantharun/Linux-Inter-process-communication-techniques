#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


struct messbuff{
int type;
char data[100];
};

struct mess_buff{
int type;
char data[100];
};


int main()
{
    struct messbuff message;
    struct mess_buff message1;     

    key_t key;   
    int msgid;    
    int msgcount;

    printf("Message queue sender process\n");
    
    // creating a key using ftok
    key = ftok("Prashanth",'r');
     
     // creating a message queue
      msgid = msgget(key, IPC_CREAT|0600 );
          
      // setting the messge type to 1
      message.type = 1;

     printf("Enter the to send :\n");
     scanf("%[^\n]",message.data);   
   
      // send the message via msgsnd
      msgsnd(msgid, &message, sizeof(message), 0);

     // data is sent
     printf("The data send is:\n");
     printf("%s\n",message.data);
      
     // receive the data using msgrcv
     msgcount = msgrcv(msgid,  &message1, sizeof(message1), 1, 0);
      
     printf("The count is %d\n",msgcount);
     printf("The data is %s\n",message1.data);
     
     // remove the message queue after receiving
     msgctl(msgid, IPC_RMID, NULL);
      
     return 0;
}
