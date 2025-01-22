#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** highestPeak(int** isWater, int isWaterSize, int* isWaterColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    //
    int isWaterRows = isWaterSize;
    int isWaterCols = isWaterColSize[0];

    //
    (*returnColumnSizes) = (int*)calloc(isWaterRows, sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("calloc");
        return pRetVal;
    }
    pRetVal = (int**)malloc(isWaterRows * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (int i = 0; i < isWaterRows; ++i) {
        pRetVal[i] = (int*)malloc(isWaterCols * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            for (int j = 0; j < i; ++j) {
                if (pRetVal[j]) {
                    free(pRetVal[j]);
                    pRetVal[j] = NULL;
                }
            }
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(pRetVal[i], -1, isWaterCols * sizeof(int));
        (*returnColumnSizes)[i] = isWaterCols;
    }
    (*returnSize) = isWaterRows;

    //
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueueSize = isWaterRows * isWaterCols + 1;
    int bfsQueue[bfsQueueSize][2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    for (int x = 0; x < isWaterRows; x++) {
        for (int y = 0; y < isWaterCols; y++) {
            if (isWater[x][y] == 1) {
                bfsQueue[bfsQueueTail][0] = x;
                bfsQueue[bfsQueueTail][1] = y;
                bfsQueueTail++;
                pRetVal[x][y] = 0;
            }
        }
    }

    //
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int row, col, bfsQueueCount, currentCellX, currentCellY, dir;
    int heightOfNextLayer = 1;
    while (bfsQueueHead < bfsQueueTail) {
        bfsQueueCount = bfsQueueTail - bfsQueueHead;
        for (int i = 0; i < bfsQueueCount; i++) {
            currentCellX = bfsQueue[bfsQueueHead][0];
            currentCellY = bfsQueue[bfsQueueHead][1];
            bfsQueueHead++;

            for (dir = 0; dir < 4; ++dir) {
                row = currentCellX + direction[dir][0];
                col = currentCellY + direction[dir][1];
                if ((row < 0) || (row >= isWaterRows) || (col < 0) || (col >= isWaterCols)) {
                    continue;
                } else if (pRetVal[row][col] != -1) {
                    continue;
                }
                pRetVal[row][col] = heightOfNextLayer;
                bfsQueue[bfsQueueTail][0] = row;
                bfsQueue[bfsQueueTail][1] = col;
                bfsQueueTail++;
            }
        }
        heightOfNextLayer++;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int isWater[MAX_SIZE][MAX_SIZE];
        int isWaterSize;
        int isWaterColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{0, 1}, {0, 0}}, 2, {2, 2}, 0, NULL}, {{{0, 0, 1}, {1, 0, 0}, {0, 0, 0}}, 3, {3, 3, 3}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: isWater = [[0,1],[0,0]]
     *  Output: [[1,0],[2,1]]
     *
     *  Input: isWater = [[0,0,1],[1,0,0],[0,0,0]]
     *  Output: [[1,1,0],[0,1,1],[1,2,2]]
     */

    int** pIsWater = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: isWater =  [");
        for (j = 0; j < testCase[i].isWaterSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].isWaterColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].isWater[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pIsWater = (int**)malloc(testCase[i].isWaterSize * sizeof(int*));
        if (pIsWater == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].isWaterSize; ++j) {
            pIsWater[j] = (int*)malloc(testCase[i].isWaterColSize[j] * sizeof(int));
            if (pIsWater[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pIsWater[k]) {
                        free(pIsWater[k]);
                        pIsWater[k] = NULL;
                    }
                }
                free(pIsWater);
                pIsWater = NULL;
                return EXIT_FAILURE;
            }
            memset(pIsWater[j], 0, testCase[i].isWaterColSize[j] * sizeof(int));
            memcpy(pIsWater[j], testCase[i].isWater[j], testCase[i].isWaterColSize[j] * sizeof(int));
        }
        pAnswer = highestPeak(pIsWater, testCase[i].isWaterSize, testCase[i].isWaterColSize, &testCase[i].returnSize,
                              &testCase[i].returnColumnSizes);
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

        for (j = 0; j < testCase[i].isWaterSize; ++j) {
            if (pIsWater[j]) {
                free(pIsWater[j]);
                pIsWater[j] = NULL;
            }
        }
        free(pIsWater);
        pIsWater = NULL;
    }

    return EXIT_SUCCESS;
}
