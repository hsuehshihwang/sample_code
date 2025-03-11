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

#define FUNC_BAR "=================================="
#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

void __cyg_profile_func_enter(void *func, void *caller) __attribute__((no_instrument_function));
void __cyg_profile_func_exit(void *func, void *caller) __attribute__((no_instrument_function));
void test001(void){
	dbge(); 
}
void test002(void){
	dbge(); 
}
void test003(void){
	dbge(); 
}
void __cyg_profile_func_enter(void *func, void *caller) {
    printf("Entering function at %p, called from %p\n", func, caller);
}
void __cyg_profile_func_exit(void *func, void *caller) {
    printf("Exiting function at %p, returning to %p\n", func, caller);
}
int main(int argc, char *argv[]){
	dbge(); 
	test001(); 
	test002(); 
    exit(EXIT_SUCCESS);
}

