#ifndef __queue_h__
#define __queue_h__

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
typedef struct queue queue; 
typedef int queueData; 
struct queue {
	queueData *data; 
	int top; 
	int size; 
	int capacity; 
}; 
queue *newQueue(int capacity);
queue *pushQueue(queue *q, queueData val);
queue *popQueue(queue *q);
queue *dumpQueue(queue *q);
queueData *headQueue(queue *q);
queueData *peekQueue(queue *q, int i);
queueData *tailQueue(queue *q);
void destroyQueue(queue *q);
void queueTest(void); 

#endif /*__queue_h__*/

