#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include "debug.h"
void dump(int *a, int n){
	printf("a[%d]:{", n); 
	for(int i=0; i<n; i++){
		printf("%d%s", a[i], i!=n-1?",":""); 
	}
	printf("}\n"); 
}
void bubble(int *a, int n){
	// for(int len=n; i>=2; i--){
	for(int len=n; len>1; len--){
		for(int i=0; i<len-1; i++){
			if(a[i]>a[i+1]){
				int a_i_bkp=a[i];
				a[i]=a[i+1]; 
				a[i+1]=a_i_bkp; 
			}
		}
	}
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	int a[]={9,7,3,2,1,5,6,8,4}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
	bubble(a, n); 
	dump(a, n); 
	return 0; 
}
