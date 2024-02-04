#include "config.h"
#include <stdlib.h>
#include <stdio.h>

Config *parse_arguments(char *argv[])
{
    Config *config = (Config *)malloc(sizeof(Config));

    config->nsets = atoi(argv[1]);
    config->bsize = atoi(argv[2]);
    config->assoc = atoi(argv[3]);

    if (strcmp(argv[4], "l") && strcmp(argv[4], "f") && strcmp(argv[4], "r"))
    {
        fprintf(stderr, "You must choose 'l', 'f' or 'r' to replacement policy.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        config->r_policy = argv[4][0];
    }

    return config;
}