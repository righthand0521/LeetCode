#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findDuplicate(int* nums, int numsSize) {
    int retVal = 0;

    int* pCount = (int*)malloc(numsSize * sizeof(int));
    if (pCount == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(pCount, 0, (numsSize * sizeof(int)));

    int i;
    for (i = 0; i < numsSize; ++i) {
        if (pCount[nums[i]] != 0) {
            retVal = nums[i];
            break;
        }
        pCount[nums[i]]++;
    }
    free(pCount);
    pCount = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 3, 4, 2, 2}, 5}, {{3, 1, 3, 4, 2}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,4,2,2]
     *  Output: 2
     *
     *  nums = [3,1,3,4,2]
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findDuplicate(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
