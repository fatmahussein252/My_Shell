#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./internal.h"

int external(int argc, const char **argv)
{
	strtok((char *)argv[argc-1],"\n");
	
	int pipeFd[2] = {0};
	char **argv1 = (char**)malloc(10*sizeof(char *));
	int argc1 = 0;
	char **argv2 = (char**)malloc(10*sizeof(char *));
	int argc2 = 0;
	int piperet = -1;
	int pipechar;
	/* get the pipe char index if exist*/
	for (pipechar = 0; pipechar < argc; pipechar++)
	{
		if (strcmp(argv[pipechar],"|") == 0)
		{
		piperet = pipe(pipeFd);
		break;
		}
	}
	/*if pipe exist, split the argv*/
	if (piperet != -1)
	{
		argc1 = pipechar;
		for (int i = 0; i < argc1; i++)
		{
		argv1[i] = (char*)malloc(sizeof(argv[i]));
		argv1[i] = (char*)argv[i];
		}
		for (argc2 = 0; argc2 < argc-argc1-1 ; argc2++)
		{
		argv2[argc2] = (char*)malloc(sizeof(argv[argc2+pipechar+1]));
		argv2[argc2] = (char*)argv[argc2+pipechar+1];
		}
	}
	/*if pipe exist, fork twice*/
	if (piperet != -1)
	{
	int retf1 = fork();
	if (retf1 > 0)
	{	
		int retf2 = fork();
		if (retf2 > 0)
		{	
			close(pipeFd[0]); // Close both ends of the pipe
            		close(pipeFd[1]);
			int status = 0;
           		 // Wait for both children
          		  waitpid(retf1, &status, 0);
        		  waitpid(retf2, &status, 0);
         	 	  return 0;
     			 
		}
		if (retf2 == 0)
		{
			close(pipeFd[1]);
			redirect(0,pipeFd[0]);
			if (execvp(argv2[0],(char *const *)argv2) != 0)
        		{
        		printf("%s: command not found\n",argv2[0]);
        		exit(EXIT_FAILURE);
			}
		}
		
	}
	if(retf1 == 0)
	{	
		close(pipeFd[0]);
		redirect(1,pipeFd[1]);
		 if (execvp(argv1[0],(char *const *)argv1) != 0)
        	{
        		printf("%s: command not found\n",argv1[0]);
        		exit(EXIT_FAILURE);
		}
					
	}
	}
	/*if not piped, fork once and run the process*/
	else 
	{
	int retf = fork();
	
	if (retf > 0)
	{
		int status =0;	
		int childPid = wait(&status);
		return 0;
	}
	if(retf == 0)
	{
        	if (execvp(argv[0],(char *const *)argv) != 0)
        	{
        		printf("%s: command not found\n",argv[0]);
        		exit(EXIT_FAILURE);
		}
	}

	}

}
