#ifndef CACHE_H
#define CACHE_H

#include "config.h"
#include <stdbool.h>
#include <stdint.h>

#define ADDRESS_LENGTH 32

typedef struct
{
    char r_policy;
    uint8_t *memory;
} Cache;

Cache *new_cache(Config *config);

uint8_t *allocate_cache_mem(Config *config);

void request_address(Cache *cache, uint32_t address);

#endif // CACHE_H