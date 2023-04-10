
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

void buildHeapRecursive(int *a, int n, int i, int max){
	int dad=i; 
	int son=2*dad+1; 
	if(dad<n&&son<n){
		if(son+1<n&&(max==0?compare(&a[son+1], &a[son]):compare(&a[son], &a[son+1]))){
			son++; 
		}
		if((max==0?compare(&a[son], &a[dad]):compare(&a[dad], &a[son]))){
			swap(&a[dad], &a[son]); 
			dad=son; 
			buildHeapRecursive(a, n, dad, max); 
		}
	}
} 

void makeHeapRecursive(int *a, int n, int max){
	// 1 ...  i  ....  2*i or  2*i+1 = n, so n/2 = i 
	for(int i=n/2-1; i>-1; i--){
		buildHeapRecursive(a, n, i, 0); 
	}
}

void heapSortRecursive(int *a, int n, int max){
	makeHeapRecursive(a, n, max==0?1:0); 
	for(int i=n; i>1; i--){
		swap(&a[0], &a[i-1]); 
		buildHeapRecursive(a, i-1, 0, max==0?1:0); 
	}
}

void maxHeapSortRecursive(int *a, int n){
	heapSortRecursive(a, n, 1); 
}

void minHeapSortRecursive(int *a, int n){
	heapSortRecursive(a, n, 0); 
}

void buildHeapLoop(int *a, int n, int i, int max){
	int dad=i; 
	int son=2*dad+1; 
	while(dad<n&&son<n){
		if(son+1<n&&(max==0?compare(&a[son+1], &a[son]):compare(&a[son], &a[son+1]))){
			son++; 
		}
		if((max==0?compare(&a[son], &a[dad]):compare(&a[dad], &a[son]))){
			swap(&a[dad], &a[son]); 
			dad=son; 
			son=2*dad+1; 
		}else break; 
	}
} 

void makeHeapLoop(int *a, int n, int max){
	// 1 ...  i  ....  2*i or  2*i+1 = n, so n/2 = i 
	for(int i=n/2-1; i>-1; i--){
		buildHeapLoop(a, n, i, 0); 
	}
}

void heapSortLoop(int *a, int n, int max){
	makeHeapLoop(a, n, max==0?1:0); 
	for(int i=n; i>1; i--){
		swap(&a[0], &a[i-1]); 
		buildHeapLoop(a, i-1, 0, max==0?1:0); 
	}
}

void maxHeapSortLoop(int *a, int n){
	heapSortLoop(a, n, 1); 
}

void minHeapSortLoop(int *a, int n){
	heapSortLoop(a, n, 0); 
}

void minHeapSortLoopTest(void){
	printf("%s: \n", __FUNCTION__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={19,27,43,52,71,35,66,78,104}; 
	int n=sizeof(a)/sizeof(a[0]);
	printf("original array: "); 
	dumpArray(a, n); 
	minHeapSortLoop(a, n); 
	printf("sorted array:   "); 
	dumpArray(a, n); 
}

void maxHeapSortLoopTest(void){
	printf("%s: \n", __FUNCTION__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={19,27,43,52,71,35,66,78,104}; 
	int n=sizeof(a)/sizeof(a[0]);
	printf("original array: "); 
	dumpArray(a, n); 
	maxHeapSortLoop(a, n); 
	printf("sorted array:   "); 
	dumpArray(a, n); 
}

void minHeapSortRecursiveTest(void){
	printf("%s: \n", __FUNCTION__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={19,27,43,52,71,35,66,78,104}; 
	int n=sizeof(a)/sizeof(a[0]);
	printf("original array: "); 
	dumpArray(a, n); 
	minHeapSortRecursive(a, n); 
	printf("sorted array:   "); 
	dumpArray(a, n); 
}

void maxHeapSortRecursiveTest(void){
	printf("%s: \n", __FUNCTION__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={19,27,43,52,71,35,66,78,104}; 
	int n=sizeof(a)/sizeof(a[0]);
	printf("original array: "); 
	dumpArray(a, n); 
	maxHeapSortRecursive(a, n); 
	printf("sorted array:   "); 
	dumpArray(a, n); 
}

int main(int argc, char *argv[]){
	// minHeapSortLoopTest(); 
	// maxHeapSortLoopTest(); 
	minHeapSortRecursiveTest(); 
	maxHeapSortRecursiveTest(); 
    exit(EXIT_SUCCESS);
}

