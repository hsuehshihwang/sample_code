
#ifndef __vertex_h__
#define __vertex_h__

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

typedef struct vertex vertex; 
typedef struct vertexTab vertexTab; 
typedef char vertexData; 
typedef struct adjacencyTab adjacencyTab; 
typedef struct adjacency adjacency; 
typedef int adjacencyData; 
struct vertex {
	vertexData val; 
	adjacencyTab *a; 
}; 
struct vertexTab {
	int size; 
	vertex *v; 
	int count; 
}; 
struct adjacencyTab {
	adjacency *head; 
	adjacency *tail; 
}; 
struct adjacency {
	adjacencyData val; 
	adjacency *next; 
}; 

vertexTab *newVertexTab(int size);
adjacencyTab *newAdjacencyTab(void);
adjacencyTab *addAdjacency(adjacencyTab *at, adjacencyData val);
adjacencyTab *removeAdjacency(adjacencyTab *at, adjacencyData val);
adjacencyTab *dumpAdjacencyTab(adjacencyTab *at);
int searchVertex(vertexTab *vt, vertexData val);
vertex *getVertex(vertexTab *vt, int i);
vertex *getVertexByVal(vertexTab *vt, vertexData val);
vertexTab *addVertex(vertexTab *vt, vertexData val);
vertexTab *addEdge(vertexTab *vt, int ia, int ib);
vertexTab *addEdgeByVal(vertexTab *vt, vertexData va, vertexData vb);
vertexTab *dumpVertexTab(vertexTab *vt);
void vertexTest(void);

#endif /*__vertex_h__*/

