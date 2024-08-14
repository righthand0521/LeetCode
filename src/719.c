#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int smallestDistancePair(int* nums, int numsSize, int k) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int middle, index, i, j;
    int left = 0;
    int right = nums[numsSize - 1] - nums[0];
    while (left <= right) {
        middle = (left + right) / 2;

        index = 0;
        i = 0;
        for (j = 0; j < numsSize; j++) {
            while (nums[j] - nums[i] > middle) {
                i++;
            }
            index += (j - i);
        }

        if (index >= k) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int k;
    } testCase[] = {{{1, 3, 1}, 3, 1}, {{1, 1, 1}, 3, 2}, {{1, 6, 1}, 3, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,3,1], k = 1
     *  Output: 0
     *
     *  Input: nums = [1,1,1], k = 2
     *  Output: 0
     *
     *  Input: nums = [1,6,1], k = 3
     *  Output: 5
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = smallestDistancePair(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
