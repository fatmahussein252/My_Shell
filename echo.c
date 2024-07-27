#include <stdio.h>
#include <string.h>
#include <unistd.h>

int echo(int argc, const char **argv)
{
	for(int i = 1; i< argc-1; i++)
	{
		for (int s = 0; s < strlen(argv[i]); s++)
		{	
			if (*(argv[i]+s) == 39 || *(argv[i]+s) == 34);
			else
				printf("%c",*(argv[i]+s));
	
		}
		printf(" ");
	}
	for (int s = 0; s < strlen(argv[argc-1]); s++)
        {
                if (*(argv[argc-1]+s) == 39 || *(argv[argc-1]+s) == 34);
                else
                        printf("%c",*(argv[argc-1]+s));

        }

}

