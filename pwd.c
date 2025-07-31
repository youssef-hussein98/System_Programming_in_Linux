#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATH_MAX 200
int main(void)
{
    char path_buff[PATH_MAX] = {0};
    char* ret_buff = NULL;
    ret_buff = getcwd(path_buff, PATH_MAX);
    if (ret_buff == NULL) {
        exit(-1);
    }
    path_buff[strlen(ret_buff)] = '\n'; /* put end of line at the end*/   
    
    /* print current working directory */
    int write_count = write(STDOUT_FILENO, path_buff, strlen(path_buff));
    if (write_count != strlen(path_buff)) {
        exit(-2);
    }
    
    return 0; 
}