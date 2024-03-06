#include "simulator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

void run(Cache *cache, int output_flag, char *file_path)
{
  int n_access = 0;
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

  uint32_t addr_buffer;

  while (fread(&addr_buffer, 4, 1, fp) > 0)
  {
    n_access++;
    // has to check if validation bit is unset inside function
    bool is_hit = request_address(cache, ntohl(addr_buffer), &compulsory_misses, &conflict_misses);

    printf("\n");
    if (is_hit)
    {
      hits++;
    }
    else
    {
      misses++;
    }
  }

  fclose(fp);

  if (output_flag)
  {
    printf("%d, %.4f, %.4f, %.2f, %.2f, %.2f",
           n_access,
           (float)hits / (float)n_access,
           (float)misses / (float)n_access,
           (float)compulsory_misses / (float)misses,
           (float)(misses - compulsory_misses - conflict_misses) / (float)misses,
           (float)conflict_misses / (float)misses);
  }
  else
  {
    printf("Misses compulsorios: %d\nMisses de conflito: %d\nMisses de capacidade %d\nHits: %d\n", compulsory_misses, conflict_misses, misses - compulsory_misses - conflict_misses, hits);
  }
}
