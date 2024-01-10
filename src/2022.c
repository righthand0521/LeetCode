#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** construct2DArray(int* original, int originalSize, int m, int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;
    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    if (originalSize != (m * n)) {
        return pRetVal;
    }

    (*returnSize) = m;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    int i;
    for (i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = n;
    }

    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }

    i = 0;
    int row = 0;
    int col = 0;
    for (row = 0; row < (*returnSize); ++row) {
        pRetVal[row] = (int*)malloc(((*returnColumnSizes)[row]) * sizeof(int));
        if (pRetVal[row] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (i = 0; i < row; ++i) {
                free(pRetVal[i]);
                pRetVal[i] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[row], 0, ((*returnColumnSizes)[row]) * sizeof(int));

        while (i < originalSize) {
            pRetVal[row][col++] = original[i++];
            if (col == (*returnColumnSizes)[row]) {
                col = 0;
                break;
            }
        }
    }

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
