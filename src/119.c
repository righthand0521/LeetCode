#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc((rowIndex + 1) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((rowIndex + 1) * sizeof(int)));

    int row, col;
    for (row = 0; row < rowIndex; ++row) {
        pRetVal[row] = 1;
        for (col = row; col > 0; --col) {
            pRetVal[col] += pRetVal[col - 1];
        }
    }
    pRetVal[rowIndex] = 1;
    (*returnSize) = rowIndex + 1;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int rowIndex;
    } testCase[] = {{3}, {0}, {1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rowIndex = 3
     *  Output: [1,3,3,1]
     *
     *  Input: rowIndex = 0
     *  Output: [1]
     *
     *  Input: rowIndex = 1
     *  Output: [1,1]
     */

    int* pAnswer = NULL;
    int returnSize = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rowIndex  = %d\n", testCase[i].rowIndex);

        pAnswer = getRow(testCase[i].rowIndex, &returnSize);
        printf("Output: [");
        for (j = 0; j < returnSize; ++j) {
            printf("%d%s", pAnswer[j], (j == returnSize - 1 ? "" : ","));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        returnSize = 0;
    }

    return EXIT_SUCCESS;
}
