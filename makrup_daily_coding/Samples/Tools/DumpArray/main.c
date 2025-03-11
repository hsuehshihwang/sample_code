#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
void dump2DArrayPtr(int **arr, int m, int n){
	printf("%s: [", __FUNCTION__); 
	for(int i=0; i<m; i++){
		printf("["); 
		for(int j=0; j<n; j++){
			int *pa=arr[i]; 
			printf("%d%s", pa[j], j==n-1?"":","); 
		}
		printf("]%s", i==m-1?"":","); 
	}
	printf("]\n"); 
}
void dump2DArray(int **arr, int m, int n){
	printf("%s: [", __FUNCTION__); 
	int (*pa)[n]=(int(*)[n])arr; 
	for(int i=0; i<m; i++){
		printf("["); 
		for(int j=0; j<n; j++){
			printf("%d%s", pa[i][j], j==n-1?"":","); 
		}
		printf("]%s", i==m-1?"":","); 
	}
	printf("]\n"); 
}
void test001(void){
	int (*arr1[3])[2]={
		(int(*)[2])((int[2]){5,6}), 
		(int(*)[2])((int[2]){3,4}), 
		(int(*)[2])((int[2]){1,2}) 
	};  
	int arr2[3][2]={
		{1, 2}, 
		{3, 4}, 
		{5, 6} 
	};  
	const char *arr1Str=
		"int (*arr1[3])[2]={\n"
		"    (int(*)[2])((int[2]){5,6}), \n"
		"    (int(*)[2])((int[2]){3,4}), \n"
		"    (int(*)[2])((int[2]){1,2}) \n"
		"};  \n"
		; 
	const char *arr2Str=
		"int arr2[3][2]={\n"
        "    {1, 2}, \n"
        "    {3, 4}, \n"
        "    {5, 6} \n"
		"};  \n"
		;
	printf("%s", arr1Str); 
	dump2DArrayPtr((int **)arr1, 3, 2); 
	printf("%s", arr2Str); 
	dump2DArray((int **)arr2, 3, 2); 
}
int main(int argc, char *argv[]){
	dbge(); 
	test001(); 
    exit(EXIT_SUCCESS);
}

