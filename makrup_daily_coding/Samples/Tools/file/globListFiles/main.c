#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <glob.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#if 0
char *REPEAT(char c, int n){
	if(n<1) return strdup(""); 
	char *ans=malloc(sizeof(char)*(n+1)); 
	if(ans){
		memset((void *)ans, c, n); 
		ans[n]='\0'; 
	}
	return ans; 
}
#endif

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

int printFileInfo(){
	return 0; 
}

void usage(char *name){
	printf("Usage: \n"); 
	printf("%.*s%s <path>\n", 4, REPEAT(" ", 40), name); 
}

int main(int argc, char *argv[]){
	dbge(); 
	if(argc>1){
		for(int i=1; i<argc; i++){
			// printf("argv[%d]: %s\n", i, argv[i]); 
			glob_t glob_result; 
			// printf("search pattern: %s\n", argv[1]); 
			int result=glob(argv[i], 0, NULL, &glob_result); 
			if(result==0){
				// printf("%lu\n", glob_result.gl_pathc); 
				for(int j=0; j<glob_result.gl_pathc; ++j){
					printf("file[%d]: %s\n", j, glob_result.gl_pathv[j]); 
				}
			}
			globfree(&glob_result); 
		}
	}else{
		usage(argv[0]); 
	}
    exit(EXIT_SUCCESS);
}

