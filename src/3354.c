#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countValidSelections(int* nums, int numsSize) {
    int retVal = 0;

    int left = 0;
    int right = 0;
    for (int i = 0; i < numsSize; i++) {
        right += nums[i];
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            if ((left - right >= 0) && (left - right <= 1)) {
                retVal++;
            }
            if ((right - left) >= 0 && (right - left <= 1)) {
                retVal++;
            }
        } else {
            left += nums[i];
            right -= nums[i];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 0, 2, 0, 3}, 5}, {{2, 3, 4, 0, 4, 1, 0}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,0,2,0,3]
     *  Output: 2
     *
     *  Input: nums = [2,3,4,0,4,1,0]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = countValidSelections(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
