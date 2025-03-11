#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <stdint.h>
#include "debug.h"
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
#if 1
	char buf[128]; 
	int len; 
	len=read(0, buf, 128); 
	printf("buf(%s) len(%d)\n", buf, len); 
#else
	char buf[128]; 
	fgets(buf, 127, stdin); 
	printf("buf(%s)\n", buf); 
#endif
	return 0; 
#ifdef BASE64DEBUG
#define base64dbg(fmt,...) printf(fmt,##__VA_ARGS__)
#else
#define base64dbg(fmt,...)
#endif
	char *base64(const char *c, int n){
		char map[64]={0}; 
		for(int i=0; i<26; i++){
			map[i]=i+'A'; 
		}
		for(int i=0; i<26; i++){
			map[i+26]=i+'a'; 
		}
		for(int i=0; i<10; i++){
			map[i+52]=i+'0'; 
		}
		map[62]='+'; 
		map[63]='/'; 
		char *pBase64=NULL; 
		int base64Size=4*((n/3)+((n%3)?1:0)); 
		int base64Count=0; 
		pBase64=malloc(sizeof(char)*base64Size+1); 
		pBase64[base64Size]='\0'; 
		if(!pBase64) return NULL; 
		memset(pBase64, '=', sizeof(char)*base64Size); 
		for(int i=0; i<n; i++){
			base64dbg("i(%d) c(%c) ", i, c[i]); 
			switch(i%3){
				case 0: 
					{
						int mapIndex=(c[i]>>2)&0x3F; 
						pBase64[base64Count++]=map[mapIndex]; 
						base64dbg("case(%d) map[%d](%c)\n", i%3, mapIndex, map[mapIndex]); 
						if(i==n-1){
							mapIndex=((c[i]&0x3)<<4);
							pBase64[base64Count++]=map[mapIndex]; 
							base64dbg("case(%d) map[%d](%c)\n", i%3, mapIndex, map[mapIndex]); 
						}
					}
					break; 
				case 1: 
					{
						int mapIndex=((c[i-1]&0x3)<<4)|((c[i]>>4)&0xF); 
						pBase64[base64Count++]=map[mapIndex]; 
						base64dbg("case(%d) map[%d](%c)\n", i%3, mapIndex, map[mapIndex]); 
						if(i==n-1){
							mapIndex=((c[i]&0xF)<<2);
							pBase64[base64Count++]=map[mapIndex]; 
							base64dbg("case(%d) map[%d](%c)\n", i%3, mapIndex, map[mapIndex]); 
						}
					}
					break; 
				case 2: 
					{
						int mapIndex=((c[i-1]&0xF)<<2)|((c[i]>>6)&0x3); 
						pBase64[base64Count++]=map[mapIndex]; 
						base64dbg("case(%d) map[%d](%c)\n", i%3, mapIndex, map[mapIndex]); 
						mapIndex=c[i]&0x3F; 
						pBase64[base64Count++]=map[mapIndex]; 
						base64dbg("case(%d) map[%d](%c)\n", i%3, mapIndex, map[mapIndex]); 
					}
					break; 
			}
		}
		base64dbg("base64Size(%d)\n", base64Size); 
		printf("base64Size(%d)\n", base64Size); 
		for(int i=0; i<base64Size; i++){
			base64dbg("%c", pBase64[i]); 
		}
		base64dbg("\n"); 
		return pBase64; 
	}
	// QUJDREVGRw==
	const char *str=argc>1?argv[1]:"ABCDEFG"; 
	// char str[]="abcdefg"; 
	int n=strlen(str); 
	printf("base64(%s): %s\n", str, base64(str, n)); 
	char cmd[128]={0}; 
	sprintf(cmd, "echo -ne \"%s\" | base64", str); 
	printf("verify(%s): ", str); 
	fflush(stdout); 
	system(cmd);  
	return 0; 
	void toBits(char c){
		printf("c('%c')(0x%02X): ", c, c); 
		for(int i=7; i>=0; i--){
			printf("%d%s", (c>>i)&1, i!=4?"":" "); 
		}
		printf("\n"); 
	}
	toBits('A'); 
	return 0; 
    int result = ({
        int temp = 42;       // Do some computation
        printf("Result = %d\n", temp);
        temp;                // Return the value
    });

    printf("Final Result = %d\n", result);
    return 0;
	printf("%s@%d: 00666(%x)\n", __FUNCTION__, __LINE__, 00666); 
	char *data=strdup("cmd_append/file\x1Ralph: hello world!!"); 
	if(data){
		printf("%s@%d: data(%s)\n", __FUNCTION__, __LINE__, strstr(data, "\x1")+1); 
		free(data); 
		data=NULL; 
	}
	data=strdup("Ralph is a good boy!!\nElly is a good girl!!\n"); 
	if(data){
		printf("%s@%d: data(%s)\n", __FUNCTION__, __LINE__, data); 
		printf("%s@%d: strspn(Ralph): %ld\n", __FUNCTION__, __LINE__, strspn(data, "Ralph")); 
		printf("%s@%d: strcspn(\\n): %ld\n", __FUNCTION__, __LINE__, strcspn(data, "\n")); 
		printf("%s@%d: strcspn(boy): %ld\n", __FUNCTION__, __LINE__, strcspn(data, "boy")); 
		free(data); 
		data=NULL; 
	}
	return 0; 
}
