#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "forkit.h"

#define STRING_MAX_LEN 1024
char g_buffer[STRING_MAX_LEN];

//Question 1 -- solution-1:
void read_file(const char *filename, char ***data, int *len)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    //文件打开函数之后, 一定要记得判错
    {
        perror("readfile failed");
        exit(1);
    }
    int total_line_num = 1024;
    char **ret_data = malloc(sizeof(char *) * total_line_num);
    int i = 0;
    while (fgets(g_buffer, STRING_MAX_LEN, f) != NULL)
    //将数据流按行读入
    {
        int alloc_len = (strlen(g_buffer) + 1);
        ret_data[i] = malloc(sizeof(char) * alloc_len);
        strcpy(ret_data[i], g_buffer);
        i++;
        (*len)++;
        if (i >= total_line_num) 
        // 如果空间不足, 则需要通过realloc原地拓展一下, 将原来的容量扩容.
        {
            total_line_num *= 2;
            ret_data = realloc(ret_data, sizeof(char) * STRING_MAX_LEN * total_line_num);
        }
    }
    fclose(f);

    *data = ret_data;
}























//Question 1 -- solution-2:
int count_lines(FILE *fp)
{
    fseek(fp, 0, SEEK_SET);
    int lines = 0;
    char ch;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            lines++;
        }
    }
    fseek(fp, 0, SEEK_SET);
    return lines;
}

//TODO solution-2


//Question 2
void create_processes(int n, char **data, int len)
{
    int chunk = len / n;
    pid_t *child_pid_array = malloc(sizeof(pid_t) * n);
    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
        {
            //1. 子进程任务划分
            int id = i;
            int start = id * chunk;
            int end = start + chunk;
            if(id == n - 1){
                end = len; // 处理除不尽的case
            }
            //2. 子进程do job
            for (int i = start; i < end; i++)
            {
                printf("%d:%s", id, data[i]);
            }
            //3 清理内存空间, 按题目要求 -> 子进程需要free因为fork带来的data clone
            for (int j = 0; j < len; j++)
            {
                free(data[j]);
            }
            free(data);
            free(child_pid_array);

            exit(0);
        }
        else
        {
            //parent 记录一下子进程的pid
            child_pid_array[i] = pid;
        }
    }

    //下面wait的方式, 二选一即可
    //方式一:
    for (int i = 0; i < n; i++)
    {
        int return_status;

        waitpid(child_pid_array[i], &return_status, 0);
        // printf("\nreturned status: %d\n", return_status); fflush(stdout);
    }
    //方式二:
	// for(int i = 0; i< n;i++){
	// 	wait(NULL);
	// }

    free(child_pid_array);
    return;
}


