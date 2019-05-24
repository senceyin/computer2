#include <stdio.h>
#include <string.h>

#define LINE_MAX_LEN 1024

int main()
{
    FILE *fp;
    char buffer[LINE_MAX_LEN + 1];

    // 打开文件流
    fp = fopen("ftest1.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return (-1);
    }
    int count=0;
    while (fgets(buffer, LINE_MAX_LEN, fp) != NULL)
    {
        //处理当前行
        printf("fgets buffer -> %s\n", buffer);
        // if(strlen(buffer)>10){
        //     puts(buffer);
        //     count++;
        // }
    }
    printf("there are %d lines more than 10 char\n", count);
    fclose(fp);

    return (0);
}

