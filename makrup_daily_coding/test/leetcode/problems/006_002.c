#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <stdarg.h>
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
int SYSTEM(const char *fmt, ...){
	char cmd[128]; 
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(cmd, 128, fmt, ap); 
	va_end(ap); 
	return system(cmd); 
}
#define debugleetcode
#ifdef debugleetcode
#define leetcodedbg(fmt,...) printf(fmt,##__VA_ARGS__)
#define ECHO(fmt,...) SYSTEM("echo \"%s@%d: "fmt"\" >> /tmp/leetcodedbg", __FUNCTION__, __LINE__,##__VA_ARGS__); 
#else
#define leetcodedbg(fmt,...)
#define ECHO(fmt,...)
#endif
char* convert_printf(char* s, int numRows) {
	int len=1; 
	char *ans=malloc(len); 
	int sectionChars=numRows-2; 
	char *endChar=s+strlen(s); 
	SYSTEM("echo -ne > /tmp/leetcodedbg"); 
	ECHO("sectionChars(%d)", sectionChars); 
	for(int line=0; line<numRows; line++){
// line=0                       o       o                        
//                              o     o o                        
// line=numRows-3 sCC=1         o   o   o                        
// line=numRows-2 sCC=0         o o     o                        
// line=numRows-1               o       o                        
//                                                               
		char *currChar=s+line; 
		ECHO("line(%d)", line); 
		while(currChar<endChar){
			printf("%c", *currChar); 
			ECHO("currChar(%c)", *currChar); 
			ans[len-1]=*currChar; 
			ans=realloc(ans, ++len); 
			currChar+=(numRows-line); 
			int sectionCharsCount=0; 
			while(currChar<endChar&&sectionCharsCount<sectionChars){
				ECHO("currChar(%c) line(%d) sectionCharsCount(%d)", *currChar, line, sectionCharsCount); 
				if(sectionCharsCount==(numRows-line-2)){
					printf("%c", *currChar); 
					ans[len-1]=*currChar; 
					ans=realloc(ans, ++len); 
				}else{
					printf(" "); 
					ans[len-1]=' ';
					ans=realloc(ans, ++len); 
				}
				sectionCharsCount++; 
				currChar++; 
			}
			currChar+=line; 
		}
		if((s+line+1)<endChar&&line<numRows-1){
			printf("\n"); 
			ans[len-1]='\n';
			ans=realloc(ans, ++len); 
		}
	}
	ans[len-1]='\0'; 
	return ans; 
}
//                                                      
// o              o  row=0                              
// o            u o  row=1     o u o u ...     o0=i, o1=i+step...   u0=o1-2*i
// o          u   o  row=2                              
// .                                                    
// .                                                   
// o o                                                  
// o                                                    
//                                                      
// oi(n)=i+step*n   ui(n)=oi(n+1)-2*i                      
char* convert(char* s, int numRows) {
	char *ans=strdup(s); 
	int step=(numRows==1?1:(numRows+numRows-2)); 
	char *curr=ans; 
	int slen=strlen(s); 
	for(int i=0, j=0; i<numRows; i++){
		j=i; 
		int up=1; 
		while(j<slen){
			*(curr++)=*(s+j); 
			if(i==0||i==numRows-1){
				j=j+step; 
			}else if(up==1){
				j=j+step-2*i; 
				up=0; 
			}else{
				j+=2*i; 
				up=1; 
			}
		}
	}
	return ans; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		char *s=(argc>1?argv[1]:"PAYPALISHIRING"); 
		int numsRow=(argc>2?atoi(argv[2]):3); 
		printf("\nconvert_printf(%s,%d): \n%s\n", s, numsRow, convert_printf(s, numsRow)); 
		printf("convert(%s,%d): \n%s\n", s, numsRow, convert(s, numsRow)); 
	}
	return 0; 
	int a[]={9,7,3,2,1,5,9,8,6}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	return 0; 
}
