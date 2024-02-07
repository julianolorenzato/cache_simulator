#include "cache.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

Config *parse_arguments(char *argv[])
{
    Config *config = (Config *)malloc(sizeof(Config));

    config->nsets = atoi(argv[1]);
    config->bsize = atoi(argv[2]);
    config->assoc = atoi(argv[3]);

    if (strcmp(argv[4], "l") && strcmp(argv[4], "f") && strcmp(argv[4], "r"))
    {
        fprintf(stderr, "You must choose 'l', 'f' or 'r' to replacement policy.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        config->r_policy = argv[4][0];
    }

    return config;
}

Cache *new_cache(Config *config)
{
    Cache *cache = (Cache *)malloc(sizeof(Cache));

    uint32_t index_bits = log2l(config->nsets);
    uint32_t offset_bits = log2l(config->bsize);
    uint32_t tag_bits = ADDRESS_BITS - index_bits - offset_bits;

    cache->address_format.index_bits = index_bits;
    cache->address_format.offset_bits = offset_bits;
    cache->address_format.tag_bits = tag_bits;

    cache->config = *config;
    cache->memory = allocate_cache_mem(cache);

    return cache;
}

uint32_t bits_to_bytes(uint32_t bits)
{
    if (bits % 8 == 0)
    {
        return bits / 8;
    }
    else
    {
        return (bits / 8) + 1;
    }
}

uint8_t *allocate_cache_mem(Cache *cache)
{
    uint32_t lines = cache->config.nsets * cache->config.assoc;
    uint32_t line_bytes = 1 + bits_to_bytes(cache->address_format.tag_bits) + cache->config.bsize;

    uint8_t *memory = (uint8_t *)calloc(lines, line_bytes);

    return memory;
}

uint32_t extract_bits(uint32_t value, uint32_t skip, uint32_t take)
{
    uint32_t mask = ((1 << take) - 1) << skip;
    return (mask & value) >> skip;
}

uint32_t *decode_address(uint32_t address, AddressFormat format)
{
    uint32_t *data = (uint32_t *)malloc(sizeof(uint32_t) * 3);

    
}

bool request_address(Cache *cache, uint32_t address)
{
    uint32_t index_bits = cache->address_format.index_bits;
    uint32_t tag_bits = cache->address_format.tag_bits;
    uint32_t offset_bits = cache->address_format.offset_bits;

    uint32_t address_tag = (address << index_bits) >> index_bits + offset_bits;

    uint32_t cache_index = address % cache->config.nsets;

    uint8_t set_start = cache->memory + cache_index;

    bool validation_bit = set_start;
    uint32_t tag = set_start + 1;
    uint32_t block = set_start + 1 + tag_bits;

    for (int i = 0; i < cache->config.assoc; i++)
    {
    }

    if (validation_bit && tag == address_tag)
    {
        return true;
    }
    else
    {
        return false;
    }
}