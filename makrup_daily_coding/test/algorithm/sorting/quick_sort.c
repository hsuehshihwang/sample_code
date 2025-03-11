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
/*
QuickSort(array, n){
	IF n>=2 DO
		pivot=array[0]
		array_sort[n]
		leftLen=0
		rightLen=0
		FOR i FROM 1 to n-1 DO
			IF array[i]>pivot DO
				array_sort[n-1-rightLen]=array[i]
				rightLen++
			ELSE
				array_sort[leftLen]=array[i]
				leftLen++
			END IF
		END FOR
		array_sort[leftLen]=pivot
		FOR i FROM 0 to n-1 DO
			array[i]=array_sort[i]
		END FOR
		QuickSort(&array[0], leftLen)
		QuickSort(&array[leftLen+1], rightLen)
	END IF
}
*/
void quick_sort(int *array, int n){
// 	IF n>=2 DO
	if(n>=2){
// 		pivot=array[0]
// 		array_sort[n]
// 		leftLen=0
// 		rightLen=0
		int pivot=array[0]; 
		int array_sort[n]; 
		int leftLen=0, rightLen=0; 
// 		FOR i FROM 1 to n-1 DO
// 			IF array[i]>pivot DO
// 				array_sort[n-1-rightLen]=array[i]
// 				rightLen++
// 			ELSE
// 				array_sort[leftLen]=array[i]
// 				leftLen++
// 			END IF
// 		END FOR
// 		array_sort[leftLen]=pivot
		for(int i=1; i<n; i++){
			if(array[i]>pivot){
 				array_sort[n-1-rightLen]=array[i]; 
 				rightLen++; 
			}else{
 				array_sort[leftLen]=array[i]; 
 				leftLen++; 
			}
		}
 		array_sort[leftLen]=pivot; 
// 		FOR i FROM 0 to n-1 DO
// 			array[i]=array_sort[i]
// 		END FOR
		for(int i=0; i<n; i++){
 			array[i]=array_sort[i]; 
		}
// 		QuickSort(&array[0], leftLen)
// 		QuickSort(&array[leftLen+1], rightLen)
		quick_sort(&array[0], leftLen); 
 		quick_sort(&array[leftLen+1], rightLen); 
// 	END IF
	}
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	quick_sort(a, n); 
	dump(a, n); 
	return 0; 
}
