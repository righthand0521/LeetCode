#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int countValidPairs(int* nums, int numsSize, int threshold) {
    int retVal = 0;

    int index = 0;
    while (index < numsSize - 1) {
        // If a valid pair is found, skip both numbers.
        if (nums[index + 1] - nums[index] <= threshold) {
            retVal += 1;
            index += 1;
        }
        index += 1;
    }

    return retVal;
}
int minimizeMax(int* nums, int numsSize, int p) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int middle;
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    while (left < right) {
        middle = left + (right - left) / 2;
        // If there are enough pairs, look for a smaller threshold.Otherwise, look for a larger threshold.
        if (countValidPairs(nums, numsSize, middle) >= p) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int p;
    } testCase[] = {{{10, 1, 2, 7, 1, 3}, 6, 2}, {{4, 2, 1, 2}, 4, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,1,2,7,1,3], p = 2
     *  Output: 1
     *
     *  Input: nums = [4,2,1,2], p = 1
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], p = %d\n", testCase[i].p);

        answer = minimizeMax(testCase[i].nums, testCase[i].numsSize, testCase[i].p);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
