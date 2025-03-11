
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
typedef struct list list; 
struct node {
	int val; 
	node *next; 
}; 
struct list {
	node *head; 
	node *tail; 
	int count; 
}; 
list *new(void){
	list *l=malloc(sizeof(*l)); 
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
		node *n=malloc(sizeof(*n)); 
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
	for(int i=0; i<n; i++){
		append(l, a[i]); 
	}
	return l; 
}
list *delete(list *l, int val){
	printf("delete(%d)\n", val); 
	if(l){
		node *prev=NULL; 
		node *curr=l->head; 
		while(curr){
			node *next=curr->next; 
			if(curr->val==val){
				if(prev){
					prev->next=next; 
				}
				if(curr==l->head){
					l->head=next; 
				}
				if(curr==l->tail){
					l->tail=prev; 
				}
				l->count--; 
				free(curr); 
			}else{
				prev=curr; 
			}
			curr=next; 
		}
	}
	return l; 
}
list *dump(list *l){
	if(l){
		printf("l(%d): ", l->count); 
		for(node *n=l->head; n; n=n->next){
			printf("(%d)%s", n->val, n->next?"->":""); 
		}
		printf("\n"); 
	}
	return l; 
}
void test001(void){
	list *l=new(); 
	if(l){
		append(l, 5); 
		dump(l); 
		dump(append(append(l, 6), 4)); 
		dump(delete(l, 5)); 
		dump(delete(l, 4)); 
		dump(delete(l, 6)); 
		{
			int a[]={1,2,3,2}; 
			int n=sizeof(a)/sizeof(a[0]); 
			// dump(appendByArray(l, (int []){1,2,3,4}, 4)); 
			dump(appendByArray(l, a, n)); 
			dump(delete(l, 2)); 
			printf("l->tail->val(%d)\n", l->tail?l->tail->val:-999); 
			// dump(append(l, 5)); 
			dump(appendByArray(l, (int []){3,2,4, 1}, 4)); 
			dump(delete(l, 1)); 
		}
	}
}
int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

