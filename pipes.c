#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


#define STDIN  0
#define STDOUT 1
#define STDERR 2

int main (int argc, char **argv)
{
  int retPid;
  int childPid = 0;
  int childStatus = 0;
  int size = 0;
  char cmdLine[100];
  char* cmd;
  char* argList[10];
  int i =0;
  const char * shellMsg = "command>";
 
  int pipeFd[2];
  char buff[100];
  int ret = pipe(pipeFd);


  write(STDOUT, shellMsg, strlen(shellMsg));

  size = read (STDIN, cmdLine, 100);

  cmdLine[size - 1] = '\0';
  
  argList[i] = strtok(cmdLine, " ");
  
  while(argList[i] != NULL)
  {
     i++;
     
     argList[i] = strtok(NULL, " ");

  }
  
  cmd = argList[0];
   
  printf("len = %d\n", strlen(cmd));

  retPid = fork();

  if (retPid > 0)
  {
      printf("This is the parent\n the current PID = %d, the child pid = %d\n",
	      getpid (), retPid);
      
      printf ("Parent Message\n");

	read(pipeFd[0], buff, 100);
      printf("msg = %s\n", buff);



      childPid = wait (&childStatus);
	
      if (childPid == retPid)
	{
	  printf ("child exit status = %d\n", WEXITSTATUS (childStatus));
	}
      else
	{
	  perror ("wait");
	}

  }
  else if (retPid == 0)
  {

      printf ("This is the Child\n, current PID = %d\n", getpid ());      
	
       write(pipeFd[1] , "hello", strlen("hello"));
      int pid = execvp(cmd, argList);

      if (pid <= 0)
	{
	  perror ("exec");
	  exit(10);
	}

  }
  else
  {

      perror ("fork");
  }
}
