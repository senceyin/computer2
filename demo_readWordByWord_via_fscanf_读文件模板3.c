#include <stdio.h>

#define MAX_WORD_LEN 512

int main()
{
    FILE *fp;

    fp = fopen("ftest1.txt", "r");
    if (fp == NULL)
    {
        perror("Error in opening file");
        return (-1);
    }

    char word[MAX_WORD_LEN];
    while (fscanf(fp, "%s", word) != EOF)
    {
        // process the word
        printf("[%s]\n", word);
    }
    fclose(fp);

    return (0);
}

