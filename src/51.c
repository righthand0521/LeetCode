#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateBoard(int n, int* pQueens, char*** pRetVal, int* returnSize) {
    pRetVal[(*returnSize)] = (char**)malloc(n * sizeof(char*));
    if (pRetVal[(*returnSize)] == NULL) {
        perror("malloc");
        return;
    }

    int i, j;
    for (i = 0; i < n; i++) {
        pRetVal[(*returnSize)][i] = (char*)malloc((n + 1) * sizeof(char));
        if (pRetVal[(*returnSize)][i] == NULL) {
            perror("malloc");
            return;
        }
        for (j = 0; j < n; j++) {
            pRetVal[(*returnSize)][i][j] = '.';
        }
        pRetVal[(*returnSize)][i][pQueens[i]] = 'Q';
        pRetVal[(*returnSize)][i][n] = 0;
    }
}
void backtrack(int n, int row, int* pQueens, int* pColumns, int* pDiagonals1, int* pDiagonals2, char*** pRetVal,
               int* returnSize) {
    if (row == n) {
        generateBoard(n, pQueens, pRetVal, returnSize);
        (*returnSize) += 1;
        return;
    }

    int diagonal1, diagonal2;
    int i;
    for (i = 0; i < n; i++) {
        if (pColumns[i] == true) {
            continue;
        }

        diagonal1 = row - i + n - 1;
        if (pDiagonals1[diagonal1] == true) {
            continue;
        }

        diagonal2 = row + i;
        if (pDiagonals2[diagonal2] == true) {
            continue;
        }

        pQueens[row] = i;
        pColumns[i] = true;
        pDiagonals1[diagonal1] = true;
        pDiagonals2[diagonal2] = true;
        backtrack(n, row + 1, pQueens, pColumns, pDiagonals1, pDiagonals2, pRetVal, returnSize);
        pQueens[row] = -1;
        pColumns[i] = false;
        pDiagonals1[diagonal1] = false;
        pDiagonals2[diagonal2] = false;
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;
    pRetVal = (char***)malloc(501 * sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int queens[n];
    memset(queens, -1, sizeof(queens));
    int columns[n];
    memset(columns, 0, sizeof(columns));
    int diagonals1[n + n];
    memset(diagonals1, 0, sizeof(diagonals1));
    int diagonals2[n + n];
    memset(diagonals2, 0, sizeof(diagonals2));

    backtrack(n, 0, queens, columns, diagonals1, diagonals2, pRetVal, returnSize);

    int i, j;
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (i = 0; i < (*returnSize); ++i) {
            for (j = 0; j < n; ++j) {
                free(pRetVal[i][j]);
                pRetVal[i][j] = NULL;
            }
            free(pRetVal[i]);
            pRetVal[i] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); i++) {
        (*returnColumnSizes)[i] = n;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        int n;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{4, 0, NULL}, {1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4
     *  Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
     *
     *  Input: n = 1
     *  Output: [["Q"]]
     */

    char*** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = solveNQueens(testCase[i].n, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                if (pAnswer[j][k]) {
                    free(pAnswer[j][k]);
                    pAnswer[j][k] = NULL;
                }
            }
            if (pAnswer[j]) {
                free(pAnswer[j]);
                pAnswer[j] = NULL;
            }
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
