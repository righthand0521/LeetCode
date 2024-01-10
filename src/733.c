#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int** pImage, int sr, int sc, int color, int oriColor, int row, int col) {
    if ((sr < 0) || (sr >= row)) {
        return;
    } else if ((sc < 0) || (sc >= col)) {
        return;
    }

    if (pImage[sr][sc] != oriColor) {
        return;
    }
    pImage[sr][sc] = color;
    dfs(pImage, sr - 1, sc, color, oriColor, row, col);
    dfs(pImage, sr + 1, sc, color, oriColor, row, col);
    dfs(pImage, sr, sc - 1, color, oriColor, row, col);
    dfs(pImage, sr, sc + 1, color, oriColor, row, col);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** floodFill(int** image, int imageSize, int* imageColSize, int sr, int sc, int color, int* returnSize,
                int** returnColumnSizes) {
    int** pRetVal = NULL;

    int i, j;

    // malloc return value
    (*returnSize) = imageSize;
    (*returnColumnSizes) = (int*)malloc((imageColSize[0]) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        (*returnColumnSizes)[i] = imageColSize[i];
    }
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (int*)malloc(((*returnColumnSizes)[i]) * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            pRetVal = NULL;
            (*returnSize) = 0;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, ((*returnColumnSizes)[i]) * sizeof(int));
        memcpy(pRetVal[i], image[i], ((*returnColumnSizes)[i]) * sizeof(int));
    }

    //
    int oriColor = image[sr][sc];
    if (oriColor == color) {
        return pRetVal;
    }
    dfs(pRetVal, sr, sc, color, oriColor, (*returnSize), (*returnColumnSizes)[0]);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (50)
    struct testCaseType {
        int image[MAX_SIZE][MAX_SIZE];
        int imageSize;
        int imageColSize;
        int sr;
        int sc;
        int color;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 1, 1}, {1, 1, 0}, {1, 0, 1}}, 3, 3, 1, 1, 2, 0, NULL},
                    {{{0, 0, 0}, {0, 0, 0}}, 2, 3, 0, 0, 0, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pMatrix = NULL;
    int* pMatrixCol = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        pMatrixCol = malloc(testCase[i].imageSize * sizeof(int));
        if (pMatrixCol == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        pMatrix = malloc(testCase[i].imageSize * sizeof(*pMatrix));
        if (pMatrix == NULL) {
            perror("malloc");
            free(pMatrixCol);
            pMatrixCol = NULL;
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].imageSize; ++j) {
            pMatrixCol[j] = testCase[i].imageColSize;
            pMatrix[j] = malloc(pMatrixCol[j] * sizeof(*pMatrix[j]));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                free(pMatrixCol);
                pMatrixCol = NULL;
                for (k = 0; k < j; ++k) {
                    free(pMatrix[k]);
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, pMatrixCol[j] * sizeof(*pMatrix[j]));
        }
        for (j = 0; j < testCase[i].imageSize; ++j) {
            for (k = 0; k < testCase[i].imageColSize; ++k) {
                pMatrix[j][k] = testCase[i].image[j][k];
            }
        }
        printf("Input: image = [");
        for (j = 0; j < testCase[i].imageSize; ++j) {
            printf("[");
            for (k = 0; k < testCase[i].imageColSize; ++k) {
                printf("%d%s", pMatrix[j][k], (k == (testCase[i].imageColSize - 1) ? "" : ","));
            }
            printf("%s", (j == (testCase[i].imageSize - 1) ? "]" : "],"));
        }
        printf("], sr = %d, sc = %d, color = %d\n", testCase[i].sr, testCase[i].sc, testCase[i].color);

        pAnswer = floodFill(pMatrix, testCase[i].imageSize, pMatrixCol, testCase[i].sr, testCase[i].sc,
                            testCase[i].color, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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

        free(pMatrixCol);
        pMatrixCol = NULL;
        for (j = 0; j < testCase[i].imageSize; ++j) {
            free(pMatrix[j]);
        }
        free(pMatrix);
        pMatrix = NULL;

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
