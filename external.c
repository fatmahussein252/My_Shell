#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int external(int argc, const char **argv)
{
	char *lastarg = (char *)argv[argc-1];
	*(lastarg+strlen(lastarg)-1) = 0;
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
		else
			exit(EXIT_SUCCESS);
	}

}
