#ifndef __vertex_h__
#define __vertex_h__

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
typedef struct vertex vertex; 
typedef struct vertexTab vertexTab; 
typedef struct adjacency adjacency; 
typedef struct adjacencyTab adjacencyTab; 
struct adjacencyTab {
	adjacency *head; 
	adjacency *tail; 
	int size; 
}; 
struct vertex {
	char val; 
	int exists; 
	int edges; 
	adjacencyTab edgeTab; 
}; 
struct vertexTab {
	vertex *v; 
	int size; 
}; 
struct adjacency {
	int val; 
	adjacency *next; 
}; 
vertexTab *new(int size);
int search(vertexTab *vt, char val);
vertexTab *addEdge(vertexTab *vt, int a, int b);
vertexTab *addEdgeByVal(vertexTab *vt, char a, char b);
vertexTab *set(vertexTab *vt, int i, char val);
vertexTab *dump(vertexTab *vt);

#endif /*__vertex_h__*/

