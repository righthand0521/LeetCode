#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** imageSmoother(int** img, int imgSize, int* imgColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;
    int i, j, x, y;

    int rowSize = imgSize;
    int colSize = imgColSize[0];
    pRetVal = (int**)malloc(rowSize * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    for (i = 0; i < rowSize; ++i) {
        pRetVal[i] = (int*)malloc(colSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], 0, (colSize * sizeof(int)));
    }
    (*returnColumnSizes) = (int*)malloc(rowSize * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j = 0; j < rowSize; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, (rowSize * sizeof(int)));

    int sum, count;
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            sum = 0;
            count = 0;
            for (x = (i - 1); x <= (i + 1); ++x) {
                for (y = (j - 1); y <= (j + 1); ++y) {
                    if (((0 <= x) && (x < rowSize)) && ((0 <= y) && (y < colSize))) {
                        sum += img[x][y];
                        count += 1;
                    }
                }
            }
            pRetVal[i][j] = sum / count;
        }
        (*returnColumnSizes)[i] = colSize;
    }
    (*returnSize) = rowSize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (200)
#define MAX_COLUMN (200)
    struct testCaseType {
        int img[MAX_ROW][MAX_COLUMN];
        int imgSize;
        int imgColSize[MAX_ROW];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}, 3, {3, 3, 3}, 0, NULL},
                    {{{100, 200, 100}, {200, 50, 200}, {100, 200, 100}}, 3, {3, 3, 3}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: img = [[1,1,1],[1,0,1],[1,1,1]]
     *  Output: [[0,0,0],[0,0,0],[0,0,0]]
     *
     *  Input: img = [[100,200,100],[200,50,200],[100,200,100]]
     *  Output: [[137,141,137],[141,138,141],[137,141,137]]
     */

    int** pImg = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: img = [");
        for (j = 0; j < testCase[i].imgSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].imgColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].img[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pImg = (int**)malloc(testCase[i].imgSize * sizeof(int*));
        if (pImg == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].imgSize; ++j) {
            pImg[j] = (int*)malloc(testCase[i].imgColSize[j] * sizeof(int));
            if (pImg[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pImg[k]);
                }
                free(pImg);
                return EXIT_FAILURE;
            }
            memset(pImg[j], 0, (testCase[i].imgColSize[j] * sizeof(int)));
            memcpy(pImg[j], testCase[i].img[j], (testCase[i].imgColSize[j] * sizeof(int)));
        }

        pAnswer = imageSmoother(pImg, testCase[i].imgSize, testCase[i].imgColSize, &testCase[i].returnSize,
                                &(testCase[i].returnColumnSizes));
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
        for (j = 0; j < testCase[i].imgSize; ++j) {
            free(pImg[j]);
            pImg[j] = NULL;
        }
        free(pImg);
        pImg = NULL;
    }

    return EXIT_SUCCESS;
}
