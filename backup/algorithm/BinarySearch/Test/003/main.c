
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

// recursive version
void bs(int *a, int N, int s, int e, int t){
	if(e>s){
		int n=e-s; 
		int m=s+n/2; 
		if(a[m]==t){
			dbg("a[%d] == %d", m, t); 
			return; 
		}
		if(a[m]>t){
			if(m>s){
				bs(a, N, s, m, t); 
			}else{
				if(abs(t-a[m-1])<abs(a[m]-t)){
					dbg("a[%d](%d) closed to %d", m-1, a[m-1], t); 
				}else{
					dbg("a[%d](%d) closed to %d", m, a[m], t); 
				}
			}
		}
		if(a[m]<t){
			if((m+1)<e){
				bs(a, N, m+1, e, t); 
			}else{
				if(abs(a[m+1]-t)<abs(t-a[m])){
					dbg("a[%d](%d) closed to %d", m+1, a[m+1], t); 
				}else{
					dbg("a[%d](%d) closed to %d", m, a[m], t); 
				}
			}
		}
	}else{
		dbg(); 
	}
}

void bs1(int *a, int n, int t){
	if(n>0){
		int m=n/2; 
		if(a[m]==t){
			dbg("search %d!!", t); 
			return; 
		}
		if(a[m]>t){
			if(m-1<0){
				dbg("%d close to %d", t, a[m]); 
			}else{
				bs1(a, m, t); 
			}
		}
		if(a[m]<t){
			if(m+1>n-1){
				dbg("%d close to %d", t, a[m]); 
			}else{
				bs1(a+m+1, n-1-m, t); 
			}
		}
	}else{
		dbg(); 
	}
}

int main(int argc, char *argv[]){
    FUNC_TITLE; 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={2, 7, 16, 25, 33, 41, 55, 69, 78, 83, 90, 112}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dumpArray(a, n); 
	bs(a, n, 0, n+1, 23); 
	bs(a, n, 0, n+1, 31); 
	bs(a, n, 0, n+1, 27); 
	bs(a, n, 0, n+1, 33); 
	bs(a, n, 0, n+1, -1); 
	bs(a, n, 0, n+1, 121); 
	bs(a, n, 0, n+1, 78); 
    exit(EXIT_SUCCESS);
}

