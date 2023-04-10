
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

int *dumpArray(int *a, int n){
	if(a){
		printf("a[%d]: [", n); 
		for(int i=0; i<n; i++){
			printf("%d%s", a[i], i!=n-1?",":""); 
		}
		printf("]\n"); 
	}
	return a; 
}

void swap(int *a, int *b){
	int c=*a; 
	*a=*b; 
	*b=c; 
}

int compare(void *a, void *b){
	return *(int *)a < *(int *)b; 
}

void merge(int *la, int ln, int *ra, int rn, int max){
	int lc=0, rc=0; 
	int a[ln+rn]; 
	int n=0; 
	while(lc<ln&&rc<rn){
		if(max==0?compare(&ra[rc], &la[lc]):compare(&la[lc], &ra[rc])){
			a[n]=ra[rc]; 
			n++; rc++; 
		}else{
			a[n]=la[lc]; 
			n++; lc++; 
		}
	}
	while(lc<ln){
		a[n]=la[lc]; 
		n++; lc++; 
	}
	while(rc<rn){
		a[n]=ra[rc]; 
		n++; rc++; 
	}
	for(int i=0; i<n; i++) la[i]=a[i]; 
}

void mergeSort(int *a, int n, int max){
	if(n>1){
		mergeSort(a, n/2, max); 
		mergeSort(a+n/2, n-n/2, max); 
		merge(a, n/2, a+n/2, n-n/2, max); 
	}
}

void minMergeSort(int *a, int n){
	if(n>1){
		mergeSort(a, n/2, 0); 
		mergeSort(a+n/2, n-n/2, 0); 
		merge(a, n/2, a+n/2, n-n/2, 0); 
	}
}


void maxMergeSort(int *a, int n){
	if(n>1){
		mergeSort(a, n/2, 1); 
		mergeSort(a+n/2, n-n/2, 1); 
		merge(a, n/2, a+n/2, n-n/2, 1); 
	}
}

void test001(void){
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dumpArray(a, n); 
	minMergeSort(a, n); 
	dumpArray(a, n); 
}

void test002(void){
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dumpArray(a, n); 
	maxMergeSort(a, n); 
	dumpArray(a, n); 
}

int main(int argc, char *argv[]){
	test001(); 
	test002(); 
    exit(EXIT_SUCCESS);
}

