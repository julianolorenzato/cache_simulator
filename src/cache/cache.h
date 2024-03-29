#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>
#include <stdint.h>

#define ADDRESS_BITS 32

typedef struct
{
    uint32_t nsets;
    uint32_t bsize;
    uint32_t assoc;
    char r_policy;
    int o_flag;
} Config;

typedef struct
{
    uint32_t index_bits;
    uint32_t tag_bits;
    uint32_t offset_bits;
} AddressFormat;

typedef struct
{
    uint32_t index_data;
    uint32_t tag_data;
    uint32_t offset_data;
} AddressData;

typedef struct
{
    Config config;
    AddressFormat address_format;
    uint8_t *memory;
    uint32_t empty_blocks;
} Cache;

Cache *new_cache(Config *config);

uint8_t *allocate_cache_mem(Cache *cache);

bool request_address(Cache *cache, uint32_t address, uint32_t *compulsory_misses, uint32_t *conflict_misses);

Config *parse_arguments(int argc, const char *argv[]);

int calculate_bits_needed(int stored);

#endif // CACHE_H