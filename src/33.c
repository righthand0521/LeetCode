#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(int* nums, int numsSize, int target) {
    int retVal = -1;

    int middle;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (nums[middle] == target) {
            retVal = middle;
            break;
        } else if (nums[middle] >= nums[left]) {
            if ((target >= nums[left]) && (target < nums[middle])) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        } else {
            if ((target <= nums[right]) && (target > nums[middle])) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int target;
    } testCase[] = {{{4, 5, 6, 7, 0, 1, 2}, 7, 0}, {{4, 5, 6, 7, 0, 1, 2}, 7, 3}, {{1}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,5,6,7,0,1,2], target = 0
     *  Output: 4
     *
     *  Input: nums = [4,5,6,7,0,1,2], target = 3
     *  Output: -1
     *
     *  Input: nums = [1], target = 0
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = search(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
