#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Node *new_node(uint32_t value)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->value = value;
  node->next = NULL;
  return node;
}

Queue *new_q()
{
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->start = NULL;
  q->end = NULL;
  return q;
}

void enqueue(Queue *q, uint32_t line_i)
{
  Node *node = new_node(line_i);
  if (q->start == NULL || q->end == NULL)
  {
    q->start = node;
    q->end = node;
  }
  else
  {
    Node *curr = q->end;
    while (curr != NULL)
    {
      curr = curr->next;
    }

    node->next = q->end;
    q->end = node;
  }
}

uint32_t dequeue(Queue *q)
{
  if (q->end == NULL)
  {
    return -1;
  }

  if (q->end->next == NULL)
  {
    free(q->end);
    q->end = NULL;
    q->start = NULL;
  }

  Node *curr = q->end;

  while (curr->next != q->start)
  {
    curr = curr->next;
  }

  uint32_t line_i = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  q->start = curr;
  return line_i;
}

void refresh(Queue *q, uint32_t line_i)
{
  if (q->end->value == line_i)
  {
    return;
  }

  Node *curr = q->end;

  while (curr->next->value != line_i)
  {
    curr = curr->next;
  }

  Node *l_i = curr->next;

  curr->next = curr->next->next;

  l_i->next = q->end;
  q->end = l_i;
}