
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
#include "vertex.h"

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

void test001(void){
	vertexTab *vt=new(10); 
#if 0
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
#endif
	// BFS(vt, 0); 
}

int main(int argc, char *argv[]){
	test001(); 
    exit(EXIT_SUCCESS);
}

