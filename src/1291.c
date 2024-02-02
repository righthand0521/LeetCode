#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInteger(const void* n1, const void* n2) {
    // ascending order
    return (*(int*)n1 > *(int*)n2);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    /* 10 <= low <= high <= 10^9
     *  9 * 8 / 2 = 36
     */
    int maxReturnSize = 64;
    pRetVal = (int*)malloc(maxReturnSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (maxReturnSize * sizeof(int)));

    // 10 <= low <= high <= 10^9
    int i, j, num;
    for (i = 1; i < 10; ++i) {
        num = i;
        for (j = i + 1; j < 10; ++j) {
            num = 10 * num + j;
            if ((num >= low) && (num <= high)) {
                pRetVal[(*returnSize)++] = num;
            }
        }
    }
    qsort(pRetVal, (*returnSize), sizeof(int), compareInteger);

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int low;
        int high;
        int returnSize;
    } testCase[] = {{100, 300, 0}, {1000, 13000, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: low = 100, high = 300
     *  Output: [123,234]
     *
     *  Input: low = 1000, high = 13000
     *  Output: [1234,2345,3456,4567,5678,6789,12345]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: low  = %d, high = %d\n", testCase[i].low, testCase[i].high);

        pAnswer = sequentialDigits(testCase[i].low, testCase[i].high, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
