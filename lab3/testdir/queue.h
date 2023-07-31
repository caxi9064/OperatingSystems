#ifndef HEADER_FILE
#define HEADER_FILE
#include <pthread.h>

struct element {
    int op_number;
	char type[10];
    int account1;
    int account2;
    int amount;
};

typedef struct queue {
	int head;
    int tail;
    int size;
    int count;
    struct element *elements; // array that holds a element structs 
    pthread_mutex_t lock;
    pthread_cond_t full;
    pthread_cond_t empty;
}queue;

queue* queue_init (int size);
int queue_destroy (queue *q);
int queue_put (queue *q, struct element* ele);
struct element * queue_get(queue *q);
int queue_empty (queue *q);
int queue_full(queue *q);

#endif
