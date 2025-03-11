#include "queue.h"
queue *newQueue(int capacity){
	queue *q=malloc(sizeof(queue)); 
	if(q){
		q->top=0; 
		q->size=0; 
		q->capacity=capacity; 
		q->data=malloc(sizeof(queueData)*q->capacity); 
	}
	return q; 
}
queueData *searchQueue(queue *q, queueData val){
	for(int i=0; i<q->size; i++){
		if(q->data[q->top+i]==val){
			return &(q->data[q->top+i]); 
		}
	}
	return NULL; 
}
queue *pushQueue(queue *q, queueData val){
	if(q){
		if((q->top+q->size)<q->capacity){
			if(q->top>0){
				for(int i=0; i<q->size; i++){
					q->data[i]=q->data[q->top+i]; 
				}
				pushQueue(q, val); 
			}else{
				queueData *tmp=q->data; 
				if((q->data=realloc(q->data, sizeof(queueData)*q->capacity*2))!=NULL){
					q->capacity*=2; 
					pushQueue(q, val); 
				}else{
					q->data=tmp; 
				}
			}
		}else{
			if(!searchQueue(q, val)){
				q->data[q->top+q->size]=val; 
				q->size++; 
			}
		}
	}
	return q; 
}
queue *popQueue(queue *q){
	if(q){
		if(q->size>0){
			q->top++; 
			q->size--; 
		}
	}
	return q; 
}
queue *dumpQueue(queue *q){
	if(q){
		printf("q(%d): ", q->size); 
		for(int i=0; i<q->size; i++){
			printf("(%d)%s", q->data[q->top+i], i!=q->size-1?"->":""); 
		}
		printf("\n"); 
	}
	return q; 
}
queueData *headQueue(queue *q){
	if(q){
		if(q->size){
			return &(q->data[q->top]); 
		}
	}
	return NULL; 
}
queueData *peekQueue(queue *q, int i){
	if(q){
		if(i<q->size){
			return &(q->data[q->top+i]); 
		}
	}
	return NULL; 
}
queueData *tailQueue(queue *q){
	if(q){
		if(q->size){
			return &(q->data[q->top+q->size-1]); 
		}
	}
	return NULL; 
}
void destroyQueue(queue *q){
	if(q){
		if(q->data) free(q->data); 
		free(q); 
	}
}
void queueTest(void){
	FUNC_TITLE; 
	queue *q=newQueue(2); 
	pushQueue(q, 5); 
	pushQueue(q, 9); 
	pushQueue(q, 7); 
	dumpQueue(q); 
	popQueue(q); 
	dumpQueue(q); 
	popQueue(q); 
	popQueue(q); 
	dumpQueue(q); 
	pushQueue(q, 5); 
	pushQueue(q, 9); 
	pushQueue(q, 7); 
	dumpQueue(q); 
	popQueue(q); 
	pushQueue(q, 5); 
	pushQueue(q, 9); 
	pushQueue(q, 7); 
	dumpQueue(q); 
	printf("head(%d)\n", *((queueData *)headQueue(q))); 
	printf("tail(%d)\n", *((queueData *)tailQueue(q))); 
	printf("peek(%d)\n", *((queueData *)peekQueue(q, 1))); 
	while(q->size>0){
		popQueue(q); 
		dumpQueue(q); 
	}
	destroyQueue(q); 
}
