#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include "debug.h"
void dump(int *a, int n){
	printf("a[%d]:{", n); 
	for(int i=0; i<n; i++){
		printf("%d%s", a[i], i!=n-1?",":""); 
	}
	printf("}\n"); 
}
void swap(int *a, int *b){
	int c=*a; 
	*a=*b; 
	*b=c; 
}
typedef struct patternNode {
	char *pattern; 
	struct patternNode *next; 
} patternNode; 
typedef struct patternNodeStack {
	patternNode *head; 
	patternNode *tail; 
	int count; 
} patternNodeStack; 
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	char *s=argc>1?argv[1]:"aa"; 
	char *p=argc>2?argv[2]:"a*"; 
	printf("s(%s) p(%s)\n", s, p); 
	// pattern: a, a*, ., a., \(\), \(\) , [abc], \{3\}
	// pattern is stack or queue? Ans: stack
	return 0; 
	dbg("v=%d, v|2=%d", 1, 1|(1<<1)); 
	dbg("v=%d, v|2=%d", 0, 0|(1<<1)); 
	return 0; 
	int a[]={9,7,3,2,1,5,9,8,6}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	return 0; 
}
