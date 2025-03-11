#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

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

__attribute__((constructor)) void __start(void){
	dbge(); 
}

__attribute__((destructor)) void __end(void){
	dbge(); 
}

void calltrace(const char **name){
	printf("%s(): exit!!\n", *name); 
}
#define CALLTRACE() __attribute__((cleanup(calltrace))) const char *__calltrace_name=__FUNCTION__; printf("%s(): enter!!\n", __FUNCTION__); 

void test002(void); 
void test001(void){
	void calltrace(const char **name);
	CALLTRACE(); 
	test002(); 
	int fd = socket(AF_INET, SOCK_STREAM, 0); 
	void cleanup_test001_function(int *_x){
		dbge(); 
		if( fd > 0 ){
			close(fd); 
		}
	}
	__attribute__((cleanup(cleanup_test001_function))) int x = 0; // Attach cleanup
}

int main(int argc, char *argv[]){
	void calltrace(const char **name);
	CALLTRACE(); 
	dbge(); 
	test001(); 
    exit(EXIT_SUCCESS);
	// return 0; 
}

