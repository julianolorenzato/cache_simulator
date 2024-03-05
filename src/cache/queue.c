#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

Node *new_node(uint32_t value) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->value = value;
  node->next = NULL;
  return node;
}

Queue *new_q() {
  Queue *q = (Queue *)malloc(sizeof(Queue));
  q->start = NULL;
  q->end = NULL;
  return q;
}

void enqueue(Queue *q, uint32_t address) {
  Node *node = new_node(address);
  if (q->start == NULL || q->end == NULL) {
    q->start = node;
    q->end = node;
  } else {
    node->next = q->end;
    q->end = node;
  }
}

uint32_t dequeue(Queue *q) {
  if (q->end == NULL) {
    return -1;
  }

  if (q->end->next == NULL) {
    free(q->end);
    q->end = NULL;
    q->start = NULL;
  }

  Node *curr = q->end;

  while (curr->next != q->start) {
    curr = curr->next;
  }

  uint32_t address = curr->value;
  free(curr->next);
  curr->next = NULL;
  q->start = curr;
  return address;
}

void refresh(Queue *q, uint32_t address) {
  if (q->end->value == address) {
    return;
  }

  Node *curr = q->end;

  while (curr->next->value != address) {
    curr = curr->next;
  }
  Node *refreshed = curr->next;
  curr->next = curr->next->next;

  refreshed->next = q->end;
  q->end = refreshed;
}

int main() {
  Queue *q = new_q();

  enqueue(q, 1245);
  enqueue(q, 246);
  enqueue(q, 2665);
  enqueue(q, 534);
  dequeue(q);
  refresh(q, 2665);
  dequeue(q);
  dequeue(q);

  printf("%d %d", q->start->value, q->end->value);
}
