#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arithmeticTriplets(int* nums, int numsSize, int diff) {
    int retVal = 0;

#define MAX_HASHTABLE_SIZE (200 + 50 + 50 + 4)  // 3 <= nums.length <= 200; 0 <= nums[i] <= 200; 1 <= diff <= 50
    int hashTable[MAX_HASHTABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));

    int i;
    for (i = 0; i < numsSize; ++i) {
        hashTable[nums[i]] = MAX_HASHTABLE_SIZE;  // 0 <= nums[i] <= 200
    }
    for (i = 0; i < numsSize; ++i) {
        if (hashTable[nums[i] + diff] != MAX_HASHTABLE_SIZE) {
            continue;
        }
        if (hashTable[nums[i] + diff + diff] != MAX_HASHTABLE_SIZE) {
            continue;
        }
        retVal += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int diff;
    } testCase[] = {{{0, 1, 4, 6, 7, 10}, 6, 3}, {{4, 5, 6, 7, 8, 9}, 6, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,4,6,7,10], diff = 3
     *  Output: 2
     *
     *  Input: nums = [4,5,6,7,8,9], diff = 2
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], diff = %d\n", testCase[i].diff);

        answer = arithmeticTriplets(testCase[i].nums, testCase[i].numsSize, testCase[i].diff);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
