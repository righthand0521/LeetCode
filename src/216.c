#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtracking(int k, int n, int* returnSize, int** returnColumnSizes, int start, int* combine, int* combineSize,
                  int** answer) {
    int* pTmp = NULL;
    if ((*combineSize) > k) {
        return;
    } else if (n < 0) {
        return;
    } else if (((*combineSize) == k) && (n == 0)) {
        pTmp = (int*)malloc(k * sizeof(int));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, (k * sizeof(int)));
        memcpy(pTmp, combine, (k * sizeof(int)));
        answer[(*returnSize)] = pTmp;
        (*returnColumnSizes)[(*returnSize)] = k;
        (*returnSize)++;
        return;
    }

    // Only numbers 1 through 9 are used.
    int i;
    for (i = start; i < 10; ++i) {
        combine[(*combineSize)++] = i;
        backtracking(k, n - i, returnSize, returnColumnSizes, i + 1, combine, combineSize, answer);
        (*combineSize)--;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

#define MAX_RETURN_SIZE (10001)
    pRetVal = (int**)malloc(MAX_RETURN_SIZE * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    (*returnColumnSizes) = (int*)malloc(MAX_RETURN_SIZE * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    int maxCombineSize = k + 1;
    int* combine = (int*)malloc(maxCombineSize * sizeof(int));
    int combineSize = 0;
    if (combine == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(combine, 0, (maxCombineSize * sizeof(int)));
    backtracking(k, n, returnSize, returnColumnSizes, 1, combine, &combineSize, pRetVal);
    free(combine);
    combine = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int k;
        int n;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{3, 7, 0, NULL}, {3, 9, 0, NULL}, {4, 1, 0, NULL}, {2, 18, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: k = 3, n = 7
     *  Output: [[1,2,4]]
     *
     *  Input: k = 3, n = 9
     *  Output: [[1,2,6],[1,3,5],[2,3,4]]
     *
     *  Input: k = 4, n = 1
     *  Output: []
     *
     *  Input: k = 2, n = 18
     *  Output: []
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: k = %d, n = %d\n", testCase[i].k, testCase[i].n);

        pAnswer =
            combinationSum3(testCase[i].k, testCase[i].n, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
