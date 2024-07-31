#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "./copy1.c"
#include "./echo.c"
#include "./move.c"
#include "./external.c"
#include "./chdir.c"
#include "./type.c"
#include "./printEnv.c"

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD_Mgenta "\033[1;35m"
#define COLOR_BOLD_YELLOW "\033[1;33m"
#define COLOR_BOLD_Cyan "\033[1;36m"

int main(void)
{ 
	const char *myargv[10];
	int myargc = 0;
	ssize_t readsize = 0;
	char cwd[100];
	char colorCWD[200];
	const char* shellMsg = COLOR_BOLD_Mgenta"What's Cooking?> "COLOR_RESET;

do
{	
	char commandline[100] = {0};
	myargc = 0;
	getcwd(cwd,100);
	snprintf(colorCWD, sizeof(colorCWD), "%s%s$ %s", COLOR_BOLD_Cyan, cwd, COLOR_RESET);
	write(STDOUT_FILENO, colorCWD, strlen(colorCWD));
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
	if(strcmp(myargv[0], "fcp") == 0 || strcmp(myargv[0], "fcp\n") == 0)
	{	
		/* check for operands*/
		if (myargc < 3)
		{
		printf("fcp: missing file operand\n");
		continue;
		}
		else
		cp(myargc,myargv);
	
	}
	else if (strcmp(myargv[0], "fmv") == 0 || strcmp(myargv[0], "fmv\n") == 0)
	{	
		if (myargc < 3)
		{
		printf("fmv: missing file operand\n");
		continue;
		}
		else
		mv(myargc,myargv);
	}
	else if (strcmp(myargv[0], "fpwd\n") == 0) 
	{
		getcwd(cwd,100);
             	printf("%s\n", cwd);
	}
	else if (strcmp(myargv[0], "fecho") == 0)
        {
                echo(myargc,myargv);
        }
	else if (strcmp(myargv[0], "fcd") == 0 || strcmp(myargv[0], "fcd\n") == 0)
        {
                fcd(myargc,myargv);
        }
	else if(strcmp(myargv[0], "ftype") == 0 || strcmp(myargv[0], "ftype\n") == 0)
	{
		type(myargc,myargv);
	}
	else if(strcmp(myargv[0], "fenv\n") == 0)
	{
		env(myargc,myargv);
	}
	else if ((strcmp(myargv[0],"\n") == 0) || (strcmp(myargv[0],"fecho\n") == 0));
	else if (strcmp(myargv[0],"fexit\n") == 0)
		printf(COLOR_BOLD_YELLOW "Good Bye :)\n" COLOR_RESET);
	else if (strcmp(myargv[0],"fhelp\n") == 0)
	{
		printf("The supported commands:\n1- fpwd: print the current working directory\n2- fecho: print a user input string\n3- fcp: copy contents of file to another (exist or created) file\n4- fmv: move file from directory to another (or the same directory with different name)\n5- fexit:terminate the fshell\n6- fhelp: print all the supported command with a brief info about each one\n7- fcd: change the current directory\n8- ftype: return the type of the command (internal, external or unsupported command)\n9- fenv: print all the environment variables\n");
	}
	else
		external(myargc,myargv);


}while(strcmp(myargv[0], "fexit\n") != 0);
		
	return 0;
}
