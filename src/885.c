#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** spiralMatrixIII(int rows, int cols, int rStart, int cStart, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int**)malloc(rows * cols * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(rows * cols * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    // East, South, West, North
    const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int idx = 0;
    int retValSize = (*returnSize);
    int i, j;
    int step;
    for (step = 1; retValSize < rows * cols;) {
        for (i = 0; i < 2; ++i) {
            for (j = 0; j < step; ++j) {
                if ((rStart >= 0) && (rStart < rows) && (cStart >= 0) && (cStart < cols)) {
                    pRetVal[(*returnSize)] = (int*)malloc(2 * sizeof(int));
                    if (pRetVal[(*returnSize)] == NULL) {
                        perror("malloc");
                        for (i = 0; i < (*returnSize); ++i) {
                            free(pRetVal[i]);
                            pRetVal[i] = NULL;
                        }
                        free(pRetVal);
                        pRetVal = NULL;
                        free((*returnColumnSizes));
                        (*returnColumnSizes) = NULL;
                        (*returnSize) = 0;
                        return pRetVal;
                    }
                    memset(pRetVal[(*returnSize)], 0, (2 * sizeof(int)));
                    (*returnColumnSizes)[(*returnSize)] = 2;

                    pRetVal[(*returnSize)][0] = rStart;
                    pRetVal[(*returnSize)][1] = cStart;
                    (*returnSize) += 1;
                }
                rStart += directions[idx][0];
                cStart += directions[idx][1];
            }
            idx = (idx + 1) % 4;
        }
        ++step;
        retValSize = (*returnSize);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int rows;
        int cols;
        int rStart;
        int cStart;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{1, 4, 0, 0, 0, NULL}, {5, 6, 1, 4, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rows = 1, cols = 4, rStart = 0, cStart = 0
     *  Output: [[0,0],[0,1],[0,2],[0,3]]
     *
     *  Input: rows = 5, cols = 6, rStart = 1, cStart = 4
     *  Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],
     *  [4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rows = %d, cols = %d, rStart = %d, cStart = %d\n", testCase[i].rows, testCase[i].cols,
               testCase[i].rStart, testCase[i].cStart);

        pAnswer = spiralMatrixIII(testCase[i].rows, testCase[i].cols, testCase[i].rStart, testCase[i].cStart,
                                  &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
