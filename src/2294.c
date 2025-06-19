#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int partitionArray(int* nums, int numsSize, int k) {
    int retVal = 1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int minValue = nums[0];
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] - minValue > k) {
            retVal++;
            minValue = nums[i];
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
    } testCase[] = {{{3, 6, 1, 2, 5}, 5, 2}, {{1, 2, 3}, 3, 1}, {{2, 2, 4, 5}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [3,6,1,2,5], k = 2
     *  Output: 2
     *
     *  Input: nums = [1,2,3], k = 1
     *  Output: 2
     *
     *  Input: nums = [2,2,4,5], k = 0
     *  Output: 3
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = partitionArray(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
