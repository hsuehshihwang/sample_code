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
#define debugleetcode
#ifdef debugleetcode
#define leetcodedbg(fmt,...) printf(fmt,##__VA_ARGS__)
#else
#define leetcodedbg(fmt,...)
#endif
char* longestPalindrome(char* s) {
	char *currChar=s; 
	char *subString=NULL; 
	int max=0; 
	char *ans=NULL; 
	while(*currChar){
		char *lChar=currChar, *rChar=currChar; 
		while((lChar>=s)||(*rChar)){
			if(*(rChar+1)==*currChar){
				rChar++; 
			}else if(*(lChar-1)==*currChar){
				lChar--; 
			}else{
				break; 
			}
		}
		while(((lChar-1)>=s)&&*(rChar+1)&&(*(lChar-1)==*(rChar+1))){
			lChar--; 
			rChar++; 
		}
#ifdef debugleetcode
		subString=strndup(lChar, rChar-lChar+1); 
		leetcodedbg("subString(%s)\n", subString); 
		free(subString); 
#endif
		if((rChar-lChar+1)>=max){
			max=rChar-lChar+1; 
			ans=lChar; 
		}
		currChar++; 
	}
	ans[max]='\0'; 
	return ans; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		char *str=argc>1?argv[1]:"aba"; 
		printf("longestPalindrome(%s): %s\n", str, longestPalindrome(str)); 
	}
	return 0; 
}
