#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	/* number of characters written */
	int ch_written = 0;

	for(int i = 1; i < argc; i++)
	{
		ch_written = write(STDOUT_FILENO, argv[i],strlen(argv[i]));
		if(ch_written == strlen(argv[i])) 
		{
			if(i < (argc -1))
			{
				/* write a space after each argument except the last one */
				ch_written = write(STDOUT_FILENO, " ",1);
				if(ch_written != 1)
				{
					exit(-2);
				}
			}
		}
		else
		{
			exit(-1);
		}
	}
    
    /* write a newline at the end */
	ch_written = write(STDOUT_FILENO, "\n",1);
	if(ch_written != 1)
	{
		exit(-3);
	}	
	
	return 0;
}
