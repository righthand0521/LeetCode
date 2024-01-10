#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int maxFrequency(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    long current = 0;
    int left = 0;
    long target;
    int right;
    for (right = 0; right < numsSize; right++) {
        target = nums[right];
        current += target;

        if ((right - left + 1) * target - current > k) {
            current -= nums[left];
            left++;
        }
    }
    retVal = numsSize - left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 2, 4}, 3, 5}, {{1, 4, 8, 13}, 4, 5}, {{3, 9, 6}, 3, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,4], k = 5
     *  Output: 3
     *
     *  Input: nums = [1,4,8,13], k = 5
     *  Output: 2
     *
     *  Input: nums = [3,9,6], k = 2
     *  Output: 1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = maxFrequency(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
