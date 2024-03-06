#include <stdio.h>
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

    argc = 7; //
    Config *config = parse_arguments(argc, fake_args_ptr);
    Cache *cache = new_cache(config);
    

    char file_path[40] = {"bin_100.bin"};
    //strcpy(file_path, fake_args_ptr[6]);

    run(cache, cache->config.o_flag, file_path);

    return 0;
}
