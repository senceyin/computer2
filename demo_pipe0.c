#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_MAX_LEN 1024

int main(int argc, char* argv[])
{
    int fd[2];
    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    char write_buffer[MSG_MAX_LEN+1];
    char read_buffer[MSG_MAX_LEN];
    scanf("%s", write_buffer);
    write(fd[1], write_buffer, strlen(write_buffer)+1);
    sleep(2);
    read(fd[0], read_buffer, MSG_MAX_LEN);
    printf("recieved %s\n", read_buffer);

    return 0;
}
