#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
int minOperations(int* nums, int numsSize) {
    int retVal = 0;

    int numsSort[numsSize];
    memset(numsSort, 0, sizeof(numsSort));
    memcpy(numsSort, nums, sizeof(numsSort));
    qsort(numsSort, numsSize, sizeof(int), compareInteger);

    int numsUiqueSortSize = 0;
    int numsUiqueSort[numsSize];
    memset(numsUiqueSort, 0, sizeof(numsUiqueSort));
    numsUiqueSort[numsUiqueSortSize++] = numsSort[0];
    int i;
    for (i = 1; i < numsSize; ++i) {
        if (numsSort[i] != numsUiqueSort[numsUiqueSortSize - 1]) {
            numsUiqueSort[numsUiqueSortSize++] = numsSort[i];
        }
    }

    retVal = numsSize;
    int count;
    int j = 0;
    for (i = 0; i < numsUiqueSortSize; i++) {
        while ((j < numsUiqueSortSize) && (numsUiqueSort[j] < numsUiqueSort[i] + numsSize)) {
            j++;
        }

        count = j - i;
        retVal = fmin(retVal, numsSize - count);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
    } testCase[] = {{{4, 2, 5, 3}, 4}, {{1, 2, 3, 5, 6}, 5}, {{1, 10, 100, 1000}, 4}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [4,2,5,3]
     *  Output: 0
     *
     *  Input: nums = [1,2,3,5,6]
     *  Output: 1
     *
     *  Input: nums = [1,10,100,1000]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("]\n");

        answer = minOperations(testCase[i].nums, testCase[i].numsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
