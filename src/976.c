#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // descending order
    return (*(int*)n1 < *(int*)n2);
}
int largestPerimeter(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    int i;
    for (i = 0; i < (numsSize - 2); ++i) {
        if (nums[i] < (nums[i + 1] + nums[i + 2])) {
            retVal = nums[i] + nums[i + 1] + nums[i + 2];
            break;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 1, 2}, 3}, {{1, 2, 1}, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,1,2]
     *  Output: 5
     *
     *  Input: nums = [1,2,1]
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

        answer = largestPerimeter(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
