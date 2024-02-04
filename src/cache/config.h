#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    unsigned int nsets;
    unsigned int bsize;
    unsigned int assoc;
    char r_policy;
} Config;

Config *parse_arguments(char *argv[]);

#endif // CONFIG_H