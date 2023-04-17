
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

typedef struct vertex vertex; 
typedef struct vertexList vertexList; 
typedef struct adjacency adjacency; 
typedef struct adjacencyList adjacencyList; 
typedef int vertexData; 
typedef vertex* adjacencyData; 
struct vertex {
	vertexData val; 
	adjacencyList *list; 
	vertex *next; 
	vertex *prev; 
}; 
struct vertexList {
	vertex *head; 
	vertex *tail; 
	int count; 
}; 
struct adjacency {
	adjacencyData val; 
	adjacency *prev; 
	adjacency *next; 
}; 
struct adjacencyList {
	adjacency *head; 
	adjacency *tail; 
	int count; 
}; 
adjacencyList *newAL(void){
	adjacencyList *al=malloc(sizeof(*al)); 
	if(al){
		al->head=NULL; 
		al->tail=NULL; 
		al->count=0; 
	}
	return al; 
}
int isExistAL(adjacencyList *al, adjacencyData val){
	for(adjacency *a=al->head; a; a=a->next){
		if(a->val==val){
			return 1; 
		}
	}
	return 0; 
}
adjacencyList *appendAL(adjacencyList *al, adjacencyData val){
	printf("appendAL(%d)\n", val?val->val:-1); 
	if(al&&val){
		if(!isExistAL(al, val)&&val->list!=al){
			adjacency *a=malloc(sizeof(*a)); 
			if(a){
				a->val=val; 
				a->prev=NULL; 
				a->next=NULL; 
				if(!al->head){
					al->head=a; 
					al->tail=a; 
					al->count++; 
				}else{
					al->tail->next=a; 
					a->prev=al->tail; 
					al->tail=a; 
					al->count++; 
				}
			}
		}
	}
	return al; 
}
adjacencyList *removeAL(adjacencyList *al, adjacencyData val){
	printf("removeAL(%d)\n", val?val->val:-1); 
	if(al&&val){
		adjacency *curr=al->head; 
		adjacency *prev=NULL; 
		adjacency *next=NULL; 
		while(curr){
			next=curr->next; 
			if(curr->val==val){
				if(prev){
					prev->next=next; 
					if(next) next->prev=prev; 
				}
				if(curr==al->head){
					al->head=next; 
					if(next) next->prev=NULL; 
				}
				if(curr==al->tail){
					al->tail=NULL; 
				}
				free(curr); 
				al->count--; 
			}
			prev=curr; 
			curr=next; 
		}
	}
	return al; 
}
adjacencyList *dumpAL(adjacencyList *al){
	printf("al(%d): ", al->head?al->count:-1); 
	if(al){
		for(adjacency *a=al->head; a; a=a->next){
			printf("(%d)%s", a->val->val, a->next?"->":""); 
		}
	}
	printf("\n"); 
	return al; 
}
vertexList *newVL(void){
	vertexList *vl=malloc(sizeof(*vl)); 
	if(vl){
		vl->head=NULL; 
		vl->tail=NULL; 
		vl->count=0; 
	}
	return vl; 
}
int isExistVL(vertexList *vl, vertexData val){
	for(vertex *v=vl->head; v; v=v->next){
		if(v->val==val){
			return 1; 
		}
	}
	return 0; 
}
vertex *findVL(vertexList *vl, vertexData val){
	for(vertex *v=vl->head; v; v=v->next){
		if(v->val==val){
			return v; 
		}
	}
	return NULL; 
}
vertexList *appendVL(vertexList *vl, vertexData val){
	printf("appendVL(%d)\n", val); 
	if(vl){
		int vertexHunt=0; 
		// search if vertex exists? 
#if 0
		for(vertex *v=vl->head; v; v=v->next){
			if(v->val==val){
				vertexHunt=1; 
				break; 
			}
		}
#endif
#if 1
		vertexHunt=isExistVL(vl, val); 
#endif
		if(!vertexHunt){
			vertex *v=malloc(sizeof(*v)); 
			if(v){
				v->val=val; 
				v->prev=NULL; 
				v->next=NULL; 
#if 0
				v->list=malloc(sizeof(*(v->list))); 
				if(v->list){
					v->list->head=NULL; 
					v->list->tail=NULL; 
					v->list->count=0; 
				}
#else
				v->list=newAL(); 
#endif
				if(!vl->head){
					vl->head=v; 
					vl->tail=v; 
					vl->count++; 
				}else{
					vl->tail->next=v; 
					v->prev=vl->tail; 
					vl->tail=v; 
					vl->count++; 
				}
			}
		}
	}
	return vl; 
}
vertexList *removeVL(vertexList *vl, vertexData val){
	printf("removeVL(%d)\n", val); 
	if(vl){
		vertex *prev=NULL, *next=NULL; 
		vertex *curr=vl->head; 
		while(curr){
			next=curr->next; 
			if(curr->val==val){
				if(prev){
					prev->next=next; 
				}
				if(curr==vl->head){
					vl->head=next; 
				}
				if(curr==vl->tail){
					vl->tail=next; 
				}
				free(curr); 
				vl->count--; 
			}
			prev=curr;
			curr=next; 
		}
	}
	return vl; 
}
vertexList *dumpVL(vertexList *vl){
	printf("vl(%d): ", vl?vl->count:-1); 
	if(vl){
		for(vertex *v=vl->head; v; v=v->next){
			printf("(%d)%s", v->val, v->next?"->":""); 
		}
	}
	printf("\n"); 
	if(vl){
		for(vertex *v=vl->head; v; v=v->next){
			printf("v(%d): ", v->val); 
			dumpAL(v->list); 
		}
	}
	return vl; 
}
vertexList *addEdgeVL(vertexList *vl, vertexData val1, vertexData val2){
	if(vl){
		if(val1!=val2){
			printf("appendEdge(%d): ", val1); 
			appendAL((findVL(vl, val1))->list, findVL(vl, val2)); 
			printf("appendEdge(%d): ", val2); 
			appendAL((findVL(vl, val2))->list, findVL(vl, val1)); 
		}
	}
	return vl; 
}
vertexList *removeEdgeVL(vertexList *vl, vertexData val1, vertexData val2){
	if(vl){
		if(val1!=val2){
			printf("removeEdge(%d): ", val1); 
			removeAL((findVL(vl, val1))->list, findVL(vl, val2)); 
			printf("removeEdge(%d): ", val2); 
			removeAL((findVL(vl, val2))->list, findVL(vl, val1)); 
		}
	}
	return vl; 
}
void test001(void){
	do {
		vertexList *vl=newVL(); 
		if(vl){
			dumpVL(appendVL(vl, 5)); 
			dumpVL(appendVL(appendVL(vl, 9), 7)); 
			dumpVL(appendVL(vl, 5)); 
			dumpVL(removeVL(vl, 5)); 
			dumpVL(removeVL(vl, 7)); 
			dumpVL(removeVL(vl, 9)); 
		}
	} while(0); 
	do {
		vertexList *vl=newVL(); 
		if(vl){
			dumpVL(appendVL(vl, 5)); 
			dumpVL(appendVL(appendVL(vl, 9), 7)); 
			dumpVL(appendVL(vl, 3)); 
			dumpVL(addEdgeVL(vl, 5, 9)); 
			dumpVL(addEdgeVL(vl, 5, 3)); 
			dumpVL(removeEdgeVL(vl, 5, 9)); 
		}
	} while(0); 
	do {
		vertexList *vl=newVL(); 
		if(vl){
			dumpVL(appendVL(vl, 5)); 
			dumpVL(appendVL(appendVL(vl, 9), 7)); 
			dumpVL(appendVL(vl, 3)); 
			dumpVL(appendVL(vl, 11)); 
			dumpVL(addEdgeVL(vl, 5, 9)); 
			dumpVL(addEdgeVL(vl, 5, 3)); 
			dumpVL(addEdgeVL(vl, 3, 11)); 
		}
	} while(0); 
}
int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

