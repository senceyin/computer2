#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "forkit.h"

int main(int argc, char *argv[])
{
    int len = 0;
    char **data = NULL;
    read_file("ftest1.txt", &data, &len);

    // for (int i = 0; i < len; i++)
    // {
    //     printf("%s\n", data_ptr[i]);
    // }

    create_processes(2, data, len);

    return 0;
}
