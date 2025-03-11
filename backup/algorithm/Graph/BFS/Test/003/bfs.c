#include "bfs.h"

void BFS(vertexTab *vt, vertexData start){
	queue *path=newQueue(20); 
	int visited[20]={0}; 
	for(int i=0; i<sizeof(visited)/sizeof(int); i++) visited[i]=0; 
	int istart=searchVertex(vt, start); 
	printf("BFS: "); 
	pushQueue(path, istart); 
	while(path->size>0){
		queueData *curr=headQueue(path); 
		popQueue(path); 
		if(curr){
			// printf("curr(%d)('%c') ", *curr, vt->v[*curr].val); 
			printf("'%c' ", vt->v[*curr].val); 
			visited[*curr]=1;
			adjacencyTab *at=vt->v[*curr].a; 
			if(at){
				for(adjacency *a=at->head; a; a=a->next){
					if(visited[a->val]==0){
						pushQueue(path, a->val); 
					}
				}
			}
		}
#if 0
		dumpQueue(path); 
		printf("visited: "); 
		for(int i=0; i<sizeof(visited); i++){
			if(visited[i]==1) printf("%d ", i); 
		}
		printf("\n"); 
#endif
	}
	printf("\n"); 
}

