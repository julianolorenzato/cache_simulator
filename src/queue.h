#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

typedef struct node {
  struct node *next;
  uint32_t value;
} Node;

typedef struct {
  Node *start;
  Node *end;
} Queue;

Node* new_node(uint32_t value);

Queue *new_q();

void enqueue(Queue *q, uint32_t address);

uint32_t dequeue(Queue *q);

void refresh(Queue *q, uint32_t address);

#endif // QUEUE_H
