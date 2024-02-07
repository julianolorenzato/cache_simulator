#include "cache.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

Config *parse_arguments(int argc, char *argv[])
{
    if (argc != 7)
    {
        fprintf(stderr, "Incorrect number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Config *config = (Config *)malloc(sizeof(Config));

    config->nsets = atoi(argv[1]);
    config->bsize = atoi(argv[2]);
    config->assoc = atoi(argv[3]);
    config->r_policy = argv[4][0];
    config->o_flag = atoi(argv[5]);

    if (config->nsets <= 0)
    {
        fprintf(stderr, "Invalid set number.\n");
        exit(EXIT_FAILURE);
    }

    if (config->bsize <= 0)
    {
        fprintf(stderr, "Invalid block number.\n");
        exit(EXIT_FAILURE);
    }

    if (config->assoc < 0 || config->assoc > config->nsets)
    {
        fprintf(stderr, "Invalid associativity.\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[4], "L") && strcmp(argv[4], "F") && strcmp(argv[4], "R"))
    {
        fprintf(stderr, "You must choose 'L', 'F' or 'R' to replacement policy.\n");
        exit(EXIT_FAILURE);
    }

    if (config->o_flag != 0 && config->o_flag != 1)
    {
        fprintf(stderr, "Invalid output flag; must be either 1 or 0. \n");
        exit(EXIT_FAILURE);
    }

    return config;
}

Cache *new_cache(Config *config)
{
    Cache *cache = (Cache *)malloc(sizeof(Cache));

    uint32_t index_bits = calculate_bits_needed(config->nsets);
    uint32_t offset_bits = calculate_bits_needed(config->bsize);
    uint32_t tag_bits = ADDRESS_BITS - index_bits - offset_bits;

    AddressFormat addr_format = {
        .index_bits = index_bits,
        .tag_bits = tag_bits,
        .offset_bits = offset_bits,
    };

    cache->address_format = addr_format;
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

// Skip x bits from right to left and then take y bits from right to left
uint32_t extract_bits(uint32_t value, uint32_t skip, uint32_t take)
{
    uint32_t mask = ((1 << take) - 1) << skip;
    return (mask & value) >> skip;
}

// Return the bits of index, tag and offset from the address
AddressData decode_address(uint32_t address, AddressFormat format)
{
    uint32_t *data = (uint32_t *)malloc(sizeof(uint32_t) * 3);

    AddressData addr_data = {
        .index_data = extract_bits(address, format.tag_bits + format.offset_bits, format.index_bits),
        .tag_data = extract_bits(address, format.offset_bits, format.tag_bits),
        .offset_data = extract_bits(address, 0, format.offset_bits),
    };

    return addr_data;
}

// Evaluate if an address is a hit or miss in the cache memory
bool request_address(Cache *cache, uint32_t address)
{
    AddressData addr_data = decode_address(address, cache->address_format);

    uint32_t cache_index = address % cache->config.nsets;

    uint8_t *memory_ptr = cache->memory + cache_index;

    // Iterate all lines in the set (in case of not direct mapping)
    for (int i = 0; i < cache->config.assoc; i++)
    {
        uint8_t validation_bit;
        memcpy(&validation_bit, memory_ptr, 1);
        memory_ptr += 1;

        uint32_t tag;
        memcpy(&tag, memory_ptr, bits_to_bytes(cache->address_format.tag_bits));
        memory_ptr += bits_to_bytes(cache->address_format.tag_bits);

        // uint32_t block;
        // memcpy(&block, memory_ptr, cache->config.bsize);
        // skip block
        memory_ptr += cache->config.bsize;

        if (validation_bit && tag == addr_data.tag_data)
        {
            return true;
        }
    }

    // Adicionar o endereço à cache aqui

    return false;
}

// Calculate bits needed to representate n values
int calculate_bits_needed(int stored)
{
    double bits_needed = 0;

    while (pow((double)2, bits_needed) < stored)
    {
        bits_needed++;
    }

    return (uint32_t)bits_needed;
}