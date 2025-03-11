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

#include "defer.h"

void testcase001(void){
	defer_list __attribute__((cleanup(defer_cleanup_function))) __dlist; 
	defer_init(&__dlist); 
	int fd=1; 
	void defer_func1(void){
		fd=0; 
		dbge("fd(%d)", fd); 
	}
	defer_add(&__dlist, defer_func1); 
	void defer_func2(void){
		dbge("fd(%d)", fd); 
	}
	defer_add(&__dlist, defer_func2); 
	void defer_func3(void){
		dbge("fd(%d)", fd); 
	}
	defer_add(&__dlist, defer_func3); 
}
void testcase002(void){
	DEFER_INIT(); 
	int fd=1; 
	DEFER_ADD(defer_func1, void defer_func1(void){
		fd=0; 
		dbge("fd(%d)", fd); 
	}); 
	DEFER_ADD(defer_func2, void defer_func2(void){
		dbge("fd(%d)", fd); 
	}); 
	DEFER_ADD(defer_func3, void defer_func3(void){
		dbge("fd(%d)", fd); 
	}); 
}

int main(int argc, char *argv[]){
	dbge(); 
	// testcase001(); 
	testcase002(); 
    exit(EXIT_SUCCESS);
}

