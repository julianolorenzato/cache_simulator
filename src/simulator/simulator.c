#include "simulator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void run(Cache *cache, int output_flag, char *file_path)
{
  int n_access = 0;
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
    n_access++;
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

  if (output_flag)
  {
    printf("%d, %.4f, %.4f, %.2f, %.2f, %.2f",
           n_access,
           (float)hits / (float)n_access,
           (float)(capacity_misses + conflict_misses + compulsory_misses) / (float)n_access,
           (float)compulsory_misses / (float)n_access,
           (float)capacity_misses / (float)n_access,
           (float)conflict_misses / (float)n_access);
  }
  else
  {
    printf("compulsorio: %d, conflito: %d, capacidade %d, hits: %d", compulsory_misses, conflict_misses, capacity_misses, hits);
  }
}
