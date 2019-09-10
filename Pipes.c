#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[])         // command line arguments
{
   int pipefd[2];
   pid_t cpid;
   char buf;
  
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
 // Check if 2 arguments are entered correctly

   if(argc != 2)
    { 
       fprintf(stderr,"Usage: %s <string>\n",argv[0]);
       exit(EXIT_FAILURE);
    }
   
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

 // Check if pipe creation failed

   if(pipe(pipefd) == -1)
    {
         perror("pipe creation failed\n");
         exit(EXIT_FAILURE);
    }

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ 

 // Create a child process and collect a child process id
  
  cpid = fork();
  
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Check if fork failed
  
    if(cpid == -1)
    {
         perror("fork failed\n");
         exit(EXIT_FAILURE);
    }

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Allow child process to read the data

   if(cpid == 0)
   {
      //  0|----------|1   <--- Parent side is closed
      //   |----------|
      
      close(pipefd[1]);
    
         while(read(pipefd[0], &buf, 1) > 0)
            {
               write(STDOUT_FILENO, &buf, 1);
            }

     write(STDOUT_FILENO, "\n", 1);
     
     exit(EXIT_SUCCESS);
   }
  else
  {
      // child side is closed ---> 0|----------|1   
      //                            |----------|

      close(pipefd[0]);

      // Write and Close the pipe
       
      write(pipefd[1], argv[1], strlen(argv[1]));
      
      close(pipefd[1]);
       
      wait(NULL);
      
      exit(EXIT_SUCCESS);
  }

}




   

       



