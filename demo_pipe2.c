#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_MAX_LEN 1024

void parent_work(int fd[2], int rfd[2], int cpid)
{
    char send_msg[MSG_MAX_LEN];
    char recv_msg[MSG_MAX_LEN];
    while(1){
        printf("[父-%d] 请输入要发送给子进程的消息: ", getpid());
        if(fgets(send_msg, MSG_MAX_LEN, stdin) == NULL)
        {
            printf("[父-%d] 收到了来自键盘发送过来的Ctrl-D, 也就是EOF, 所以parent进程退出了\n", getpid());
            break;
        }

        //send message
        write(fd[1], send_msg, strlen(send_msg)+1);

        //wait for message
        read(rfd[0], recv_msg, MSG_MAX_LEN);

        //process message
        printf("[父-%d] 收到来自子进程(儿子-%d)的消息 {{{\n %s}}}\n", getpid(), cpid, recv_msg);

        if(strcmp(recv_msg, "CHILD_EXIT")==0){
            printf("[父-%d] 收到来自子进程的退出消息, 所以父进程也退出了\n", getpid());
            break;
        }
    }
    exit(0);
}

void child_work(int fd[2], int rfd[2]){
    char send_msg[MSG_MAX_LEN];
    char recv_msg[MSG_MAX_LEN];
    while(1){
        //wait for message
        read(fd[0], recv_msg, MSG_MAX_LEN);


        //process message
        printf("[子-%d] 收到来自父进程(爸爸-%d)的消息 {{{\n %s}}}\n", getpid(), getppid(), recv_msg);

        printf("[子-%d] 回复给父进程的消息, 请输入: ", getpid());
        if(fgets(send_msg, MSG_MAX_LEN, stdin) == NULL)
        {
            printf("[子-%d]收到了来自键盘发送过来的Ctrl-D, 也就是EOF, 所以child进程退出了\n", getpid());
            strcpy(send_msg, "CHILD_EXIT");
            write(rfd[1], send_msg, strlen(send_msg)+1);
            break;
        }
        //reply message
        write(rfd[1], send_msg, strlen(send_msg)+1);
    }
    exit(0);
}

int main(int argc, char* argv[])
{
    int fd[2];   // parent -> child
    int rfd[2];  // child -> parent

    int ret1 = pipe(fd);
    int ret2 = pipe(rfd);
    if (ret1 == -1 || ret2 == -1)
    {
        fprintf(stderr, "Pipe Failed");
        exit(1);
    }

    int pid = fork();
    if(pid >0){
        //parent
        parent_work(fd, rfd, pid);
    } else if(pid==0) {
        //child
        child_work(fd, rfd);
    } else {
        perror("fork failed");
        exit(1);
    }


    return 0;
}


