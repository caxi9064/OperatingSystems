//OS-P3 2022-2023

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "queue.h"
#include <pthread.h> // to allow for waiting for elements to be added or removed from the queue

//To create a queue
queue* queue_init(int size){
	queue * q = (queue *)malloc(sizeof(queue));
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->size = size;
    q->elements = (struct element*)malloc(size * sizeof(struct element));
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->full, NULL);
    pthread_cond_init(&q->empty, NULL);
    return q;
}

// To Enqueue an element
int queue_put(queue *q, struct element * ele) {
	pthread_mutex_lock(&q->lock); // Acquire the queue lock before performing any operations
    while (q->count == q->size) { // Wait until the queue has available space
        pthread_cond_wait(&q->full, &q->lock);
    }
    q->elements[q->tail] = *ele; // Add the element to the tail of the queue, *ele dereferences pointer ele allowing access to structure element object
    q->tail = (q->tail + 1) % q->size; // // Move the tail pointer to the next available position
    q->count++; // Increment the number of elements in the queue
    pthread_cond_signal(&q->empty); // Signal the condition variable to notify waiting threads that the queue is no longer empty
    pthread_mutex_unlock(&q->lock); // Release the lock to allow other threads to access the queue
    return 0;
}

// To Dequeue an element.
struct element* queue_get(queue *q) {
	pthread_mutex_lock(&q->lock);
    while (q->count == 0) { // wait for queue to be non-empty
        pthread_cond_wait(&q->empty, &q->lock);
    }
    struct element* element = &(q->elements[q->head]); // extract element from head of queue
    q->head = (q->head + 1) % q->size;
    q->count--;
    pthread_cond_signal(&q->full);
    pthread_mutex_unlock(&q->lock);
	
	return element;
}

//To check queue state
int queue_empty(queue *q){
	pthread_mutex_lock(&q->lock); // ensure that multiple threads do not access queue at the same time
    int empty = q->count == 0;
    pthread_mutex_unlock(&q->lock);
    return empty;

	/*if (q->front == q->rear) {
        return 1;
    }
    return 0;*/
}

int queue_full(queue *q){
	pthread_mutex_lock(&q->lock); // ensure that multiple threads do not access queue at the same time
    int full = q->count == q->size;
    pthread_mutex_unlock(&q->lock);
    return full;

	/*if ((q->rear + 1) % q->size == q->front) {
        return 1;
    }
    return 0;*/
}

//To destroy the queue and free the resources
int queue_destroy(queue *q){
	free(q->elements);
    pthread_mutex_destroy(&q->lock);
    pthread_cond_destroy(&q->full);
    pthread_cond_destroy(&q->empty);
    free(q);
    return 0;
}
