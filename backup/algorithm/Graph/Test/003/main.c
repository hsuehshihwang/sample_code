
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

void bfs(void){
	char q[100]; 
	int qc=0, qrm=0; 
	// q.add(root); => 
	{
		q[qc]='A'; 
		qc++; 
	}
	// dump(root); =>
	printf("(%c)->", q[0]); 
	while((qc-qrm)>0){
		// n=q.remove(); =>
		char n=q[qrm]; 
		qrm++; 
		// initChiildList(); => 
		typedef struct child child; 
		struct child {
			char val; 
			int visited; 
		}; 
		child childList[100]; 
		int cc=0; 
		memset(childList, 0, sizeof(childList)); 
		// loadChildList(); => 
	}
#if 0
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

