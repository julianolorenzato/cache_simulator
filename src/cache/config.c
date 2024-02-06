#include "config.h"
#include <stdlib.h>
#include <stdio.h>

Config *parse_arguments(int argc, char *argv[])
{
    if (argc != 7)
    {
        fprintf(stderr, "Incorrect number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Config *config = (Config *)malloc(sizeof(Config));

    config->nsets = atoi(argv[1]);
    config->bsize = atoi(argv[2]);
    config->assoc = atoi(argv[3]);
    config->r_policy = argv[4][0];
    config->o_flag = atoi(argv[5]);

    if (config->nsets <= 0)
    {
        fprintf(stderr, "Invalid set number.\n");
        exit(EXIT_FAILURE);
    }

    if (config->bsize <= 0)
    {
        fprintf(stderr, "Invalid block number.\n");
        exit(EXIT_FAILURE);
    }
    
    if (config->assoc < 0 || config->assoc > config->nsets)
    {
        fprintf(stderr, "Invalid associativity.\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[4], "L") && strcmp(argv[4], "F") && strcmp(argv[4], "R"))
    {
        fprintf(stderr, "You must choose 'L', 'F' or 'R' to replacement policy.\n");
        exit(EXIT_FAILURE);
    }

    if (config->o_flag != 0 && config->o_flag != 1)
    {
        fprintf(stderr, "Invalid output flag; must be either 1 or 0. \n");
        exit(EXIT_FAILURE); 
    }

    return config;
}