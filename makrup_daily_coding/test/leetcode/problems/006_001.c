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
char* convert(char* s, int numRows) {
	int len=0; 
	char *ans=strdup(s); 
	int sectionChars=numRows-2; 
	char *endChar=s+strlen(s); 
	for(int line=0; line<numRows; line++){
// line=0                       o       o                        
//                              o     o o                        
// line=numRows-3 sCC=1         o   o   o                        
// line=numRows-2 sCC=0         o o     o                        
// line=numRows-1               o       o                        
//                                                               
		char *currChar=s+line; 
		while(currChar<endChar){
			ans[len++]=*currChar; 
			currChar+=(numRows-line); 
			int sectionCharsCount=0; 
			while(currChar<endChar&&sectionCharsCount<sectionChars){
				if(sectionCharsCount==(numRows-line-2)){
					ans[len++]=*currChar; 
				}
				sectionCharsCount++; 
				currChar++; 
			}
			currChar+=line; 
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
