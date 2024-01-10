#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    (*returnColumnSizes) = (int*)malloc(numRows * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (numRows * sizeof(int)));

    pRetVal = (int**)malloc(numRows * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    int i;
    int row, col;
    for (row = 0; row < numRows; ++row) {
        (*returnColumnSizes)[row] = row + 1;
        pRetVal[row] = (int*)malloc((*returnColumnSizes)[row] * sizeof(int));
        if (pRetVal[row] == NULL) {
            perror("malloc");
            for (i = 0; i < row; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }
        memset(pRetVal[row], 0, ((*returnColumnSizes)[row] * sizeof(int)));

        for (col = 0; col <= row; ++col) {
            if ((col == 0) || (col == row)) {
                pRetVal[row][col] = 1;
            } else {
                pRetVal[row][col] = pRetVal[row - 1][col - 1] + pRetVal[row - 1][col];
            }
        }
    }
    (*returnSize) = numRows;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int numRows;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{5, 0, NULL}, {1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: numRows = 5
     *  Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
     *
     *  Input: numRows = 1
     *  Output: [[1]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: numRows = %d\n", testCase[i].numRows);

        pAnswer = generate(testCase[i].numRows, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
