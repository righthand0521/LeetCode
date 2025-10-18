#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxDistinctElements(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int previous = INT_MIN;
    int current;
    for (int i = 0; i < numsSize; i++) {
        current = fmin(fmax(nums[i] - k, previous + 1), nums[i] + k);
        if (current > previous) {
            retVal += 1;
            previous = current;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 2, 3, 3, 4}, 6, 2}, {{4, 4, 4, 4}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,2,3,3,4], k = 2
     *  Output: 6
     *
     *  Input: nums = [4,4,4,4], k = 1
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxDistinctElements(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
