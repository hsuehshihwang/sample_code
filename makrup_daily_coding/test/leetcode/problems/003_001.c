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
// #define debugleetcode
#ifdef debugleetcode
#define leetcodedbg(fmt,...) printf(fmt"\n",##__VA_ARGS__)
#else
#define leetcodedbg(fmt,...)
#endif
int lengthOfLongestSubstring(char* s) {
	if(!s||!*s) return 0; 
	char *subStringStart=s, *subStringEnd=s+1; 
	int max=1; 
	while(1){
		int new_max=1; 
		char *subString=strndup(subStringStart, subStringEnd-subStringStart); 
		leetcodedbg("subString(%s)", subString); 
		free(subString); 
		char *currChar=subStringStart; 
		char lastChar=*(subStringEnd-1); 
		leetcodedbg("lastChar(%c)", lastChar); 
		new_max=1;
		while(currChar<subStringEnd-1){
			leetcodedbg("compareCurrLastChar(%c,%c)", *currChar, lastChar); 
			if(*currChar==lastChar){
				leetcodedbg("new_max(%d) maxSubString(%.*s)", new_max, new_max, subStringStart); 
				subStringStart=currChar+1; 
				break; 
			}
			new_max++; 
			currChar++; 
		}
		if(new_max>max) max=new_max; 
		if(*subStringEnd) subStringEnd++; 
		else break; 
	}
	return max; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		char str[]="ab"; 
		dbg("lengthOfLongestSubstring(%s): %d", str, lengthOfLongestSubstring(str)); 
	}
	{
		char str[]="abcabcbb"; 
		dbg("lengthOfLongestSubstring(%s): %d", str, lengthOfLongestSubstring(str)); 
	}
	{
		char str[]="a"; 
		dbg("lengthOfLongestSubstring(%s): %d", str, lengthOfLongestSubstring(str)); 
	}
	{
		char str[]=" "; 
		dbg("lengthOfLongestSubstring(%s): %d", str, lengthOfLongestSubstring(str)); 
	}
	{
		char str[]=""; 
		dbg("lengthOfLongestSubstring(%s): %d", str, lengthOfLongestSubstring(str)); 
	}
	{
		dbg("lengthOfLongestSubstring(NULL): %d", lengthOfLongestSubstring(NULL)); 
	}
	return 0; 
}
