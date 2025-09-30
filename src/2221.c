#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int triangularSum(int* nums, int numsSize) {
    int retVal = 0;

    int* current = (int*)malloc(numsSize * sizeof(int));
    if (current == NULL) {
        perror("malloc");
        return retVal;
    }
    memcpy(current, nums, numsSize * sizeof(int));
    int currentSize = numsSize;

    int* newNums = (int*)malloc(numsSize * sizeof(int));
    if (newNums == NULL) {
        perror("malloc");
        free(current);
        return retVal;
    }
    while (currentSize > 1) {
        for (int i = 0; i < currentSize - 1; ++i) {
            newNums[i] = (current[i] + current[i + 1]) % 10;
        }
        currentSize--;
        memcpy(current, newNums, sizeof(int) * currentSize);
    }
    retVal = current[0];

    //
    free(current);
    free(newNums);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3, 4, 5}, 5}, {{5}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3,4,5]
     *  Output: 8
     *
     *  Input: nums = [5]
     *  Output: 5
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = triangularSum(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
