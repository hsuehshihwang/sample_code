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
void merge_sort(int *array, int n){
	int *LArray=&array[0]; 
	int LN=n/2; 
	int *RArray=&array[LN]; 
	int RN=n-LN; 
	void arrangeLR(int *inArray, int inN, int *inLArray, int inLN, int *inRArray, int inRN){
		int outArray[inN]; 
		int outN=0, outLN=0, outRN=0; 
		while(outLN<inLN&&outRN<inRN){
			if(inLArray[outLN]<inRArray[outRN]){
				outArray[outN++]=inLArray[outLN++]; 
			}else{
				outArray[outN++]=inRArray[outRN++]; 
			}
		}
		while(outLN<inLN){
			outArray[outN++]=inLArray[outLN++]; 
		}
		while(outRN<inRN){
			outArray[outN++]=inRArray[outRN++]; 
		}
		for(int i=0; i<inN; i++){
			inArray[i]=outArray[i]; 
		}
	}
	if(n>=2){
		merge_sort(LArray, LN); 
		merge_sort(RArray, RN); 
 		arrangeLR(array, n, LArray, LN, RArray, RN); 
	}
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	merge_sort(a, n); 
	dump(a, n); 
	return 0; 
}
