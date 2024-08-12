#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include "./internal.h"

#define COLOR_RESET "\033[0m"
#define COLOR_BOLD_Mgenta "\033[1;35m"
#define COLOR_BOLD_YELLOW "\033[1;33m"
#define COLOR_BOLD_Cyan "\033[1;36m"

int main(void)
{ 
	const char *myargv[10];
	const char ** cmdhistory = (const char**)malloc(100*sizeof(char*));
	int cmdcount = 0;
	int myargc = 0;
	ssize_t readsize = 0;
	char cwd[100];
	char colorCWD[200];
	const char* shellMsg = COLOR_BOLD_Mgenta"What's Cooking?> "COLOR_RESET;
	int outfd = 1;
	int dupout;
	int errfd = 2;
        int duperr;
	int infd = 0;
        int dupin;
do
{	
	
	char commandline[100] = {0};
	myargc = 0;
	getcwd(cwd,100);
	snprintf(colorCWD, sizeof(colorCWD), "%s%s$ %s", COLOR_BOLD_Cyan, cwd, COLOR_RESET);
	write(STDOUT_FILENO, colorCWD, strlen(colorCWD));
	write(STDOUT_FILENO, shellMsg, strlen(shellMsg));
	readsize = read(STDIN_FILENO, commandline, 100);
	cmdhistory[cmdcount] = (const char*)malloc(sizeof(commandline));
	cmdhistory[cmdcount] = strdup(commandline);
	cmdcount++;
	/* get the first argument */
	myargv[myargc] = strtok(commandline, " ");
	/*walk through other tokens*/
	while (myargv[myargc] != NULL )
	{
		myargc+=1;
                myargv[myargc] = strtok(NULL, " ");
		
	}
	char **modifiedargs = (char **) myargv; //this array used to edit the arguments array after redirection if exist
	for (int c = 0;c < myargc;c++)
	{	
		if (strcmp(myargv[c],"to>") == 0)
		{
			dupout = dup(1);
			if (c == myargc-2)
				strtok((char*)myargv[c+1],"\n");
			outfd = creat(myargv[c+1],S_IRWXU);
			redirect(1,outfd);
			/*remove redirection argumets from array of arguments*/
			modifiedargs[c] = NULL;
			modifiedargs[c+1] = NULL;
			myargc=myargc-2;
			continue;
			
		}
		if (strcmp(myargv[c],"err>") == 0)
                {
                        duperr = dup(2);
                        if (c == myargc-2)
				strtok((char*)myargv[c+1],"\n");
                        errfd = open(myargv[c+1],O_WRONLY);
                        redirect(2,errfd);
                        /*remove redirection argumets from array of arguments*/
                        modifiedargs[c] = NULL;
			modifiedargs[c+1] = NULL;
			myargc=myargc-2;
                        continue;

                }
                if (strcmp(myargv[c],"from<") == 0)
                {
                        dupin = dup(0);
                        if (c == myargc-2)
				strtok((char*)myargv[c+1],"\n");
                        infd = open(myargv[c+1],O_RDONLY);
                        redirect(0,infd);
                        /*remove redirection argumets from array of arguments*/
                        modifiedargs[c] = NULL;
			modifiedargs[c+1] = NULL;
			myargc=myargc-2;
                        continue;
                }
	}
	/* check the command */
	if (strcmp(myargv[0], "history\n") == 0)
	{
		for(int i = 0; i < cmdcount; i++)
		{
		if (strcmp(cmdhistory[i],"\n") == 0);
		else
		printf("%s",cmdhistory[i]);
		}
	}
	else if(strcmp(myargv[0], "fcp") == 0 || strcmp(myargv[0], "fcp\n") == 0)
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
	else if (strcmp(myargv[0], "fpwd\n") == 0 || strcmp(myargv[0],"fpwd") == 0) 
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
	else if(strcmp(myargv[0], "fenv\n") == 0 || strcmp(myargv[0], "fenv") == 0)
	{
		env(myargc,myargv);
	}
	else if(strcmp(myargv[0], "ffree\n") == 0 || strcmp(myargv[0],"ffree") == 0)
        {
                ffree(myargc,myargv);
        }
	else if(strcmp(myargv[0], "fuptime\n") == 0)
        {
                uptime(myargc,myargv);
        }
	else if ((strcmp(myargv[0],"\n") == 0) || (strcmp(myargv[0],"fecho\n") == 0));
	else if (strcmp(myargv[0],"fexit\n") == 0)
		printf(COLOR_BOLD_YELLOW "Good Bye :)\n" COLOR_RESET);
	else if (strcmp(myargv[0],"fhelp\n") == 0 || strcmp(myargv[0],"fhelp") == 0)
	{
		printf("The supported commands:\n"
		"1- fpwd: print the current working directory\n"
		"2- fecho: print a user input string\n"
		"3- fcp: copy contents of file to another (exist or created) file\n"
		"4- fmv: move file from directory to another (or the same directory with different name)\n"
		"5- fexit:terminate the fshell\n"
		"6- fhelp: print all the supported command with a brief info about each one\n"
		"7- fcd: change the current directory\n"
		"8- ftype: return the type of the command (internal, external or unsupported command)\n"
		"9- fenv: print all the environment variables\n"
		"10- ffree:\n"
		"11- fuptime:\n");
	}
	else
	{
		external(myargc,myargv);
	}
	if (outfd != 1)
	{
	redirect(1,dupout);
	close(dupout);
	}
	if (errfd != 2)
        {
        redirect(2,duperr);
        close(duperr);
        }
       if (infd != 0)
        {
        redirect(0,dupin);
        close(dupin);
        } 

}while(strcmp(myargv[0], "fexit\n") != 0);
		
	return 0;
}
