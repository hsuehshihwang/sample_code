#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
void dump(int *a, int n){
	printf("a[%d]:{", n); 
	for(int i=0; i<n; i++){
		printf("%d%s", a[i], i!=n-1?",":""); 
	}
	printf("}\n"); 
}
void swap(int *a, int *b){
	int a_bkp=*a; 
	*a=*b; 
	*b=a_bkp; 
}
#if 0
void insert_sort(int *a, int n){
	for(int len=2; len<=n; len++){
		for(int i=len-1; i>0; i--){
			if(a[i]<a[i-1]){
				swap(&a[i], &a[i-1]); 
			}
		}
	}
}
#endif
/*
Algorithm: InsertionSort(array, n)
Input: array[n] 
Output: sorted array in accending order

FOR i FROM 1 TO n-1 DO
  j = i
  WHILE (j > 0) AND (array[j] < array[j-1]) DO
    key = array[j]
    array[j] = array[j-1]
    array[j-1] = key
    j = j - 1
  ENd WHILE
END FOR
*/
void insert_sort(int *array, int n){
	for(int i=1; i<n; i++){
		int j=i; 
		while(j>0&&array[j-1]>array[j]){
			int key=array[j];
			array[j]=array[j-1]; 
			array[j-1]=key;  
			j--; 
		}
	}
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	// int a[]={9,7,3,2,1,5,6,8,4}; 
	// int a[]={9,7,3,2,3,5,6,5,4}; 
	// int a[]={}; 
	int a[]={3,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	insert_sort(a, n); 
	dump(a, n); 
	return 0; 
}
