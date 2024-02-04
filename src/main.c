#include <stdio.h>
#include <stdbool.h>
#include "cache/config.h"

int main(int argc, char const *argv[])
{

    Config *config = parse_arguments(argv);

    printf("%d %d %d %c\n\n", config->nsets, config->bsize, config->assoc, config->r_policy);

    return 0;
}
