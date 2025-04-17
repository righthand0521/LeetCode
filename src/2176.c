#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPairs(int* nums, int numsSize, int k) {
    int retVal = 0;

    for (int i = 0; i < numsSize - 1; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if ((nums[i] == nums[j]) && ((i * j) % k == 0)) {
                retVal++;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{3, 1, 2, 2, 2, 1, 3}, 7, 2}, {{1, 2, 3, 4}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,1,2,2,2,1,3], k = 2
     *  Output: 4
     *
     *  Input: nums = [1,2,3,4], k = 1
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = countPairs(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
