#ifndef CACHE_H
#define CACHE_H

#include "config.h"
#include <stdbool.h>

#define ADDRESS_LENGTH 32

typedef signed char Byte;

typedef Byte *Block;

typedef Byte *Tag;

typedef struct
{
    bool validation;
    Tag tag;
    Block block;
} Line;

typedef Line *Set;

typedef struct
{
    char r_policy;
    Set *sets;
} Cache;

Cache *new_cache(Config *config);

#endif // CACHE_H