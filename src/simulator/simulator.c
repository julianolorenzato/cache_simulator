#include "simulator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void run(Cache *cache, char *file_path)
{
  uint32_t capacity_misses = 0;
  uint32_t conflict_misses = 0; // figure out what to do with these
  uint32_t compulsory_misses = 0;
  uint32_t misses = 0;
  uint32_t hits = 0;

  FILE *fp = fopen(file_path, "rb");
  if (fp == NULL)
  {
    fprintf(stderr, "Error opening file");
    exit(EXIT_FAILURE);
  }

  int addr_buffer;

  while (fread(&addr_buffer, 4, 1, fp) > 0)
  {
    printf("%x\n", addr_buffer);
    // has to check if validation bit is unset inside function
    bool is_hit = request_address(cache, addr_buffer, &compulsory_misses, &conflict_misses);

    if (is_hit)
    {
      hits++;
    }
    else
    {
      misses++;

      if (cache->empty_blocks == 0)
      {
        capacity_misses++;
      }
      else
      {
        cache->empty_blocks--;
      }
    }
  }

  fclose(fp);
}
