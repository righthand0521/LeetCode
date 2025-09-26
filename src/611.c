#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int triangleNumber(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);
    for (int i = 0; i < numsSize; ++i) {
        int k = i;
        for (int j = i + 1; j < numsSize; ++j) {
            while ((k + 1 < numsSize) && (nums[k + 1] < nums[i] + nums[j])) {
                ++k;
            }
            retVal += fmax(k - j, 0);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 2, 3, 4}, 4}, {{4, 2, 3, 4}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,2,3,4]
     *  Output: 3
     *
     *  Input: nums = [4,2,3,4]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = triangleNumber(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
