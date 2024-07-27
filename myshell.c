#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "./copy1.c"
#include "./echo.c"
#include "./move.c"

int main(void)
{ 
	const char *myargv[10];
	int myargc = 0;
	ssize_t readsize = 0;
	char cwd[100];
	const char* shellMsg = "Let's hear it!> ";
do
{	
	char commandline[100] = {0};
	myargc = 0;
	write(STDOUT_FILENO, shellMsg, strlen(shellMsg));
	readsize = read(STDIN_FILENO, commandline, 100);
	/* get the first argument */
	myargv[myargc] = strtok(commandline, " ");

	/*walk through other tokens*/
	while (myargv[myargc] != NULL )
	{
		myargc+=1;
                myargv[myargc] = strtok(NULL, " ");
		
	}
	
	/* check the command type*/
	if(strcmp(myargv[0], "cp") == 0)
	{	
		cp(myargc,myargv);
	
	}
	else if (strcmp(myargv[0], "mv") == 0)
		mv(myargc,myargv);
	else if (strcmp(myargv[0], "pwd\n") == 0) 
	{
             	printf("%s\n", getcwd(cwd,100));
	}
	else if (strcmp(myargv[0], "echo") == 0)
        {
                echo(myargc,myargv);

        }

	else if ((strcmp(myargv[0],"\n") == 0) || (strcmp(myargv[0],"echo\n") == 0));
	else if (strcmp(myargv[0],"exit\n") == 0)
		printf("Good Bye :)\n");
	else if (strcmp(myargv[0],"help\n") == 0)
	{
		printf("The supported commands:\n1- pwd: print the current working directory\n2- echo: print a user input string\n3- cp: copy contents of file to another (exist or created) file\n4- mv: move file from directory to another (or the same directory with different name)\n5- exit:terminate the shell\n6- help: print all the supported command with a brief info about each one\n");
	}
	else 
		printf("ana mesh hena\n");

}while(strcmp(myargv[0], "exit\n") != 0);
		
	return 0;
}
