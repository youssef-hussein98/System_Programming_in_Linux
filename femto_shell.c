/*  Femto Shell

	Implement a simple program in c language that acts as a Shell 
	(but very simple shell - Femto Shell) that supports the following built in commands

    echo: echoes any text entered by the user.

    exit: If the user entered "exit", the shell will reply with "Good Bye" and terminate.

    print an "Invalid command" error if the user entered any command other than "echo" and "exit".
*/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFF_SIZE 100

int print_header(void)
{
	char *header = "Femto Shell > ";
	int write_count = write(STDOUT_FILENO, header, strlen(header));
	if (write_count != (int)strlen(header)) {
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[]) 
{
	char buff[BUFF_SIZE] = {0};
	char *exit_msg = "Good Bye\n";
	char *error_msg = "Invalid command\n";
	int run_app = 1;
	int read_count = 0;

	while (run_app)
	{
		print_header();
		read_count = read(STDIN_FILENO,buff, 5);

		if(strncmp(buff, "exit", 4) == 0) 
		{
			
			write(STDOUT_FILENO, exit_msg, strlen(exit_msg));
			run_app = 0;
			continue;
		}
		else if(strncmp(buff, "echo", 4) == 0) 
		{
			do
			{
				read_count = read(STDIN_FILENO, buff, sizeof(buff));
				write(STDOUT_FILENO, buff, read_count);
			} while (read_count > 0);
			continue;
		}
		else if((buff[0] == '\n' || buff[0] == '\0') && (read_count ==1)) 
		{
			continue; // Ignore empty input
		}
		else 
		{
			write(STDOUT_FILENO, error_msg, strlen(error_msg));
			while ((buff[read_count - 1] != '\0') && (buff[read_count - 1] != '\n')) 
			{
				read_count = read(STDIN_FILENO, buff, sizeof(buff));
			}
		}
	}

    return 0;
}