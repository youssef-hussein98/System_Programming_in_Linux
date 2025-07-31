#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    /* if data is not passed correctly */
    if(argc !=3)
    {
        char* error_msg = "Usage: cp oldfilePath newfilePath\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(-1);
    }
    
    /* Open read file and write file, truncate write file */
    int readfile = open(argv[1],  O_RDONLY );
    int writefile = open(argv[2], O_WRONLY | O_TRUNC);
    /* error opening one of the files */
    if(readfile < 0 || writefile < 0)
    {
        exit(-2);
    }

    char buff[100];
    int read_count = 0;
    int write_count = 0;
    do
    {
        read_count = read(readfile, buff, 100);
        write_count = write(writefile, buff, read_count);

    }while(read_count > 0 && write_count > 0);

    /* close files at the end*/
    close(readfile);
    close(writefile);

    return 0;
}

