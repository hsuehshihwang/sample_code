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
void swap(int *a, int *b){
	int c=*a; 
	*a=*b; 
	*b=c; 
}
#define debugleetcode
#ifdef debugleetcode
// #define leetcodedbg(fmt,...) printf(fmt"\n",##__VA_ARGS__)
#define leetcodedbg dbg
#else
#define leetcodedbg(fmt,...)
#endif
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int numsSize=nums1Size+nums2Size; 
	int numsCount=0; 
	// case 1: n=6 => 0,1,2,3,4,5 => n/2=3, n%2=0 medians={2,3}
	// case 2: n=5 => 0,1,2,3,4 => n/2=2, n%2=1 medians=(2,2)
	// case 3: n=2 => 0,1 medians=(0,1)
	int medians[2]={numsSize/2-!(numsSize%2),numsSize/2}; 
	int mediansNums[2]={0,0}; 
	leetcodedbg("numsSize(%d), medians(%d,%d)", numsSize, medians[0], medians[1]); 
	int *currNums1=nums1; 
	int *currNums2=nums2; 
	while((currNums1<nums1+nums1Size)||(currNums2<nums2+nums2Size)){
		if((currNums1<nums1+nums1Size)&&(currNums2<nums2+nums2Size)){
			while((currNums1<nums1+nums1Size)&&(*currNums1<*currNums2)){
				leetcodedbg("nums[%d]=currNums1(%d)", numsCount, *currNums1); 
				if(medians[0]==-1){
					if(medians[1]==numsCount){
						mediansNums[1]=*currNums1; 
						goto ans; 
					}
				}else{
					if(medians[0]==numsCount){
						medians[0]=-1; 
						mediansNums[0]=*currNums1; 
						mediansNums[1]=*currNums1; 
					}
				}
				numsCount++; 
				currNums1++; 
			}
			while((currNums1<nums1+nums1Size)&&(currNums2<nums2+nums2Size)&&(*currNums2<=*currNums1)){
				leetcodedbg("nums[%d]=currNums2(%d)", numsCount, *currNums2); 
				if(medians[0]==-1){
					if(medians[1]==numsCount){
						mediansNums[1]=*currNums2; 
						goto ans; 
					}
				}else{
					if(medians[0]==numsCount){
						medians[0]=-1; 
						mediansNums[0]=*currNums2; 
						mediansNums[1]=*currNums2; 
					}
				}
				numsCount++; 
				currNums2++; 
			}
		}else{
			while(currNums1<nums1+nums1Size){
				leetcodedbg("nums[%d]=currNums1(%d)", numsCount, *currNums1); 
				if(medians[0]==-1){
					if(medians[1]==numsCount){
						mediansNums[1]=*currNums1; 
						goto ans; 
					}
				}else{
					if(medians[0]==numsCount){
						medians[0]=-1; 
						mediansNums[0]=*currNums1; 
						mediansNums[1]=*currNums1; 
					}
				}
				numsCount++; 
				currNums1++; 
			}
			while(currNums2<nums2+nums2Size){
				leetcodedbg("nums[%d]=currNums2(%d)", numsCount, *currNums2); 
				if(medians[0]==-1){
					if(medians[1]==numsCount){
						mediansNums[1]=*currNums2; 
						goto ans; 
					}
				}else{
					if(medians[0]==numsCount){
						medians[0]=-1; 
						mediansNums[0]=*currNums2; 
						mediansNums[1]=*currNums2; 
					}
				}
				numsCount++; 
				currNums2++; 
			}
		}
	}
	dump(mediansNums, 2); 
ans: 
	return (double) (mediansNums[0]+mediansNums[1])/2; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
	{
		int a1[]={0,0}; 
		int n1=sizeof(a1)/sizeof(a1[0]); 
		dump(a1, n1); 
		int a2[]={0,0}; 
		int n2=sizeof(a2)/sizeof(a2[0]); 
		dump(a2, n2); 
		printf("findMedianSortedArrays(%f)\n", findMedianSortedArrays(a1, n1, a2, n2)); 
	}
#if 0
	{
		int a1[]={1,3,5,7}; 
		int n1=sizeof(a1)/sizeof(a1[0]); 
		dump(a1, n1); 
		int a2[]={2,4,6}; 
		int n2=sizeof(a2)/sizeof(a2[0]); 
		dump(a2, n2); 
		printf("findMedianSortedArrays(%f)\n", findMedianSortedArrays(a1, n1, a2, n2)); 
	}
	{
		int a1[]={1}; 
		int n1=sizeof(a1)/sizeof(a1[0]); 
		dump(a1, n1); 
		int a2[]={6}; 
		int n2=sizeof(a2)/sizeof(a2[0]); 
		dump(a2, n2); 
		printf("findMedianSortedArrays(%f)\n", findMedianSortedArrays(a1, n1, a2, n2)); 
	}
#endif
	return 0; 
}
