#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** rangeAddQueries(int n, int** queries, int queriesSize, int* queriesColSize, int* returnSize,
                      int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int diff[n + 1][n + 1];
    memset(diff, 0, sizeof(diff));
    int row1, col1, row2, col2;
    for (int i = 0; i < queriesSize; ++i) {
        row1 = queries[i][0];
        col1 = queries[i][1];
        row2 = queries[i][2];
        col2 = queries[i][3];
        diff[row1][col1] += 1;
        diff[row2 + 1][col1] -= 1;
        diff[row1][col2 + 1] -= 1;
        diff[row2 + 1][col2 + 1] += 1;
    }

    (*returnColumnSizes) = (int*)malloc(n * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(n * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        pRetVal[i] = (int*)calloc(n, sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("calloc");
            for (int j = 0; j < i; j++) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }
        (*returnColumnSizes)[i] = n;
    }
    (*returnSize) = n;

    int x1, x2, x3;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            x1 = (i == 0) ? (0) : (pRetVal[i - 1][j]);
            x2 = (j == 0) ? (0) : (pRetVal[i][j - 1]);
            x3 = ((i == 0) || (j == 0)) ? (0) : (pRetVal[i - 1][j - 1]);
            pRetVal[i][j] = diff[i][j] + x1 + x2 - x3;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (int)(1e4)
#define MAX_COLUMN (4)
    struct testCaseType {
        int n;
        int queries[MAX_ROW][MAX_COLUMN];
        int queriesSize;
        int queriesColSize[MAX_ROW];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{3, {{1, 1, 2, 2}, {0, 0, 1, 1}}, 2, {4, 4}, 0, NULL}, {2, {{0, 0, 1, 1}}, 1, {4}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
     *  Output: [[1,1,0],[1,2,1],[0,1,1]]
     *
     *  Input: n = 2, queries = [[0,0,1,1]]
     *  Output: [[1,1],[1,1]]
     */

    int** pQueries = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, queries = [", testCase[i].n);
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pQueries[k]);
                }
                free(pQueries);
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, (testCase[i].queriesColSize[j] * sizeof(int)));
            memcpy(pQueries[j], testCase[i].queries[j], (testCase[i].queriesColSize[j] * sizeof(int)));
        }

        pAnswer = rangeAddQueries(testCase[i].n, pQueries, testCase[i].queriesSize, testCase[i].queriesColSize,
                                  &testCase[i].returnSize, &(testCase[i].returnColumnSizes));
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
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            free(pQueries[j]);
            pQueries[j] = NULL;
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
