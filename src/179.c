#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    /* Example
     *  43243 432
     *  43243: 43243000 +   432 = 43243432
     *    432: 43200000 + 43243 = 43243243
     *
     *  432 43200
     *    432: 43200000 + 43200 = 43243200
     *  43200: 43200000 +   432 = 43200432
     */
    long digits1 = 10;
    while (digits1 <= *(int*)n1) {
        digits1 *= 10;
    }
    long digits2 = 10;
    while (digits2 <= *(int*)n2) {
        digits2 *= 10;
    }
    long comp1 = (*(int*)n2) * digits1 + (*(int*)n1);
    long comp2 = (*(int*)n1) * digits2 + (*(int*)n2);

    return (comp1 > comp2);
}
char* largestNumber(int* nums, int numsSize) {
    char* pRetVal = NULL;

    qsort(nums, numsSize, sizeof(int), compareInteger);

    // Input: nums = [0, 0], Output: "0".
    if (nums[0] == 0) {
        pRetVal = (char*)calloc(2, sizeof(char));
        if (pRetVal == NULL) {
            perror("calloc");
            return pRetVal;
        }
        pRetVal[0] = '0';

        return pRetVal;
    }

    // 0 <= nums[i] <= 10^9.
    int returnSize = numsSize * 10 + 1;
    pRetVal = (char*)calloc(returnSize, sizeof(char));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }

    int idx = 0;
    int i;
    for (i = 0; i < numsSize; ++i) {
        idx += snprintf(pRetVal + idx, returnSize - idx - 1, "%d", nums[i]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{10, 2}, 2}, {{3, 30, 34, 5, 9}, 5}, {{432, 43243}, 2}, {{999999991, 9}, 2}, {{0, 0}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [10,2]
     *  Output: "210"
     *
     *  Input: nums = [3,30,34,5,9]
     *  Output: "9534330"
     *
     *  Input: nums = [432, 43243]
     *  Output: "43243432"
     *
     *  Input: nums = [999999991, 9]
     *  Output: "9999999991"
     *
     *  Input: nums = [0, 0]
     *  Output: "0"
     */

    char* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        pAnswer = largestNumber(testCase[i].nums, testCase[i].numsSize);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
