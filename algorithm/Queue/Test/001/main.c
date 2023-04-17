
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
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 

#define FUNC_BAR "=================================="
#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
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
typedef int queueData; 
#define QUEUECAPACITYBASE 2
struct queue {
	queueData *data; 
	int capacity; 
	int size; 
}; 

queue *new(void){
	queue *q=malloc(sizeof(*q)); 
	if(q){
		q->capacity=QUEUECAPACITYBASE; 
		q->size=0; 
		q->data=malloc(sizeof(queueData)*q->capacity); 
	}
	return q; 
}

queue *add(queue *q, queueData val){
	if(q){
		if(q->size<q->capacity){
			if(q->data){
				q->data[q->size]=val; 
				q->size++; 
			}
		}else{
			queueData *dataBkp=q->data; 
			if((q->data=realloc(q->data, sizeof(queueData)*q->capacity*2))!=NULL){
				q->capacity*=2; 
				printf("enlarge capacity(%d)\n", q->capacity); 
				add(q, val); 
			}else{
				q->data=dataBkp; 
			}
		}
	}
	return q; 
}

queue *delete(queue *q){
	if(q){
		if(q->size){
			q->size--;
		}
	}
	return q; 
}

void destroy(queue *q){
	if(q){
		if(q->data) free(q->data); 
		free(q); 
	}
}

queue *dump(queue *q){
	if(q){
		printf("q(%d): ", q->size); 
		for(int i=0; i<q->size; i++){
			printf("(%d)%s", q->data[i], i!=q->size-1?"->":""); 
		}
		printf("\n"); 
	}
	return q; 
}

void test001(void){
	queue *q=new(); 
	if(q){
		dump(add(q, 5)); 
		dump(add(add(q, 9), 7)); 
		dump(delete(q)); 
		dump(delete(delete(q))); 
		destroy(q); 
	}
}

int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

