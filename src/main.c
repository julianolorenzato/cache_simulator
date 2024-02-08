#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "cache.h"
#include "simulator.h"

int main(int argc, char const *argv[])
{
    Config *config = parse_arguments(argc, argv);
    Cache *cache = new_cache(config);

    char file_path[40];
    strcpy(file_path, argv[6]);

    run(cache, file_path);

    return 0;
}
