#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
int mv(int argc, const char **argv)
{
	struct stat newpath_stat;
	struct stat oldpath_stat;
	stat(argv[1], &newpath_stat);
	if (stat(argv[1], &oldpath_stat) != 0)
       	{
        	perror("source stat");
        	return 0;
       	}

    	// Check if the path is a directory
    	if (S_ISDIR(oldpath_stat.st_mode))
       	{
        	printf("The source path is a directory.\n");
    		return 0;
	}

	/* store the target pathname in modifiable array*/
	char temp[100];
	strncpy(temp, argv[2], strlen(argv[2]));
	/* delete the "\n" char from the target path (If it was the last arguement in the argv)*/
	if (argc == 3)
	{
        	temp[strlen(argv[2])-1] = 0;
	}
	argv[2] = temp;
    	
	/*Check for names conflicts in the target directory*/
	if(access(argv[2],F_OK) == 0)
	{	
		/* Check if the found pathname is directory or repeated file name*/
		// Get the target path status
        	stat(argv[2], &newpath_stat); 
		// Check if the path is a directory
                if (S_ISDIR(newpath_stat.st_mode))
                {
                        //check if the path ends with back slash or no
                        if (*(argv[2]+strlen(argv[2])-1) == '/')
                        {
                                strncat(temp, argv[1], strlen(argv[1]));
                        }
                        else
                        {
                                strcat(temp,"/");
                                strncat(temp, argv[1], strlen(argv[1]));
                        }
			/* recheck for names conflicts after concatinating the source file name*/
                        if(access(argv[2],F_OK) == 0)
                        {
                                printf("A file with the same name exists in the target directory\n");
                                return 0;
                        }
                        
                }
		else if (S_ISREG(newpath_stat.st_mode))
		{
			if(access(argv[2],F_OK) == 0)
                        {
				printf("A file with the same name exists in the target directory\n");
                        	return 0;
		
			}
		}
		else
		{
			printf("target path: No such file or directory\n");
			return 0;
		}
	}

	/* move the file*/
	int ret = rename(argv[1],argv[2]);
	
    	return 0;
}

