#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    int count = 1;
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (nums[i - 1] == nums[i]) {
            count++;
            continue;
        }

        if (count == 1) {
            retVal = -1;
            return retVal;
        }
        retVal += (count / 3);
        if (count % 3 != 0) {
            retVal += 1;
        }

        count = 1;
    }
    if (count == 1) {
        retVal = -1;
        return retVal;
    }
    retVal += (count / 3);
    if (count % 3 != 0) {
        retVal += 1;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{2, 3, 3, 2, 2, 4, 2, 3, 4}, 9}, {{2, 1, 2, 2, 3, 3}, 6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [2,3,3,2,2,4,2,3,4]
     *  Output: 4
     *
     *  Input: nums = [2,1,2,2,3,3]
     *  Output: -1
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
