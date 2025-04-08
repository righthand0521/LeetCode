#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumOperations(int* nums, int numsSize) {
    int retVal = 0;

    int hashTable[128];  // 1 <= nums.length <= 100
    memset(hashTable, 0, sizeof(hashTable));

    for (int i = numsSize - 1; i >= 0; --i) {
        if (hashTable[nums[i]] == 1) {
            retVal = i / 3 + 1;
            break;
        }
        hashTable[nums[i]] = 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4, 2, 3, 3, 5, 7}, 9}, {{4, 5, 6, 4, 4}, 5}, {{6, 7, 8, 9}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,2,3,3,5,7]
     *  Output: 2
     *
     *  Input: nums = [4,5,6,4,4]
     *  Output: 2
     *
     *  Input: nums = [6,7,8,9]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minimumOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
