#ifndef FORKIT_H
#define FORKIT_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void read_file(const char* filename, char*** data, int* len);

void create_processes(int n, char** data, int len);

#endif

