#include "vertex.h"

vertexTab *newVertexTab(int size){
	vertexTab *vt=malloc(sizeof(vertexTab)); 
	if(vt){
		vt->size=size; 
		vt->count=0; 
		vt->v=malloc(sizeof(vertex)*size); 
	}
	return vt; 
}

adjacencyTab *newAdjacencyTab(void){
	adjacencyTab *at=malloc(sizeof(adjacencyTab)); 
	if(at){
		at->head=NULL; 
		at->tail=NULL; 
	}
	return at; 
}

adjacencyTab *addAdjacency(adjacencyTab *at, adjacencyData val){
	if(at){
		adjacency *a=malloc(sizeof(adjacency)); 
		if(a){
			a->val=val; 
			a->next=NULL; 
			if(at->head){
				at->tail->next=a; 
				at->tail=a; 
			}else{
				at->head=a; 
				at->tail=a; 
			}
		}
	}
	return at; 
}

adjacencyTab *removeAdjacency(adjacencyTab *at, adjacencyData val){
	if(at){
		adjacency *curr=at->head; 
		adjacency *prev=NULL; 
		adjacency *next=NULL; 
		while(curr){
			next=curr->next; 
			if(curr->val==val){
				if(prev){
					prev->next=next; 
				}
				if(curr==at->head){
					at->head=next; 
				}
				if(curr==at->tail){
					at->tail=NULL; 
				}
				free(curr); 
			}else{
				prev=curr; 
			}
			curr=next; 
		}
	}
	return at; 
}

adjacencyTab *dumpAdjacencyTab(adjacencyTab *at){
	if(at){
		for(adjacency *a=at->head; a; a=a->next){
			printf("'%d' ", a->val); 
		}
		printf("\n"); 
	}
	return at; 
}

int searchVertex(vertexTab *vt, vertexData val){
	if(vt){
		for(int i=0; i<vt->count; i++){
			if(vt->v[i].val==val) return i; 
		}
	}
	return -1; 
}

vertex *getVertex(vertexTab *vt, int i){
	vertex *v=NULL; 
	if(vt){
		if(i<vt->count){
			v=&vt->v[i]; 
		}
	}
	return v; 
}

vertex *getVertexByVal(vertexTab *vt, vertexData val){
	vertex *v=NULL; 
	if(vt){
		for(int i=0; i<vt->count; i++){
			if(val==vt->v[i].val){
				v=&vt->v[i]; 
				break; 
			}
		}
	}
	return v; 
}

vertexTab *addVertex(vertexTab *vt, vertexData val){
	if(vt){
		if(vt->v){
			if(getVertexByVal(vt, val)==NULL){
				vt->v[vt->count].val=val; 
				vt->v[vt->count].a=newAdjacencyTab(); 
				vt->count++; 
			}
		}
	}
	return vt; 
}

vertexTab *addEdge(vertexTab *vt, int ia, int ib){
	if(vt){
		addAdjacency(vt->v[ia].a, ib); 
		addAdjacency(vt->v[ib].a, ia); 
	}
	return vt; 
}

vertexTab *addEdgeByVal(vertexTab *vt, vertexData va, vertexData vb){
	if(vt){
		int ia=searchVertex(vt, va); 
		int ib=searchVertex(vt, vb); 
		if(ia!=-1&&ib!=-1){
			addAdjacency((getVertexByVal(vt, va))->a, ib); 
			addAdjacency((getVertexByVal(vt, vb))->a, ia); 
		}
	}
	return vt; 
}

vertexTab *dumpVertexTab(vertexTab *vt){
	printf("vt(%d): \n", vt?vt->count:0); 
	if(vt){
		for(int i=0; i<vt->count; i++){
			printf("'%c': ", vt->v[i].val); 
			adjacencyTab *at=vt->v[i].a; 
			if(at){
				for(adjacency *a=at->head; a; a=a->next){
					if(a->val<vt->count){
						printf("'%c' ", vt->v[a->val].val); 
					}
				}
				printf("\n"); 
			}
			// dumpAdjacencyTab(vt->v[i].a); 
		}
	}
	return vt; 
}

#include "bfs.h"
#include "dfs.h"

void vertexTest(void){
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
		// BFS(vt, 'A'); 
		// BFS(vt, 'B'); 
		// BFS(vt, 'E'); 
		// BFS(vt, 'D'); 
		// BFS(vt, 'C'); 
		DFS(vt, 'A'); 
	}
}

