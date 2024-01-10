#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = n;
    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));
    //
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    int i, j;
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc((*returnSize) * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnSize) * sizeof(int)));
        (*returnColumnSizes)[i] = (*returnSize);
    }

    /*
     *  (top,left)                              (top,right)
     *      +---------------------------------------+
     *      | 01(111) | 02(112) | 03(113) | 04(114) |
     *      | 12(142) | 13(211) | 14(212) | 05(121) |
     *      | 11(141) | 16(231) | 15(221) | 06(122) |
     *      | 10(133) | 09(132) | 08(131) | 07(123) |
     *      +---------------------------------------+
     * (down,left)                             (down,right)
     */
    int left = 0;
    int right = n - 1;
    int top = 0;
    int down = n - 1;
    int num = 1;
    int row, col;
    while ((left <= right) && (top <= down)) {
        for (col = left; col < right + 1; ++col) {
            pRetVal[top][col] = num;
            ++num;
        }

        for (row = top + 1; row < down + 1; ++row) {
            pRetVal[row][right] = num;
            ++num;
        }

        if ((left < right) && (top < down)) {
            for (col = right - 1; col > left; --col) {
                pRetVal[down][col] = num;
                ++num;
            }

            for (row = down; row > top; --row) {
                pRetVal[row][left] = num;
                ++num;
            }
        }

        ++left;
        --right;
        ++top;
        --down;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{3, 0, NULL}, {1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: [[1,2,3],[8,9,4],[7,6,5]]
     *
     *  Input: n = 1
     *  Output: [[1]]
     */

    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = generateMatrix(testCase[i].n, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
