#include <stdio.h>

int main()
{
    FILE *fp;
    char c;

    fp = fopen("ftest1.txt", "r");
    if (fp == NULL)
    {
        perror("Error in opening file");
        return (-1);
    }

    while (1)
    {
        c = fgetc(fp); // 一次只读一个字符
        if (feof(fp))
        { // 如果到文件结尾
            break;
        }
        printf("%c", c);
    }
    fclose(fp);

    return (0);
}

