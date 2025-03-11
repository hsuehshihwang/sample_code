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
bool isPalindrome(int x) {
	bool ans=false; 
	int curr=x; 
	if(x>=0){
		int digit=0; 
		int digits[12]={0}; 
		digits[digit++]=(curr%10); 
		while(curr/10){
			digits[digit++]=((curr/10)%10); 
			curr/=10; 
		}
#if 0
		for(int i=digit-1; i>=0; i--){
			leetcodedbg("%d", digits[i]); 
		}
		leetcodedbg("\n"); 
#endif
		int left=0, right=digit-1; 
		while(left<right){
			if(digits[left]!=digits[right]) return false; 
			left++; 
			right--; 
		}
		return true; 
	}else return false; 
	return ans; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		int num=(argc>1?atoi(argv[1]):12321); 
		printf("isPalindrome(%d): %s\n", num, isPalindrome(num)?"true":"false"); 
	}
	return 0; 
	int a[]={9,7,3,2,1,5,9,8,6}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	return 0; 
}
