#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>
       
int cp(int argc, const char **argv)
{ 
        struct stat path_stat;
	char buff[100];
        ssize_t rsize = 0;
        ssize_t wsize = 0;
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
	/* get the real path of the source and target files*/
	realpath(argv[1], srcpath);
	realpath(argv[2], dispath);
	argv[1] = srcpath;
	/* Check if the source and target are the same file*/
        if (strcmp(srcpath,dispath) == 0)
        {
                printf("cp: '%s' and '%s' are the same file\n",argv[1],argv[2]);
                return 0;
        }


	/*open the source and create the target file*/
        int srcd = open(argv[1], O_RDONLY);
        int distd = creat(argv[2],S_IRWXU);
	
	// Get the target path status
        stat(argv[2], &path_stat);

        if (srcd == -1 )
        {
                perror("source file");
                return 0;
        }
        if (distd == -1)
        {
		// Check if the path is a directory
        	if (S_ISDIR(path_stat.st_mode))
        	{	
            		srcfileName = basename(srcpath);
			strcat(dispath,"/");
              		strncat(dispath, srcfileName, strlen(argv[1]));
            		
			/* recheck for the source and target be the same file after concatination*/
			if (strcmp(srcpath,dispath) == 0)
        		{
                		printf("cp: '%s' and '%s' are the same file\n",argv[1],argv[2]);
                		return 0;
        		}
			distd = creat(argv[2],S_IRWXU);
        	}
		else
		{
			perror("target file");
                	return 0;
		}
        }
        /* read the source file content and write in the target*/
        do
        {
                rsize = read(srcd, buff, 100);
                wsize = write(distd, buff, rsize);
        }while(rsize == 100);

        /* check for read/write access*/
        if (rsize == -1 || wsize == -1)
        {
                perror("R/W access error");
                return 0;
        }

	/* close the files*/
        close(srcd);
        close(distd);
        return 0;	
}




