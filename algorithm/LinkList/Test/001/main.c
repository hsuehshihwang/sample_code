
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

typedef struct node node; 
struct node {
	int val; 
	node *next; 
}; 

typedef struct list list; 
struct list {
	node *head; 
	node *tail; 
	int count; 
}; 

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

#if 0
node *new(int val, node *next){
	node *n=malloc(sizeof(n)); 
	if(n){
		n->val=val; 
		n->next=next; 
	}
	return n; 
}

node *next(node *n, node *next){
	if(n) n->next=next; 
	return n; 
}

node *dump(node *n){
	printf("nodes: "); 
	for(; n; n=n->next){
		printf("(%d)%s", n->val, n->next?"->":""); 
	}
	printf("\n"); 
	return n; 
}
#else
list *new(void){
	list *l=malloc(sizeof(l)); 
	if(l){
		l->head=NULL; 
		l->tail=NULL; 
		l->count=0; 
	}
	return l; 
}

list *append(list *l, int val){
	printf("append(%d)\n", val); 
	if(l){
		node *n=malloc(sizeof(n)); 
		if(n){
			n->val=val; 
			n->next=NULL; 
			if(l->head){
				l->tail->next=n; 
				l->tail=n; 
				l->count++; 
			}else{
				l->head=n; 
				l->tail=n; 
				l->count++; 
			}
		}
	}
	return l; 
}

list *appendByArray(list *l, int *a, int n){
	if(l){
		if(a){
			for(int i=0; i<n; i++) append(l, a[i]); 
		}
	}
	return l; 
}

list *delete(list *l, int val){
	printf("delete(%d)\n", val); 
	if(l){
		node *prev, *curr; 
		prev=NULL; 
		curr=l->head; 
		while(curr){
			if(curr->val==val){
				if(prev){
					prev->next=curr->next; 
				}
				if(curr==l->head){
					l->head=curr->next; 
				}
				if(curr==l->tail){
					l->tail=prev; 
				}
				free(curr); 
				l->count--; 
			}
			prev=curr; 
			curr=curr->next; 
		}
	}
	return l; 
}

list *dump(list *l){
	printf("list(%d): ", l->count); 
	for(node *n=l->head; n; n=n->next){
		printf("(%d)%s", n->val, n->next?"->":""); 
	}
	printf("\n"); 
	return l; 
}

#endif

void test001(void){
#if 0
	node *n=new(5, new(4, new(6, NULL))); 
	dump(n); 
#else
	list *l=new(); 
	append(append(append(l, 5), 6), 4); 
	dump(l); 
	append(l, 9); 
	dump(l); 
	delete(l, 5); 
	dump(l); 
	delete(l, 9); 
	dump(l); 
	delete(dump(delete(l, 4)), 6); 
	dump(l); 
	appendByArray(l, (int *)((int []){9,7,3,2,1,5,6,8,4}), 9); 
#endif
}

int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

