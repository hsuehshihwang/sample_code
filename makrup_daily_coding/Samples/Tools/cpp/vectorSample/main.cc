#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

using namespace std; 

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 


#ifdef __cplusplus
extern "C"
{
#endif
#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)
#define FUNC_TITLE() \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
    } while(0); 
#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus
extern "C"
{
#endif
int c_main(int argc, char *argv[]);
#ifdef __cplusplus
} /* extern "C" */
#endif

int cpp_main(int argc, char **argv);

#include <vector>

int main(int argc, char *argv[]){
    FUNC_TITLE(); 
	vector<int> v1; 
	v1.push_back(9); 
	v1.push_back(7); 
	v1.push_back(3); 
	v1.push_back(2); 
	dbge("capacity(%ld)", v1.capacity()); 
	dbge("size(%ld)", v1.size()); 
	printf("v1[%ld]: {", v1.size()); 
	for(vector<int>::iterator it=v1.begin(); it!=v1.end(); ++it){
		printf("%d%s", *it, it!=v1.end()-1?",":""); 
	}
	printf("}\n"); 
	vector<int> v2={9,7,3,2,1,5,6,8}; 
	printf("v2[%ld]: {", v2.size()); 
	for(vector<int>::iterator it=v2.begin(); it!=v2.end(); ++it){
		printf("%d%s", *it, it!=v2.end()-1?",":""); 
	}
	printf("}\n"); 
	dbge("v2[2](%d)", v2[2]); 
    exit(EXIT_SUCCESS);
}

