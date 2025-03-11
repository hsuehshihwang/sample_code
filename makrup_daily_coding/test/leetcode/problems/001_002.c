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
#if 0
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.
Example 1:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:
Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:
Input: nums = [3,3], target = 6
Output: [0,1]
Constraints:
2 <= nums.length <= 10^4
-10^9 <= nums[i] <= 10^9
-10^9 <= target <= 10^9
Only one valid answer exists.
#endif
// psuedo code
#if 0
twoSum(inArray, inArraySize, target, outReturnSize)
#endif
int *pNums=NULL; 
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int comInt(const void*a, const void *b){
	return pNums[*(int*)a]-pNums[*(int*)b]; 
}
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
	int map[numsSize]; 
	for(int i=0; i<numsSize; i++) map[i]=i; 
	int *ans=NULL; 
	*returnSize=2; 
	ans=malloc(sizeof(int)*(*returnSize)); 
	for(int i=0; i<(*returnSize); i++) ans[i]=0; 
	void qsort(void *base, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *));
	pNums=nums; 
	qsort(map, numsSize, sizeof(int), comInt); 
	int left=0, right=numsSize-1; 
	while(left<right){
		if((nums[map[left]]+nums[map[right]])==target){
			ans[0]=map[left]; 
			ans[1]=map[right]; 
			break; 
		}else if((nums[map[left]]+nums[map[right]])<target){
			left++; 
		}else{
			right--; 
		}
	}
	return ans; 
}
int main(int argc, char *argv[]){
	printf("%s@%d: \n", __FUNCTION__, __LINE__); 
#if 1
	{
		int a[]={2,7,11,15}; 
		int n=sizeof(a)/sizeof(a[0]); 
		int t=9; 
		int returnSize=0; 
		dump(a, n); 
		int *ans=twoSum(a, n, t, &returnSize); 
		dump(ans, returnSize); 
		printf("a[%d](%d)+a[%d](%d)=t(%d)\n", ans[0], a[ans[0]], ans[1], a[ans[1]], t); 
	}
	{
		int a[]={3,2,4}; 
		int n=sizeof(a)/sizeof(a[0]); 
		int t=6; 
		int returnSize=0; 
		dump(a, n); 
		int *ans=twoSum(a, n, t, &returnSize); 
		dump(ans, returnSize); 
		printf("a[%d](%d)+a[%d](%d)=t(%d)\n", ans[0], a[ans[0]], ans[1], a[ans[1]], t); 
	}
	{
		int a[]={3,2,95,4,-3}; 
		int n=sizeof(a)/sizeof(a[0]); 
		int t=92; 
		int returnSize=0; 
		dump(a, n); 
		int *ans=twoSum(a, n, t, &returnSize); 
		// dump(ans, returnSize); 
		printf("a[%d](%d)+a[%d](%d)=t(%d)\n", ans[0], a[ans[0]], ans[1], a[ans[1]], t); 
	}
#endif
	{
		int a[]={50000000,3,2,4,50000000}; 
		int n=sizeof(a)/sizeof(a[0]); 
		int t=100000000; 
		int returnSize=0; 
		dump(a, n); 
		int *ans=twoSum(a, n, t, &returnSize); 
		// dump(ans, returnSize); 
		printf("a[%d](%d)+a[%d](%d)=t(%d)\n", ans[0], a[ans[0]], ans[1], a[ans[1]], t); 
	}
#if 0
	{
		int a[]={3,2,3}; 
		int n=sizeof(a)/sizeof(a[0]); 
		int t=6; 
		int returnSize=0; 
		int *ans=twoSum(a, n, t, &returnSize); 
		dump(a, n); 
		dump(ans, returnSize); 
		printf("a[%d](%d)+a[%d](%d)=t(%d)\n", ans[0], a[ans[0]], ans[1], a[ans[1]], t); 
	}
#endif
#if 0
	int a[]={9,7,3,2,1,5,9,8,6}; 
	int n=sizeof(a)/sizeof(a[0]); 
	dump(a, n); 
#endif
	return 0; 
}
