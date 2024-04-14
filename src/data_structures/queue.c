#include "queue.h"

int enqueue(struct queue** queue_addr, struct queue* customer) {
    if(queue_addr == NULL || customer == NULL)
        return 1;
    customer->next = NULL;
    if(*queue_addr == NULL) {
        *queue_addr = customer;
        return 0;
    }
    
    struct queue* queue = *queue_addr;

    while(queue->next != NULL)
        queue = queue->next;

    queue->next = customer;

    return 0;
}

int dequeue(struct queue** queue_addr) {
    if(queue_addr == NULL || *queue_addr == NULL)
        return -1;
    
    struct queue* queue = *queue_addr;
    int front_customer = queue->value;

    struct queue* queue_copy = queue;
    queue = queue->next;

    *queue_addr = queue;
    return front_customer;
}

int free_mqueue(struct queue** memory_queue_addr) {
    if(memory_queue_addr == NULL || *memory_queue_addr == NULL)
        return -1;
    
    struct queue* memory_queue = *memory_queue_addr;

    struct queue* queue_copy = memory_queue;
    memory_queue = memory_queue->next;
    free(queue_copy);

    *memory_queue_addr = memory_queue;
    return 0;
}

int menqueue(struct queue** queue_addr, int value, struct queue** memory_queue_addr) {
    if(queue_addr == NULL || memory_queue_addr == NULL)
        return 1;
    
    struct queue* memory_queue = *memory_queue_addr;
    struct queue* queue = *queue_addr;
    if(queue == NULL) {
        if(memory_queue != NULL) {
            queue = memory_queue;
            dequeue(memory_queue_addr);
        }
        else
            queue = malloc(sizeof(struct queue));
        if(queue == NULL)
            return 1;
        queue->value = value;
        queue->next = NULL;
        *queue_addr = queue;
        return 0;
    }

    struct queue* customer;
    if(memory_queue != NULL) {
        customer = memory_queue;
        dequeue(memory_queue_addr);
    }
    else
        customer = malloc(sizeof(struct queue));
    if(customer == NULL)
        return 1;
    
    while(queue->next != NULL)
        queue = queue->next;
    customer->value = value;
    customer->next = NULL;
    queue->next = customer;

    return 0;
}

int mdequeue(struct queue** queue_addr, struct queue** memory_queue_addr) {
    if(queue_addr == NULL || *queue_addr == NULL || memory_queue_addr == NULL)
        return -1;
    
    struct queue* queue = *queue_addr;
    int front_customer = queue->value;

    struct queue* queue_copy = queue;
    queue = queue->next;
    enqueue(memory_queue_addr, queue_copy);

    *queue_addr = queue;
    return front_customer;
}