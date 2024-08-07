#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int type(int argc,const char **argv)
{
	char *cmds[9] = {"fcp","fmv","fecho","fpwd","fcd","ftype","fenv","fhelp","fexit"};
	if (argc == 1)
	{
		printf("ftype: missing command operand\n");
		return 0;
	}
	/* remove the \n char from the last argument*/
    	char *lastarg = (char*) argv[argc-1];
    	*(lastarg+strlen(lastarg)-1) = 0;

	char *path = getenv("PATH");
	if (path == NULL)
       	{
        	fprintf(stderr, "Error: PATH environment variable is not set.\n");
        	return 0;
    	}

	for (int i = 1; i < argc; i++)
	{
    		char *path_copy = strdup(path);
		char *dir = strtok(path_copy, ":");
    		while (dir != NULL)
	       	{
        	char full_path[1024];
        	snprintf(full_path, sizeof(full_path), "%s/%s", dir, argv[i]);
        	if (access(full_path, X_OK) == 0)
	       	{
            		printf("%-5s: external command\n",argv[i]); // Command is external
        		break;
		}	
        	dir = strtok(NULL, ":");
    		}
    		free(path_copy);
		if(dir == NULL)
		{
			int c;
                	for (c = 0; c < 9 ; c++)
                	{
                       	if (strcmp(argv[i],cmds[c]) == 0)
                       	{
                            printf("%-5s: internal command\n",argv[i]);
                            break;
                       	}
                	}	
                	if (c == 9)
                       	    printf("%-5s: command not found\n",argv[i]);
		}
	}
	return 0;
}
