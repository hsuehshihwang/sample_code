
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

#include "debug.h"
#include "queue.h"
#include "stack.h"

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
typedef struct vertexTab vertexTab; 
struct vertex {
	char val; 
	int exists; 
	int *adjacency; 
	int edges; 
}; 
struct vertexTab {
	vertex *v; 
	int size; 
}; 

vertexTab *new(int size){
	vertexTab *vt=malloc(sizeof(vertexTab)); 
	if(vt){
		vt->size=size; 
		vt->v=malloc(sizeof(vertex)*size); 
		if(vt->v){
			for(int i=0; i<size; i++){
				vt->v[i].val=0; 
				vt->v[i].exists=0; 
				vt->v[i].edges=0; 
				vt->v[i].adjacency=malloc(sizeof(int)*size); 
				if(vt->v[i].adjacency){
					for(int j=0; j<size; j++){
						vt->v[i].adjacency[j]=0; 
					}
				}
			}
		}
	}
	return vt; 
}

int search(vertexTab *vt, char val){
	if(vt){
		for(int i=0; i<vt->size; i++){
			if(vt->v[i].val==val){
				return i; 
			}
		}
	}
	return -1; 
}

vertexTab *addEdge(vertexTab *vt, int a, int b){
	if(vt){
		vt->v[a].adjacency[b]=1; 
		vt->v[a].edges++; 
		vt->v[a].exists=1; 
		vt->v[b].adjacency[a]=1; 
		vt->v[b].edges++; 
		vt->v[b].exists=1; 
	}
	return vt; 
}

vertexTab *addEdgeByVal(vertexTab *vt, char a, char b){
	if(vt){
		int ia=search(vt, a); 
		int ib=search(vt, b); 
		addEdge(vt, ia, ib); 
	}
	return vt; 
}

vertexTab *set(vertexTab *vt, int i, char val){
	if(vt){
		vt->v[i].val=val; 
		vt->v[i].exists=1; 
	}
	return vt; 
}

vertexTab *dump(vertexTab *vt){
	if(vt){
		if(vt->v){
			for(int i=0; i<vt->size; i++){
				if(vt->v[i].edges>0){
					// printf("v[%d](val:'%c'): ", i, vt->v[i].val); 
					printf("'%c': ", vt->v[i].val); 
					if(vt->v[i].adjacency){
						for(int j=0; j<vt->size; j++){
							if(vt->v[i].adjacency[j]==1){
								// printf("v[%d](val:'%c') ", j, vt->v[j].val); 
								printf("'%c' ", vt->v[j].val); 
							}
						}
					}
					printf("\n"); 
				}else if(vt->v[i].exists==1){
					// printf("v[%d](val:'%c'): \n", i, vt->v[i].val); 
					printf("'%c': \n", vt->v[i].val); 
				}
			}
		}
	}
	return vt; 
}

#if 0
void BFS(vertexTab *vt, int start){
	// vertex *root=&(vt->v[start]); 
	int q[20]={0}; 
	int qc=0, qtop=0; 
	int qvisited[20]={0}; 
	int qcvisited=0, qtopvisited=0; 
	q[qtop+qc]=start; 
	qc++; 
	printf("BFS: "); 
	while(qc){
		qvisited[qcvisited+qtopvisited]=q[qtop]; 
		qcvisited++; 
		vertex *v=&(vt->v[q[qtop]]); 
		qtop++; qc--; 
		// printf("'%c' qc(%d) qtop(%d)\n", v->val, qc, qtop); 
		printf("'%c' ", v->val); 
		fflush(stdout); 
		if(v->edges){
			for(int i=0; i<vt->size; i++){
				if(v->adjacency[i]==1){
					int visited=0; 
					for(int j=0; j<qcvisited; j++){
						if(qvisited[j+qtopvisited]==i){
							// printf("[%d](%c) visited!!\n", i, vt->v[i].val); 
							visited=1; 
							break; 
						}
					}
					for(int j=0; j<qc; j++){
						if(q[j+qtop]==i){
							// printf("[%d](%c) visited!!\n", i, vt->v[i].val); 
							visited=1; 
							break; 
						}
					}
					if(!visited){
						// printf("push(%c)\n", vt->v[i].val); 
						q[qtop+qc]=i; 
						qc++; 
					}
				}
			}
		}
#if 0
		printf("q: "); 
		for(int i=0; i<qc; i++){
			printf("(%c) ", vt->v[q[i+qtop]].val); 
		}
		printf("\n"); 
		printf("qvisited: "); 
		for(int i=0; i<qcvisited; i++){
			printf("(%c) ", vt->v[qvisited[i+qtopvisited]].val); 
		}
		printf("\n"); 
		sleep(1); 
#endif
	}
	printf("\n"); 
}
#endif

