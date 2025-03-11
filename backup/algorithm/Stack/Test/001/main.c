
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

typedef struct node node; 
typedef struct stack stack; 
struct node {
	int val; 
	node *next; 
}; 
struct stack {
	node *top; 
	int count; 
}; 
stack *new(void){
	stack *s=malloc(sizeof(*s)); 
	if(s){
		s->count=0; 
		s->top=NULL; 
	}
	return s; 
}
stack *push(stack *s, int val){
	printf("push(%d)\n", val); 
	if(s){
		node *n=malloc(sizeof(*n)); 
		n->val=val; 
		n->next=s->top; 
		s->top=n; 
		s->count++; 
	}
	return s; 
}
stack *pushByArray(stack *s, int *a, int n){
	for(int i=0; i<n; i++){
		push(s, a[i]); 
	}
	return s; 
}
stack *pop(stack *s){
	printf("pop()\n"); 
	if(s){
		if(s->top){
			node *n=s->top; 
			s->top=s->top->next; 
			free(n); 
			s->count--; 
		}
	}
	return s; 
}
stack *popWithTimes(stack *s, int n){
	if(s){
		for(int i=0; i<n; i++) pop(s); 
	}
	return s; 
}
stack *dump(stack *s){
	if(s){
		printf("stack(%d): ", s->count); 
		for(node *n=s->top; n; n=n->next){
			printf("(%d)%s", n->val, n->next?"->":""); 
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
		dump(pop(s)); 
		dump(pushByArray(s, (int[]){9, 7, 3, 2, 1}, 5)); 
		dump(popWithTimes(s, 4)); 
	}
}
int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

