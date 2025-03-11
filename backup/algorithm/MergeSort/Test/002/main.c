
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

void minMerge(int *al, int nl, int *ar, int nr){
	int cm=0, cl=0, cr=0; 
	int am[nl+nr]; 
	while(cl<nl&&cr<nr){
		if(al[cl]<ar[cr]){
			am[cm]=al[cl]; 
			cl++; cm++; 
		}else{
			am[cm]=ar[cr]; 
			cr++; cm++; 
		}
	}
	while(cl<nl){
		am[cm]=al[cl]; 
		cl++; cm++; 
	}
	while(cr<nr){
		am[cm]=ar[cr]; 
		cr++; cm++; 
	}
	for(int i=0; i<cm; i++){
		al[i]=am[i]; 
	}
}

void minMergeSort(int *a, int n){
	if(n>1){
		int nl=n/2, nr=n-nl; 
		minMergeSort(a, nl); 
		minMergeSort(a+nl, nr); 
		minMerge(a, nl, a+nl, nr); 
	}
}

int main(int argc, char *argv[]){
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={9,7,3,2,0,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dumpArray(a, n); 
	minMergeSort(a, n); 
	dumpArray(a, n); 
    exit(EXIT_SUCCESS);
}

