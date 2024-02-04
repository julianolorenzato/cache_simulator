#ifndef CACHE_H
#define CACHE_H

#include "config.h"
#include <stdbool.h>
#include <stdint.h>

#define ADDRESS_LENGTH 32

typedef struct
{
    char r_policy;
    __uint8_t *memory;
} Cache;

Cache *new_cache(Config *config);

__uint8_t *allocate_cache_mem(Config *config);

#endif // CACHE_H