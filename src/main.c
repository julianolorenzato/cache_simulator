#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "cache/cache.h"
#include "simulator/simulator.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    Config *config = parse_arguments(argc, argv);
    Cache *cache = new_cache(config);

    char file_path[40];
    strcpy(file_path, argv[6]);

    run(cache, cache->config.o_flag, file_path);

    return 0;
}
