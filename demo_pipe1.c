
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_MAX_LEN 1024

void parent_func(int* fd) {
    // fd[1] --> write
    char msg[1024];
    while(1){
        printf("[parent]输入要写到管道里的数据: ");
        if(fgets(msg, 1024, stdin) == NULL){
            printf("[parent]收到了来自键盘发送过来的Ctrl-D, 也就是EOF, 所以parent进程退出了\n");
            break;
        }
        write(fd[1], msg, strlen(msg)+1);
        sleep(2);
    }
    _exit(0);
}

void child_func(int* fd) {
    // fd[0] --> read
    char msg[1024];
    while (1)
    {
        read(fd[0], msg, 1024);
        printf("[child]收到了来自parent的数据 {{{\n%s}}}\n", msg);
    }
    _exit(0);
}


int main(int argc, char* argv[])
{
    int fd[2];
    if (pipe(fd)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    int val = fork();
    if(val < 0){
        perror("fork failed");
        return 1;
    } else if (val > 0) {
        //parent
        parent_func(fd);
        wait(NULL);
    } else {
        child_func(fd);
    }

    // char write_buffer[MSG_MAX_LEN+1];
    // char read_buffer[MSG_MAX_LEN];
    // scanf("%s", write_buffer);
    // write(fd[1], write_buffer, strlen(write_buffer)+1);
    // sleep(2);
    // read(fd[0], read_buffer, MSG_MAX_LEN);
    // printf("recieved %s\n", read_buffer);

    return 0;
}
