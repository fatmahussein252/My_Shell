#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void redirect(int oldfd, int newfd);

void redirect(int oldfd, int newfd)
{
	if (newfd < 0)
	{
		printf("open error\n");
		return;
	}
	int fd = dup2(newfd,oldfd);
	if (fd != oldfd)
	{
	//	sprintf("error dup2");
		return;
	}
close(newfd);	
}
