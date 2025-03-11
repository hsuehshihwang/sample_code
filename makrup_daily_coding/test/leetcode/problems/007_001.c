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
#define MAXNUMBER 0x7FFFFFFF
#define MAXMINUSNUMBER 0x80000000
int myAtoi(char* s) {
	int ans=0; 
	char *curr=s; 
	int minus=0; 
	while(*curr){
		// if(curr) leetcodedbg("%02x\n", *curr); 
		if(*curr==' '||*curr=='\t') curr++; 
		else break; 
	}
	if(*curr=='+'){
		minus=0; 
		curr++; 
	}else if(*curr=='-'){
		minus=1; 
		curr++; 
	}
	while(*curr){
		if((*curr)>=0x30&&(*curr)<=0x39){
			int currNumber=(*curr-0x30); 
			// if(currNumber>9) break; 
			// check if out of range
			leetcodedbg("ans(%d)\n", ans); 
			if(minus){
				int checkNumber=MAXMINUSNUMBER/10; 
				if(ans>checkNumber){
					return MAXMINUSNUMBER; 
				}else if(ans==checkNumber){
					currNumber=(currNumber<9?currNumber:8); 
					if(*(curr+1)&&*(curr+1)>=0x30&&*(curr+1)<=0x39) return MAXMINUSNUMBER; 
					else return MAXMINUSNUMBER+(8-currNumber); 
				}
			}else{
				int checkNumber=MAXNUMBER/10; 
				if(ans>checkNumber){
					return MAXNUMBER; 
				}else if (ans==checkNumber){
					leetcodedbg("%s@%d: \n", __FUNCTION__, __LINE__); 
					currNumber=(currNumber<8?currNumber:7); 
					if(*(curr+1)&&*(curr+1)>=0x30&&*(curr+1)<=0x39) return MAXNUMBER; 
					else return MAXNUMBER-(7-currNumber); 
				}
			}
			ans*=10; 
			ans+=currNumber; 
		}else break; 
		curr++; 
	}
	return (minus?-1:1)*ans; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: %d %d\n", __FUNCTION__, __LINE__, 0x80000000, 0x7FFFFFFF); 
	{
		char *str=argc>1?argv[1]:"\x0"; 
		printf("myAtoi(%s): %d\n", str, myAtoi(str)); 
	}
	return 0; 
	int a[]={9,7,3,2,1,5,9,8,6}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	return 0; 
}
