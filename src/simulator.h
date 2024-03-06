#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "cache.h"

void run(Cache *cache, int output_flag, char *file_path);

void read_address(char *file_path);

#endif // SIMULATOR_H