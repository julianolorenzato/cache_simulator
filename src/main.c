#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "cache.h"
#include "simulator.h"
#include "string.h"

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    char const fakeArgs[7][20] = {"main.exe", "256", "4", "1", "R", "1", "bin_100.bin"};//
    char const* fake_args_ptr[7];

    for(int i = 0; i < 7; i++) {
    fake_args_ptr[i] = fakeArgs[i];
    }

    argc = 7; //
    Config *config = parse_arguments(argc, fake_args_ptr);
    Cache *cache = new_cache(config);
    
    char file_path[] = {"bin_100.bin"}; //useless
    run(cache, cache->config.o_flag, &file_path[0]);

    return 0;
}
