
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

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
}while(0); 

#define FUNC_BAR "=================================="
#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
    } while(0); 

void dumpArray(int *a, int n){
	printf("a[%d]: {", n); 
	for(int i=0; i<n; i++){
		printf("%d%s", a[i], i!=n-1?",":""); 
	}
	printf("}\n"); 
}

void BS(int *a, const int bs, const int be, int s, int e, int t){
	if(e>=s){
		int m=(s+e)/2; 
		if(a[m]==t){
			dbg("a[%d](%d) == %d", m, a[m], t); 
		}
		if(a[m]>t){
			BS(a, bs, be, s, m-1, t); 
		}
		if(a[m]<t){
			BS(a, bs, be, m+1, e, t); 
		}
	}
}

void binarySearch(int *a, int n, int t){
	BS(a, 0, n-1, 0, n-1, t);
}

int main(int argc, char *argv[]){
	int a[]={2, 7, 16, 25, 33, 41, 55, 69, 78, 83, 90, 112}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dumpArray(a, n); 
	binarySearch(a, n, a[3]); 
	binarySearch(a, n, -1); 
	binarySearch(a, n, 113); 
	binarySearch(a, n, 13); 
#if 0
	binarySearch(a, n, a[3]); 
	binarySearch(a, n, a[0]); 
	binarySearch(a, n, a[10]); 
	binarySearch(a, n, a[11]); 
	binarySearch(a, n, -1); 
	binarySearch(a, n, 113); 
	binarySearch(a, n, 13); 
	binarySearch(a, n, 43); 
	binarySearch(a, n, 52); 
#endif
	exit(EXIT_SUCCESS);
}

