#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdio.h>

struct queue { int value; struct queue* next; };

int enqueue(struct queue** queue_addr, struct queue* customer);
int dequeue(struct queue** queue_addr);
int free_mqueue(struct queue** memory_queue_addr);
int menqueue(struct queue** queue_addr, int value, struct queue** memory_queue_addr);
int mdequeue(struct queue** queue_addr, struct queue** memory_queue_addr);

#endif