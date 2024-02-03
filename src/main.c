#include <stdio.h>
#include <stdbool.h>
#include "arg_parser/arg_parser.h"

int main(int argc, char const *argv[])
{
    int nsets, bsize, assoc;
    char r_policy;
    bool output_flag;

    parse(argv, &nsets, &bsize, &assoc, &r_policy, &output_flag);

    printf("%d %d %d %c %d\n\n", nsets, bsize, assoc, r_policy, output_flag);

    return 0;
}
