#include "simulator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void run(Cache *cache, char *file_path)
{
    uint32_t misses = 0;
    uint32_t hits = 0;

    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening file");
        exit(EXIT_FAILURE);
    }

    int addr_buffer;

    while (fread(&addr_buffer, 4, 1, fp) > 0)
    {
        printf("%x\n", addr_buffer);
    }

    fclose(fp);
}