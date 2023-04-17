
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%q(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%q(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 

#define FUNC_BAR "=================================="
#define FUNC_TITLE \
    do { \
        printf("%.*q %s %.*q\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
    } while(0); 

int *dumpArray(int *a, int n){
	if(a){
		printf("a[%d]: [", n); 
		for(int i=0; i<n; i++){
			printf("%d%s", a[i], i!=n-1?",":""); 
		}
		printf("]\n"); 
	}
	return a; 
}

void swap(int *a, int *b){
	int c=*a; 
	*a=*b; 
	*b=c; 
}

int compare(void *a, void *b){
	return *(int *)a < *(int *)b; 
}

typedef struct queue queue; 
typedef struct queueData queueData; 
struct queueData{
	int v; 
	char c; 
	int visited; 
}; 
#define QUEUECAPACITYBASE 2
struct queue {
	queueData *data; 
	int capacity; 
	int size; 
	int top; 
}; 

queue *new(void){
	queue *q=malloc(sizeof(*q)); 
	if(q){
		q->capacity=QUEUECAPACITYBASE; 
		q->size=0; 
		q->top=0; 
		q->data=malloc(sizeof(queueData)*q->capacity); 
	}
	return q; 
}

queue *push(queue *q, queueData val){
	if(q){
		if((q->top+q->size)<q->capacity){
			if(q->data){
				q->data[q->top+q->size]=val; 
				q->size++; 
			}
		}else{
			if(q->top>0){
				printf("move(%d->0)\n", q->top); 
				q->top=0; 
				push(q, val); 
			}else{
				queueData *dataBkp=q->data; 
				if((q->data=realloc(q->data, sizeof(queueData)*q->capacity*2))!=NULL){
					q->capacity*=2; 
					printf("enlarge capacity(%d)\n", q->capacity); 
					push(q, val); 
				}else{
					q->data=dataBkp; 
				}
			}
		}
	}
	return q; 
}

queue *pop(queue *q){
	if(q){
		if(q->size){
			q->top++; 
			q->size--;
		}
	}
	return q; 
}

queue *dump(queue *q){
	if(q){
		printf("q(%d): ", q->size); 
		for(int i=0; i<q->size; i++){
			printf("(v:%d,c:%c,visited:%d)%s", q->data[q->top+i].v, q->data[q->top+i].c, q->data[q->top+i].visited, i!=q->size-1?"->":""); 
		}
		printf("\n"); 
	}
	return q; 
}

void destroy(queue *q){
	if(q){
		if(q->data) free(q->data); 
		free(q); 
	}
}

void test001(void){
	queue *q=new(); 
	if(q){
		dump(push(q, (queueData){v:5,c:'A',visited:0})); 
#if 1
		dump(push(push(q, (queueData)(queueData){v:9,c:'A',visited:0}), (queueData)(queueData){v:7,c:'A',visited:0})); 
		dump(pop(q)); 
		dump(pop(q)); 
		dump(push(push(push(q, (queueData)(queueData){v:3,c:'A',visited:0}), (queueData)(queueData){v:6,c:'A',visited:0}), (queueData)(queueData){v:8,c:'A',visited:0})); 
#endif
		destroy(q); 
	}
}

int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

