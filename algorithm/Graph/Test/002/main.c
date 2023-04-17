
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
struct vertex {
	char val;
	char *adjacency; 
	int num; 
}; 

vertex list[]={
	{val:'A', adjacency:(char []){'B', 'D', 'E'}, num: 3}, 
	{val:'B', adjacency:(char []){'A', 'C'}, num: 2}, 
	{val:'C', adjacency:(char []){'A', 'C'}, num: 2}, 
	{val:'D', adjacency:(char []){'A', 'E'}, num: 2}, 
	{val:'E', adjacency:(char []){'A', 'D', 'F'}, num: 3}, 
	{val:'F', adjacency:(char []){'E'}, num: 1}, 
}; 

typedef struct queue queue; 
typedef struct queueNode queueNode; 
struct queue {
	queueNode *head;
	queueNode *tail;
	int count; 
	void (*add)(char); 
}; 

void qAdd(char val){
	dbg("val(%c)", val); 
}

queue q={
	head: NULL, 
	tail: NULL, 
	count: 0, 
	add: qAdd, 
}; 

void bfs(void){
	q.add('A'); 
#if 0
	q.add(root); 
	dump(root); 
	while(q.isNotEmpty()){
		n=q.remove(); 
		while((child=n.getUnvistedChild())!=NULL){
			child.visited=true; 
			dump(child); 
			q.add(child); 
		}
	}
#endif
}

void dfs(void){
	int n=sizeof(list)/sizeof(list[0]); 
}

int main(int argc, char *argv[]){
	bfs(); 
	dfs(); 
    exit(EXIT_SUCCESS);
}

