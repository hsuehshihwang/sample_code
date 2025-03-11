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

// Define a struct for storing the hash table entries.
typedef struct {
    int value;
    int index;
} HashEntry;

int hash(int key, int size) {
    return abs(key) % size;
}

// Find the indices of the two numbers that add up to the target.
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int hashSize = numsSize * 2;
    HashEntry* hashTable = (HashEntry*)calloc(hashSize, sizeof(HashEntry));
    
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int hashIndex = hash(complement, hashSize);
        
        // Check if the complement is in the hash table.
        if (hashTable[hashIndex].value == complement) {
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = hashTable[hashIndex].index;
            result[1] = i;
            *returnSize = 2;
            free(hashTable);
            return result;
        }

        // Store the current element in the hash table.
        int currentHashIndex = hash(nums[i], hashSize);
        hashTable[currentHashIndex].value = nums[i];
        hashTable[currentHashIndex].index = i;
    }

    *returnSize = 0;
    free(hashTable);
    return NULL;
}

int main() {
	dbge(); 
    int nums[] = {2, 7, 11, 15};
    int target = 9;
    int returnSize;
    int* result = twoSum(nums, 4, target, &returnSize);

    if (result != NULL) {
        printf("Indices: %d, %d\n", result[0], result[1]);
        free(result);
    } else {
        printf("No solution found.\n");
    }

    // exit(EXIT_SUCCESS);
    return 0;
}


