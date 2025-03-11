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
patternNodeStack *initPatternNodeStack(patternNodeStack *pns){
	if(pns){
		pns->head=NULL; 
		pns->tail=NULL; 
		pns->count=0; 
	}
	return pns; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	char *s=argc>1?argv[1]:"aa"; 
	char *p=argc>2?argv[2]:"a*"; 
	printf("s(%s) p(%s)\n", s, p); 
	// \(\(a[bc].e\)*\)\{3\}\(pqrs\)t\(uv\)
	// 1: \(, 2: \(
	// 1. a[bc].e
	// 1. \)*, 2: \)\{3\}
	char *pss[100]={"\(", "\(", "abc[de].g", NULL}, *pse[100]={"", NULL}; 
	int pssc=0, psec=0; 
#if 0
	char *patternStackStart[100]={NULL}; 
	char *patternStackEnd[100]={NULL}; 
	int patternStackStartCount=0; 
	int patternStackEndCount=0; 
	// printf("sizeof(patternStackStart): %ld\n", sizeof(patternStackStart)/sizeof(char *)); 
	for(int i=0; i<sizeof(patternStackStart)/sizeof(char *); i++) patternStackStart[i]=NULL; 
	for(int i=0; i<sizeof(patternStackEnd)/sizeof(char *); i++) patternStackEnd[i]=NULL; 
	int plen=strlen(p); 
	char *patternStart=p, *patternEnd=p; 
	char *patternCurrent=p; 
	// pattern: a, a*, ., a., \(\), \(\) , [abc], \{3\}
	// pattern is stack or queue? Ans: stack
	while(patternCurrent<patternEnd){
		if(*patternCurrent=='\\'){
			if((pattenCurrent+1)<patternEnd&&*(patternCurrent+1)==')'){
				break; 
			}else if((pattenCurrent+1)<patternEnd&&*(patternCurrent+1)=='('){
				patternStackStart[patternStackStartCount++]=strdup("\\("); 
			}
		}
	}
#endif
#if 0
	patternNodeStack pns; 
	initPatternNodeStack(&pns); 
	appendPatternNodeStack(*pns, ""); 
#endif
	return 0; 
}
