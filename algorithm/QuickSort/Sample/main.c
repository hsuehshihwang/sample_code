
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

void quickSortRecursive(int *a, int n, int max){
	if(n>1){
		int a2[n]; 
		int t=a[n-1]; 
		int lc=0, rc=n-1; 
		for(int i=0; i<n-1; i++){
			if(max==0?compare(&a[i], &t):compare(&t, &a[i])){
				a2[lc]=a[i]; 
				lc++; 
			}else{
				a2[rc]=a[i]; 
				rc--; 
			}
		}
		a2[lc]=t; 
		for(int i=0; i<n; i++) a[i]=a2[i]; 
		quickSortRecursive(a, lc, max); 
		quickSortRecursive(a+lc+1, n-lc-1, max); 
	}
}

void minQuickSortRecursive(int *a, int n){
	quickSortRecursive(a, n, 0); 
}

void minQuickSort(int *a, int n){
	minQuickSortRecursive(a, n); 
}

void maxQuickSortRecursive(int *a, int n){
	quickSortRecursive(a, n, 1); 
}

void maxQuickSort(int *a, int n){
	maxQuickSortRecursive(a, n); 
}

void minQuickSortTest(void){
	printf("%s: \n", __FUNCTION__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={19,27,43,52,71,35,66,78,104}; 
	int n=sizeof(a)/sizeof(a[0]); 
	printf("original array: "); 
	dumpArray(a, n); 
	minQuickSort(a, n); 
	printf("sorted array:   "); 
	dumpArray(a, n); 
}

void maxQuickSortTest(void){
	printf("%s: \n", __FUNCTION__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	int a[]={19,27,43,52,71,35,66,78,104}; 
	int n=sizeof(a)/sizeof(a[0]); 
	printf("original array: "); 
	dumpArray(a, n); 
	maxQuickSort(a, n); 
	printf("sorted array:   "); 
	dumpArray(a, n); 
}

int main(int argc, char *argv[]){
	minQuickSortTest(); 
	maxQuickSortTest(); 
    exit(EXIT_SUCCESS);
}

