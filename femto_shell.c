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
	char *prompt_msg = "Femto Shell > ";
	int run_app = 1;
	int read_count = 0;
	
	/* make stdin read nonblock */
	int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

	while (run_app)
	{
		
		write(STDOUT_FILENO, prompt_msg, strlen(prompt_msg));
		do 
		{
			read_count = read(STDIN_FILENO, buff, BUFF_SIZE);
		}while(read_count == -1);

		if(strlen(buff) == 1 && buff[strlen(buff) - 1] == '\n') 
		{
			continue; // Ignore empty input
		}
		else if((strncmp(buff, "exit", 4) == 0) && (buff[4] == '\n' || buff[4] == '\0' || buff[4] == ' ')) 
		{
			printf("%s", exit_msg);
			run_app = 0;
			continue;
		}
		else if((strncmp(buff, "echo", 4) == 0) && (buff[4] == '\n' || buff[4] == '\0' || buff[4] == ' '))
		{
			write(STDOUT_FILENO, buff+5, read_count - 5);
			if(read_count < BUFF_SIZE)
			 continue; // If no more input, continue to next iteration

			do 
			{
				read_count = read(STDIN_FILENO, buff, BUFF_SIZE);
				write(STDOUT_FILENO, buff, read_count);
			}while(read_count == BUFF_SIZE);
		}
		else 
		{
			write(STDOUT_FILENO, error_msg, strlen(error_msg));
			do 
			{
				/* empty stdin */
				read_count = read(STDIN_FILENO, buff, BUFF_SIZE);
			}while(read_count == BUFF_SIZE);
		}
	}

    return 0;
}