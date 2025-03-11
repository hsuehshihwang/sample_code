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
void build_heap(int *array, int n){
	// 0, 1, 2, 3....
	// (0, 1, 2) (1, 3, 4) (2, 5, 6) ...
	// L=(root+1)*2-1  R=(root+1)*2
	// rootId=len/2
// 	lastRootId=n/2-1
	int lastrootid=n/2-1; 
// 	FOR rootId FROM lasRootId to 0 DO
	for(int rootid=lastrootid; rootid>=0; rootid--){
// 		sonId=2*rootId+1
// 		IF array[sonId+1] > array[sonId] DO
// 			sonId++
// 		ENd IF
		int sonid=2*rootid+1; 
		if(array[sonid+1]>array[sonid]) sonid++; 
// 		IF array[sonId]>array[rootId] DO
// 			key=array[sonId]
// 			array[sonId]=array[rootId]
// 			array[rootId]=key
// 		END IF
		if(array[sonid]>array[rootid]){
			int root=array[rootid]; 
			array[rootid]=array[sonid]; 
			array[sonid]=root; 
		}
	}
// 	END FOR
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	build_heap(a, n); 
	dump(a, n); 
	return 0; 
}
