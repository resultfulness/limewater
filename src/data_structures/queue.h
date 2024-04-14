#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>
#include <stdio.h>

struct queue { int value; struct queue* next; };

/**
 * @brief adds whole queue node to the end of queue
 * 
 * @param queue_addr address to queue to which a customer will be added
 *                   (address to handle null queue)
 * @param customer   pointer to a queue structure which will be added to
 *                   to queue on queue_addr   
 * @return 1 if provided with corrupted data, 0 if operation was successful
 */
int enqueue(struct queue** queue_addr, struct queue* customer);

/**
 * @brief removes front customer from queue
 * 
 * @param queue_addr address to queue from which the first customer will be removed
 *                   (address to handle nullifying queue)
 * @return -1 if provided with corrupted data or empty queue, first customer's value otherwise
 */
int dequeue(struct queue** queue_addr);

/**
 * @brief frees memory allocated for queue
 * 
 * @param memory_queue_addr address to queue which memory will be freed
 *                          (address to handle nullifying queue)
 * @return -1 if provided with corrupted data or empty queue, 0 otherwise
 */
int free_mqueue(struct queue** memory_queue_addr);

/**
 * @brief adds new customer to queue, using memory queue as a buffer so that
 *        it only allocates new memory if memory queue is empty
 * 
 * @param queue_addr address to queue to which a customer will be added
 *                   (address to handle null queue)
 * @param value      value of new customer
 * @param memory_queue_addr address to queue which will be used as a memory buffer
 *                          (address to handle nullifying queue)
 * @return 0 if ok, 1 if provided with corrupted data or memory can't be allocated
 */
int menqueue(struct queue** queue_addr, int value, struct queue** memory_queue_addr);
/**
 * @brief removes the first customer from queue
 * 
 * @param queue_addr address to queue from which a customer will be removed
 *                   (address to handle nullifying queue)
 * @param memory_queue_addr address to queue used as a memory buffer, to which
 *                          a queue struct that is removed will be added to save
 *                          memory
 *                          (address to handle null queue)
 * 
 * @return -1 if provided with corrupted data or empty queue, first customer's value otherwise
 */
int mdequeue(struct queue** queue_addr, struct queue** memory_queue_addr);

#endif