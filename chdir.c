#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int fcd(int argc, const char **argv)
{
    /* remove the \n char from the last argument*/
    char *path = (char*) argv[argc-1];
    *(path+strlen(path)-1) = 0;
    if (argc == 1)
    {   
        chdir("/home/fatma");
        return 0;
    }
    else if (chdir(realpath(argv[1],path)) !=0)
    perror("fcd");
    return 0;
}
