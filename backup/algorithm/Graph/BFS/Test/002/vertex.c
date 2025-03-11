#include "vertex.h"
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
				vt->v[i].edgeTab.head=NULL; 
				vt->v[i].edgeTab.tail=NULL; 
				vt->v[i].edgeTab.size=0; 
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
			}
		}
	}
	return vt; 
}

