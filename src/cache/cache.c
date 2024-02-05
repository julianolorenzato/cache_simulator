#include "cache.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

Cache *new_cache(Config *config)
{
    Cache *cache = (Cache *)malloc(sizeof(Cache));

    cache->memory = allocate_cache_mem(config);

    return cache;
}

uint8_t *allocate_cache_mem(Config *config)
{
    uint32_t index_length = log2l(config->nsets);
    uint32_t offset_length = log2l(config->bsize);
    uint32_t tag_size = ADDRESS_LENGTH - index_length - offset_length;

    uint32_t lines = config->nsets * config->assoc;
    uint32_t line_bytes = 1 + tag_size + config->bsize;

    uint8_t *memory = (uint8_t *)calloc(lines, line_bytes);

    return memory;
}

void request_address(Cache *cache, __uint32_t address)
{
    uint8_t start = cache->memory + 
}