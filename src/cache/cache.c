#include "cache.h"
#include <math.h>

Cache *new_cache(Config *config)
{
    unsigned int index_length = log2l(config->nsets);
    unsigned int offset_length = log2l(config->bsize);
    unsigned int tag_size = ADDRESS_LENGTH - index_length - offset_length;

    // Alocate a space in memory for a block
    Block *block = (Block *)malloc(sizeof(Byte) * config->bsize);

    // Fill all block bytes with zero
    for (int i = 0; i < config->bsize; i++)
    {
        block[i] = 0b00000000;
    }

    // Alocate a space in memory for a tag
    Tag *tag = (Tag *)malloc(sizeof(Byte) * tag_size);

    // Fill all tag bytes with zero
    for (int i = 0; i < tag_size; i++)
    {
        tag[i] = 0b00000000;
    }
    
}