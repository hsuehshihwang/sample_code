
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

typedef struct stack stack; 
typedef int stackData; 
#define STACKCAPACITYBASE 2
struct stack {
	stackData *data; 
	int capacity; 
	int size; 
	int top; 
}; 

stack *new(void){
	stack *s=malloc(sizeof(*s)); 
	if(s){
		s->capacity=STACKCAPACITYBASE; 
		s->size=0; 
		s->top=0; 
		s->data=malloc(sizeof(stackData)*s->capacity); 
	}
	return s; 
}

stack *push(stack *s, stackData val){
	if(s){
		if((s->top+s->size)<s->capacity){
			if(s->data){
				s->data[s->size]=val; 
				s->size++; 
			}
		}else{
			if(s->top>0){
				for(int i=s->top, j=0; i<(s->top+s->size); i++){
					s->data[j]=s->data[i]; 
					j++; 
				}
				push(s, val); 
			}else{
				stackData *dataBkp=s->data; 
				if((s->data=realloc(s->data, sizeof(stackData)*s->capacity*2))!=NULL){
					s->capacity*=2; 
					push(s, val); 
				}else{
					s->data=dataBkp; 
				}
			}
		}
	}
	return s; 
}

stack *pop(stack *s){
	if(s){
		if(s->size){
			s->top++; 
			s->size--;
		}
	}
	return s; 
}

void destroy(stack *s){
	if(s){
		if(s->data) free(s->data); 
		free(s); 
	}
}

stack *dump(stack *s){
	if(s){
		printf("s(%d): ", s->size); 
		for(int i=0; i<s->size; i++){
			printf("(%d)%s", s->data[s->top+i], i!=s->size-1?"->":""); 
		}
		printf("\n"); 
	}
	return s; 
}

void test001(void){
	stack *s=new(); 
	if(s){
		dump(push(s, 5)); 
		dump(push(push(s, 9), 7)); 
		dump(pop(s)); 
		destroy(s); 
	}
}

int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