#if 1
void BFS(vertexTab *vt, int start){
	queue *q=newQueue(20);
	queue *qvisited=newQueue(20);
	pushQueue(q, start); 
	printf("BFS: "); 
	while(q->size>0){
		pushQueue(qvisited, *headQueue(q)); 
		vertex *v=&(vt->v[*(headQueue(q))]); 
		popQueue(q); 
		printf("'%c' ", v->val); 
		fflush(stdout); 
		if(v->edges){
			for(int i=0; i<vt->size; i++){
				if(v->adjacency[i]==1){
					int visited=0; 
					for(int j=0; j<qvisited->size; j++){
						if(*(peekQueue(qvisited, j))==i){
							visited=1; 
							break; 
						}
					}
					for(int j=0; j<q->size; j++){
						if(*peekQueue(q, j)==i){
							visited=1; 
							break; 
						}
					}
					if(!visited){
						pushQueue(q, i); 
					}
				}
			}
		}
#if 0
		printf("\n"); 
		printf("q: "); 
		dumpQueue(q); 
		printf("qvisited: "); 
		dumpQueue(qvisited); 
		sleep(1); 
#endif
	}
	printf("\n"); 
}
#endif

void DFS(vertexTab *vt, int start){
	// root=getroot(); 
	stack *path=newStack(20); 
	int visited[vt->size]={0}; 
	for(int i=0; i<vt->size; i++) visited[i]=0; 
	printf("DFS: "); 
	printf("'%c' ", vt->v[start].val); 
	pushStack(path, start); 
	visited[start]=1; 
#if 0
	while(path.exists()){
		curr=path.top(); 
		if((child=curr.getunvisitedchild())){
			print(child); 
			path.push(child); 
		}else{
			path.pop(); 
		}
	}
#else
	while(path->size>0){
		stackData *top=topStack(path); 
		stackData *child=NULL; 
		for(int i=0; i<vt->size; i++){
			if(vt->v[*top].edges){
				if((vt->v[*top].adjacency[i]==1)&&visited[i]){
				}
			}
		}
		if(child){
			printf("'%c'", vt->v[*child].val); 
		}else{
			popStack(path); 
		}
	}
#endif
	printf("\n"); 
}

void test001(void){
	vertexTab *vt=new(10); 
	set(vt, 0, 'A'); 
	set(vt, 1, 'B'); 
	set(vt, 2, 'C'); 
	set(vt, 3, 'D'); 
	set(vt, 4, 'E'); 
	set(vt, 5, 'F'); 
	addEdgeByVal(addEdgeByVal(vt, 'A', 'B'), 'A', 'D'); 
	addEdgeByVal(vt, 'A', 'E'); 
	addEdgeByVal(vt, 'B', 'C'); 
	addEdgeByVal(vt, 'B', 'D'); 
	addEdgeByVal(vt, 'C', 'E'); 
	addEdgeByVal(vt, 'D', 'E'); 
	addEdgeByVal(vt, 'E', 'F'); 
	dump(vt); 
	// BFS(vt, 0); 
	DFS(vt, 0); 
}

void test002(void){
	queueTest(); 
}

void test003(void){
	stackTest(); 
}

int main(int argc, char *argv[]){
	test001(); 
	// test002(); 
	// test003(); 
    exit(EXIT_SUCCESS);
}

