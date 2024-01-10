#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtracking(int cur, int n, int k, int** ans, int* ansSize, int* temp, int* tempSize) {
    if ((*tempSize) + (n - cur + 1) < k) {
        return;
    }

    if ((*tempSize) == k) {
        int* tmp = malloc(sizeof(int) * k);
        for (int i = 0; i < k; i++) {
            tmp[i] = temp[i];
        }
        ans[(*ansSize)++] = tmp;
        return;
    }

    temp[(*tempSize)++] = cur;
    backtracking(cur + 1, n, k, ans, ansSize, temp, tempSize);
    (*tempSize)--;
    backtracking(cur + 1, n, k, ans, ansSize, temp, tempSize);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (int**)malloc(10001 * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int tempSize = 0;
    int* temp = malloc(k * sizeof(int));
    if (temp == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }

    backtracking(1, n, k, pRetVal, returnSize, temp, &tempSize);

    int i;
    (*returnColumnSizes) = (int*)malloc(sizeof(int) * (*returnSize));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        free(temp);
        temp = NULL;
        for (i = 0; i < (*returnSize); ++i) {
            free(pRetVal[i]);
            pRetVal[i] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); i++) {
        (*returnColumnSizes)[i] = k;
    }

    free(temp);
    temp = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int k;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{4, 2, 0, NULL}, {1, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, k = 2
     *  Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
     *
     *  Input: n = 1, k = 1
     *  Output: [[1]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, k = %d\n", testCase[i].n, testCase[i].k);

        pAnswer = combine(testCase[i].n, testCase[i].k, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
