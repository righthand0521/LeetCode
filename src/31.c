#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void reverse(int *nums, int left, int right) {
    while (left < right) {
        swap(nums + left, nums + right);
        left++;
        right--;
    }
}
void nextPermutation(int *nums, int numsSize) {
    int i, j;
    for (i = numsSize - 2; i >= 0; --i) {
        if (nums[i] < nums[i + 1]) {
            break;
        }
    }
    if (i < 0) {
        reverse(nums, 0, numsSize - 1);
    } else {
        for (j = numsSize - 1; j > i; --j) {
            if (nums[j] > nums[i]) {
                break;
            }
        }
        swap(nums + i, nums + j);
        reverse(nums, i + 1, numsSize - 1);
    }
}

int main(int argc, char **argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{1, 2, 3}, 3}, {{3, 2, 1}, 3}, {{1, 1, 5}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,2,3]
     *  Output: [1,3,2]
     *
     *  Input: nums = [3,2,1]
     *  Output: [1,2,3]
     *
     *  Input: nums = [1,1,5]
     *  Output: [1,5,1]
     */

    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        nextPermutation(testCase[i].nums, testCase[i].numsSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
