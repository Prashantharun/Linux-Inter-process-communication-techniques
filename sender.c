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

    printf("Message queue sender process\n");
    
    // creating a key using ftok
    key = ftok("Prashanth",'r');
     
     // creating a message queue
      msgid = msgget(key, IPC_CREAT|0600 );
          
      // setting the messge type to 1
      message.type = 2;

     printf("Enter the data to send :\n");
     scanf("%[^\n]",message.data);   
   
      // send the message via msgsnd
      msgsnd(msgid, &message, sizeof(message), 0);
       printf("Sending the data.........\n");          

     // data is sent
     printf("The data sent is:\n");
     printf("%s\n",message.data);

     return 0;
}
