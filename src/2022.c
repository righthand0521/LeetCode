#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** construct2DArray(int* original, int originalSize, int m, int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (originalSize != (m * n)) {
        return pRetVal;
    }

    (*returnColumnSizes) = (int*)malloc(m * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (m * sizeof(int)));

    pRetVal = (int**)malloc(m * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    int originalIndex = 0;
    int x, y;
    for (x = 0; x < m; ++x) {
        pRetVal[x] = (int*)malloc(n * sizeof(int));
        if (pRetVal[x] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int i = 0; i < x; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[x], 0, (n * sizeof(int)));
        for (y = 0; y < n; ++y) {
            pRetVal[x][y] = original[originalIndex++];
        }
        (*returnColumnSizes)[x] = n;
    }
    (*returnSize) = m;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        int original[MAX_SIZE];
        int originalSize;
        int m;
        int n;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{1, 2, 3, 4}, 4, 2, 2, 0, NULL}, {{1, 2, 3}, 3, 1, 3, 0, NULL}, {{1, 2}, 2, 1, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: original = [1,2,3,4], m = 2, n = 2
     *  Output: [[1,2],[3,4]]
     *
     *  Input: original = [1,2,3], m = 1, n = 3
     *  Output: [[1,2,3]]
     *
     *  Input: original = [1,2], m = 1, n = 1
     *  Output: []
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: original =  [");
        for (j = 0; j < testCase[i].originalSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].original[j]);
        }
        printf("], m = %d, n = %d\n", testCase[i].m, testCase[i].n);

        pAnswer = construct2DArray(testCase[i].original, testCase[i].originalSize, testCase[i].m, testCase[i].n,
                                   &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
