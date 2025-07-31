#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) 
{

    /* old file should not be the same as new file */
    if(argc < 3 || (strcmp(argv[1], argv[2]) == 0)) 
    {
        exit(-1);
    }
    
    int readfile = open(argv[1],  O_RDONLY);
    int writefile = open(argv[2], O_WRONLY | O_TRUNC);
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
    }
    while(read_count > 0 && write_count > 0);

    close(readfile);
    unlink(argv[1]);
    close(writefile);
    return 0;
}