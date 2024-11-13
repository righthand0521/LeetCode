#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long lowerBound(int* nums, int numsSize, int value) {
    long long retVal = 0;

    int sum;
    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        sum = nums[left] + nums[right];
        // If sum is less than value, add the size of window to result and move to the next index.
        // Otherwise, shift the right pointer backwards, until we get a valid window.
        if (sum < value) {
            retVal += (right - left);
            left++;
        } else {
            right--;
        }
    }

    return retVal;
}
int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
long long countFairPairs(int* nums, int numsSize, int lower, int upper) {
    long long retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    retVal = lowerBound(nums, numsSize, upper + 1) - lowerBound(nums, numsSize, lower);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int lower;
        int upper;
    } testCase[] = {{{0, 1, 7, 4, 4, 5}, 6, 3, 6}, {{1, 7, 9, 2, 5}, 5, 11, 11}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
     *  Output: 6
     *
     *  Input: nums = [1,7,9,2,5], lower = 11, upper = 11
     *  Output: 1
     */

    long long answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], lower = %d, upper = %d\n", testCase[i].lower, testCase[i].upper);

        answer = countFairPairs(testCase[i].nums, testCase[i].numsSize, testCase[i].lower, testCase[i].upper);
        printf("Output: %lld\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
