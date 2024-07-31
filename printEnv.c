#include <stdio.h>

extern char** environ;
int env(int argc, const char **argv)
{
	int i =0 ;
	while(environ[i] !=NULL)
	{
		printf("%s\n", environ[i++]);
	}
return 0;
}
