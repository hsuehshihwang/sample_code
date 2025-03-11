#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <stdbool.h>
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
#define debugleetcode
#ifdef debugleetcode
#define leetcodedbg(fmt,...) printf(fmt,##__VA_ARGS__)
#else
#define leetcodedbg(fmt,...)
#endif
typedef struct matchNode {
	char *string; 
	struct matchNode *next; 
} matchNode; 
typedef struct patternNode {
	char *string;  
	struct patternNode *next; 
} patternNode; 
// ex: \(xxx\), xxx[abc]yyy
char *getPattern(char *start, char *end){
	char *pCurr=start; 
	char *pPatternStart=NULL, *pPatternEnd=NULL; 
	while(pCurr<end){
		if(*pCurr=='\\'){
			pCurr++; 
			if(pCurr<end&&*pCurr=='('){
				pCurr++; 
			}else{
				leetcodedbg("pattern start error!!\n"); 
				exit(1); 
			}
		}else{
			pPatternStart=pCurr; 
			pCurr++; 
			break; 
		}
	}
	leetcodedbg("pPatternStart(%c)\n", *pPatternStart); 
	while(pCurr<end){
		if(*pCurr=='\\'){
			pCurr++; 
			if(pCurr<end&&*pCurr=='('){
				leetcodedbg("pattern end error!!\n"); 
				exit(1); 
			}else{
				pCurr++; 
			}
		}else{
			pPatternEnd=(++pCurr); 
		}
	}
	leetcodedbg("pPatternEnd(%c)\n", *pPatternEnd); 
	return strndup(pPatternStart, pPatternEnd-pPatternStart); 
}
char *getMatch(char *start, char *end, char *pattern){
}
bool isMatch(char* s, char* p) {
	bool ans=false; 
	int slen=strlen(s); 
	int plen=strlen(p); 
	char *pPattern=getPattern(p, p+plen); 
	leetcodedbg("pattern(%s)\n", pPattern); 
	char *pMatch=getMatch(s, s+slen, pPattern); 
	if(pPattern) free(pPattern); 
	return ans; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		char *s=(argc>1?argv[1]:"aa"); 
		char *p=(argc>2?argv[2]:"a*"); 
		printf("isMatch(\"%s\", \"%s\"): %d\n", s, p, isMatch(s, p)); 
	}
	return 0; 
	int a[]={9,7,3,2,1,5,9,8,6}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	return 0; 
}
