#include "arg_parser.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void parse(char const *argv[], int *nsets, int *bsize, int *assoc, char *r_policy, bool output_flag)
{
    *nsets = atoi(argv[1]);
    *bsize = atoi(argv[2]);
    *assoc = atoi(argv[3]);
    if (strcmp(argv[4], "l") || strcmp(argv[4], "f") || strcmp(argv[4], "r"))
    {
        *r_policy = (char)argv[4];
    }
    else
    {
        printf("You must choose 'l', 'f' or 'r' to replacement policy.\n");
        exit(0);
    }
}