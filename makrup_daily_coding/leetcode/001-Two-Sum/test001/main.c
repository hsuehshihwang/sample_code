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


void dump(int *nums, int numsSize){
	printf("nums[%d]: {", numsSize); 
	if(nums){
		for(int i=0; i<numsSize; i++){
			printf("%d%s", nums[i], i==numsSize-1?"":", "); 
		}
	}
	printf("}\n"); 
}

int hash(int _num, int _size){
	return abs(_num%_size); 
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
	*returnSize=2; 
	int *ans=malloc(sizeof(int)*(*returnSize)); 
	int hashTab1Size=numsSize+1; 
	int hashTab2Size=hashTab1Size+1; 
	int hashTab1[hashTab1Size]; 
	int hashTab2[hashTab2Size]; 
	return ans; 
}

int main(int argc, char *argv[]){
	dbge(); 
#if 0
	void hashTest(){
		{
			int num=-5, size=10; 
			dbge("hash(%d, %d): %d", num, size, hash(num, size)); 
		}
		{
			int num=-5, size=3; 
			dbge("hash(%d, %d): %d", num, size, hash(num, size)); 
		}
		{
			int num=35, size=13; 
			dbge("hash(%d, %d): %d", num, size, hash(num, size)); 
		}
		{
			int num=-495, size=71; 
			dbge("hash(%d, %d): %d", num, size, hash(num, size)); 
		}
	}
#endif
	{
		int nums[]={2, 7, 11, 15}; 
		int target=9; 
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0; 
		int *ans=twoSum(nums, numsSize, target, &returnSize); 
		dump(ans, returnSize); 
	}
	{
		int nums[] = {2, 7, 11, 15};
		int target = 9; // Expected output: [0, 1]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {3, 2, 4};
		int target = 6; // Expected output: [1, 2]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}


	{
		int nums[] = {3, 3};
		int target = 6; // Expected output: [0, 1]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {1, 5, 3, 6};
		int target = 9; // Expected output: [1, 3]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {0, 4, 3, 0};
		int target = 0; // Expected output: [0, 3]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {-1, -2, -3, -4, -5};
		int target = -8; // Expected output: [2, 4]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {10, 26, 30, 31, 47, 60};
		int target = 40; // Expected output: [0, 2]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {5, 75, 25};
		int target = 100; // Expected output: [1, 2]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {1, 2, 3, 4, 4};
		int target = 8; // Expected output: [3, 4]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

	{
		int nums[] = {1, 3, 5, 7, 9};
		int target = 10; // Expected output: [1, 3]
		int numsSize=sizeof(nums)/sizeof(nums[0]); 
		int returnSize=0;
		int *ans=twoSum(nums, numsSize, target, &returnSize);
		dump(ans, returnSize); 
	}

    exit(EXIT_SUCCESS);
}

