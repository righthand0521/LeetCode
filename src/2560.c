#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minCapability(int* nums, int numsSize, int k) {
    int retVal = 0;

    int maxNum = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    int possibleThefts;
    int totalHouses = numsSize;
    int middle;
    int left = 1;
    int right = maxNum;
    while (left < right) {
        middle = (left + right) / 2;
        possibleThefts = 0;

        for (int index = 0; index < totalHouses; ++index) {
            if (nums[index] <= middle) {
                possibleThefts += 1;
                index++;  // Skip the next house to maintain the non-adjacent condition
            }
        }

        if (possibleThefts >= k) {
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
        int k;
    } testCase[] = {{{2, 3, 5, 9}, 4, 2}, {{2, 7, 9, 3, 1}, 5, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,5,9], k = 2
     *  Output: 5
     *
     *  Input: nums = [2,7,9,3,1], k = 2
     *  Output: 2
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], k = %d\n", testCase[i].k);

        answer = minCapability(testCase[i].nums, testCase[i].numsSize, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
