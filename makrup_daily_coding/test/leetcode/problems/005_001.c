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
	int max=0; 
	int new_max=0; 
	char *ans=NULL; 
	while(*currChar){
		char *currSubStringEndChar=currChar; 
		leetcodedbg("currChar(%c) currSubStringEndChar(%c)\n", *currChar, *currSubStringEndChar); 
		while(*currSubStringEndChar){
			leetcodedbg("currSubStringEndChar(%c)\n", *currSubStringEndChar); 
			if(*currChar==*currSubStringEndChar){
				char *pStartChar=currChar, *pEndChar=currSubStringEndChar; 
				int palindrome=1; 
				while(pStartChar<pEndChar){
					if(*pStartChar!=*pEndChar){
						palindrome=0; 
						break; 
					}
					pStartChar++; 
					pEndChar--; 
				}
				if(palindrome){
					new_max=currSubStringEndChar-currChar+1; 
					if(new_max>=max){
						max=new_max; 
						if(ans) free(ans); 
						ans=strndup(currChar, max); 
						leetcodedbg("get palindrome: %s\n", ans); 
					}
				}
			}
			currSubStringEndChar++; 
		}
		currChar++; 
	}
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
