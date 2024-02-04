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

__uint8_t *allocate_cache_mem(Config *config)
{
    __u_int index_length = log2l(config->nsets);
    __u_int offset_length = log2l(config->bsize);
    __u_int tag_size = ADDRESS_LENGTH - index_length - offset_length;

    __u_int lines = config->nsets * config->assoc;
    __u_int line_bytes = 1 + tag_size + config->bsize;

    __uint8_t *memory = (__uint8_t *)calloc(lines, line_bytes);

    return memory;
}