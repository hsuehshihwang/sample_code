
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
	for(int i=0; i<n; i++) printf("%d%s", a[i], i!=n-1?",":"}\n"); 
}

int bsLoop(int *a, int n, int s, int e, int t){
	return -1; 
}

int bs(int *a, int n, int t){
	// return bsLoop(a, n, 0, n-1, t); 
	int s=0, e=n-1; 
	while(1){
		int m=(s+e)/2; 
		if(m<0||m>(n-1)) break; 
		if(a[m]==t){
			dbg("a[%d]==%d", m, t); 
			return m; 
		}
		if(a[m]<t){
			if((m+1)>e){
				if(m==(n-1)){
					dbg("m==n-1. a[%d](%d) is closest to %d", m, a[m], t); 
					return m; 
				}else{
					int rv=abs(a[m+1]-t); 
					int lv=abs(a[m]-t); 
					if(rv==lv){
						dbg("rv==lv!!"); 
						dbg("a[%d](%d) is closest to %d!!", m, a[m], t); 
						return m; 
					}
					if(rv>lv){
						dbg("rv>lv!!"); 
						dbg("a[%d](%d) is closest to %d!!", m, a[m], t); 
						return m; 
					}
					if(rv<lv){
						dbg("rv<lv!!"); 
						dbg("a[%d](%d) is closest to %d!!", m+1, a[m+1], t); 
						return m; 
					}
				}
			}else{
				s=m+1; 
			}
		}
		if(a[m]>t){
			if((m-1)<s){
				if(m==0){
					dbg("m==0, a[%d](%d) is closest to %d", m, a[m], t); 
					return m; 
				}else{
					int rv=abs(a[m]-t); 
					int lv=abs(a[m-1]-t); 
					if(rv==lv){
						dbg("rv==lv!!"); 
						dbg("a[%d](%d) is closest to %d!!", m-1, a[m-1], t); 
						return m; 
					}
					if(rv>lv){
						dbg("rv>lv!!"); 
						dbg("a[%d](%d) is closest to %d!!", m-1, a[m-1], t); 
						return m; 
					}
					if(rv<lv){
						dbg("rv<lv!!"); 
						dbg("a[%d](%d) is closest to %d!!", m, a[m], t); 
						return m; 
					}
				}
			}else{
				e=m-1; 
			}
		}
	}
	return -1; 
}

int main(int argc, char *argv[]){
    FUNC_TITLE; 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={2, 7, 16, 25, 33, 41, 55, 69, 78, 83, 90, 112}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dumpArray(a, n); 
	dbg("bs(%d)", bs(a, n, 33)); 
	dbg("bs(%d)", bs(a, n, 2)); 
	dbg("bs(%d)", bs(a, n, 112)); 
	dbg("bs(%d)", bs(a, n, 12)); 
	dbg("bs(%d)", bs(a, n, 11)); 
	dbg("bs(%d)", bs(a, n, 17)); 
	dbg("bs(%d)", bs(a, n, 71)); 
	dbg("bs(%d)", bs(a, n, 29)); 
	dbg("bs(%d)", bs(a, n, -1)); 
	dbg("bs(%d)", bs(a, n, 122)); 
    exit(EXIT_SUCCESS);
}

