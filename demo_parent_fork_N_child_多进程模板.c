
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    const int N = 10;
    pid_t child_pid_array[N];
    for (size_t i = 0; i < N; i++)
    {
        pid_t val = fork();
        if (val == 0)
        {
            // child's job area
            sleep(1);
            printf("yo I am child[pid=%d]\n", getpid());
            _exit(0);
        } else {
            child_pid_array[i] = val;
        }
    }
    // parent job area


    //wait your children
    for (int i = 0; i < N; i++)
    {
        int return_status;

        waitpid(child_pid_array[i], &return_status, 0);
        // printf("\nreturned status: %d\n", return_status);
    }
    printf("parent finished\n");
    // wait(NULL);
    
    return 0;
}


