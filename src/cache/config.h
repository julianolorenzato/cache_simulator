#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    unsigned int nsets;
    unsigned int bsize;
    unsigned int assoc;
    char r_policy;
    int o_flag;
    
} Config;

Config *parse_arguments(int argc, char *argv[]);

#endif // CONFIG_H