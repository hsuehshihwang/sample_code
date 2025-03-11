#include "dfs.h"
#include "stack.h"

void DFS(vertexTab *vt, vertexData start){
	stack *path=newStack(20); 
	int visited[20]={0}; 
	for(int i=0; i<sizeof(visited)/sizeof(int); i++) visited[i]=0; 
	int istart=searchVertex(vt, start); 
	printf("DFS: "); 
	pushStack(path, istart); 
	printf("'%c' ", vt->v[istart].val); 
	while(path->size>0){
		stackData *curr=topStack(path); 
		if(curr){
			visited[*curr]=1; 
			adjacencyTab *at=vt->v[*curr].a; 
			int unvisited=0; 
			if(at){
				for(adjacency *a=at->head; a; a=a->next){
					if(visited[a->val]==0){
						pushStack(path, a->val); 
						printf("'%c' ", vt->v[a->val].val); 
						unvisited=1; 
						break; 
					}
				}
			}
			if(unvisited==0){
				popStack(path); 
			}
		}
	}
	printf("\n"); 
}

void dfsTest(void){
	FUNC_TITLE; 
	vertexTab *vt=newVertexTab(20); 
	if(vt){
		addVertex(vt, 'A'); 
		addVertex(vt, 'B'); 
		addVertex(vt, 'C'); 
		addVertex(vt, 'D'); 
		addVertex(vt, 'E'); 
		addVertex(vt, 'F'); 
		// addAdjacency((getVertexByVal(vt, 'A'))->a, 1); 
		// addEdge(vt, 0, 1); 
		addEdgeByVal(addEdgeByVal(vt, 'A', 'B'), 'A', 'D'); 
		addEdgeByVal(vt, 'A', 'E'); 
		addEdgeByVal(vt, 'B', 'C'); 
		addEdgeByVal(vt, 'C', 'E'); 
		addEdgeByVal(vt, 'D', 'E'); 
		addEdgeByVal(vt, 'E', 'F'); 
		dumpVertexTab(vt); 
		DFS(vt, 'A'); 
	}
}
