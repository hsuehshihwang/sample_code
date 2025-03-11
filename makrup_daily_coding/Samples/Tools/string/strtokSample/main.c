#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)

#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

#define DELIM1 "\x77\x88\x11"
#define DELIM2 "\x77\x88\x22"
#define DELIM3 "\x77\x88\x33"
int main(int argc, char *argv[]){
	dbge(); 
	char buf[]="greeting"DELIM1"20"DELIM2"    Hello World!!   "DELIM3; 
	int tlv=0; 
	char *p=strtok(buf, DELIM1); 
	printf("T(%s)\n", p); 
	while(p){
		p=strtok(NULL, tlv==1?DELIM2:DELIM3); 
		printf("%s(%s)\n", tlv==1?"L":"V", p); 
		tlv++; 
	}
    exit(EXIT_SUCCESS);
}

