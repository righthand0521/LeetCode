#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int findMaxK(int* nums, int numsSize) {
    int retVal = -1;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int left = 0;
    int right = numsSize - 1;
    while (left < right) {
        if ((-nums[left]) == nums[right]) {
            retVal = nums[right];
            break;
        } else if ((-nums[left]) > nums[right]) {
            left += 1;
        } else if ((-nums[left]) < nums[right]) {
            right -= 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{-1, 2, -3, 3}, 4}, {{-1, 10, 6, 7, -7, 1}, 6}, {{-10, 8, 6, 7, -2, -3}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [-1,2,-3,3]
     *  Output: 3
     *
     *  Input: nums = [-1,10,6,7,-7,1]
     *  Output: 7
     *
     *  Input: nums = [-10,8,6,7,-2,-3]
     *  Output: -1
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = findMaxK(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
