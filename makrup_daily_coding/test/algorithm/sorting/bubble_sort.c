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
Algorithm: BubbleSort(number array[], size=n)
Input: array[n]
Output: sorted array in accending order

FOR size FROM n to 2 DO
  id=0
  lastId=size-1
  WHILE id != lastId DO
    IF array[id]>array[id+1] DO
      key=array[id]
      array[id]=array[id+1]
      array[id+1]=key
    END IF
    id++
  END WHILE
END FOR

*/
void bubble_sort(int *array, int n){
	for(int size=n; size>1; size--){
		int id=0; 
		int lastId=size-1; 
		while(id!=lastId){
			if(array[id]>array[id+1]){
				int key=array[id]; 
				array[id]=array[id+1]; 
				array[id+1]=key; 
			}
			id++; 
		}
	}
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	bubble_sort(a, n); 
	dump(a, n); 
	return 0; 
}
