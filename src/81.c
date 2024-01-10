#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool search(int* nums, int numsSize, int target) {
    bool retVal = false;

    int middle;
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (nums[middle] == target) {
            retVal = true;
            break;
        } else if ((nums[middle] == nums[left]) && (nums[middle] == nums[right])) {
            left += 1;
            right -= 1;

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
    } testCase[] = {{{2, 5, 6, 0, 0, 1, 2}, 7, 0}, {{2, 5, 6, 0, 0, 1, 2}, 7, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,5,6,0,0,1,2], target = 0
     *  Output: true
     *
     *  Input: nums = [2,5,6,0,0,1,2], target = 3
     *  Output: false
     */

    bool answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], target = %d\n", testCase[i].target);

        answer = search(testCase[i].nums, testCase[i].numsSize, testCase[i].target);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
