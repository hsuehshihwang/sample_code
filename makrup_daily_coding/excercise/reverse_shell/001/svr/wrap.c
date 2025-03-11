#include <stdio.h>
#include <string.h>
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

int __real_socket(int domain, int type, int protocol);
int __wrap_socket(int domain, int type, int protocol){
	dbge(); 
	return __real_socket(domain, type, protocol); 
}
