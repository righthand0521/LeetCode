#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(int* nums, int numsSize, int target) {
    int retVal = -1;

    int mid = 0;
    int low = 0;
    int high = numsSize - 1;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (nums[mid] == target) {
            retVal = mid;
            break;
        }

        if (nums[mid] > target) {
            high = mid - 1;
        } else if (nums[mid] < target) {
            low = mid + 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{-1, 0, 3, 5, 9, 12}, 6, 9},
                    {{-1, 0, 3, 5, 9, 12}, 6, 2},
                    {{5}, 1, 5},
                    {{5}, 1, 2},
                    {{2, 5}, 2, 2},
                    {{2, 5}, 2, 5},
                    {{2, 5}, 2, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-1,0,3,5,9,12], target = 9
     *  Output: 4
     *
     *  Input: nums = [-1,0,3,5,9,12], target = 2
     *  Output: -1
     *
     *  Input: nums = [5], target = 5
     *  Output: 0
     *
     *  Input: nums = [5], target = 2
     *  Output: -1
     *
     *  Input: nums = [2,5], target = 2
     *  Output: 0
     *
     *  Input: nums = [2,5], target = 5
     *  Output: 1
     *
     *  Input: nums = [2,5], target = 0
     *  Output: -1
     */

    int pAnswer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        pAnswer = search(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
