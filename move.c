#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
int mv(int argc, const char **argv)
{
	struct stat newpath_stat;
	struct stat oldpath_stat;
	char srcpath[50];
        char dispath[50];
        char *srcfileName;


	/* store the target pathname in modifiable array*/
	strncpy(dispath, argv[2], strlen(argv[2]));
	/* delete the "\n" char from the target path (If it was the last arguement in the argv)*/
	if (argc == 3)
	{
        	dispath[strlen(argv[2])-1] = 0;
	}
	argv[2] = dispath;
	/*Get the real path for tha source and target*/
	realpath(argv[1],srcpath);
	realpath(argv[2],dispath);
	if(strcmp(srcpath,dispath)==0)
	{
		printf("A file with the same name exists in the target directory\n");
                return 0;

	}
	/*check for the validity of the source path*/
	if (srcpath == NULL)
	{
		perror("source path");
		return 0;
	}
	/*Check for names conflicts in the target directory*/
	if(access(argv[2],F_OK) == 0)
	{	
		/* Check if the found pathname is directory or repeated file name*/
		// Get the target path status
        	stat(argv[2], &newpath_stat); 
		// Check if the path is a directory
                if (S_ISDIR(newpath_stat.st_mode))
                {
                        srcfileName = basename(srcpath);
			//check if the path ends with back slash or no
                        if (*(argv[2]+strlen(argv[2])-1) == '/')
                        {
                                strncat(dispath, srcfileName, strlen(srcfileName));
                        }
                        else
                        {
                                strcat(dispath,"/");
                                strncat(dispath, srcfileName, strlen(srcfileName));
                        }
			/* recheck for names conflicts after concatinating the source file name*/
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
	if (ret == -1)
	{	
		perror("Couldn't move this file");
		return 0;
		
	}	
    	return 0;
}

