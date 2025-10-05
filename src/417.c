#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bfs(int row, int col, bool** ocean, int** heights, int heightsSize, int heightsColSize) {
    if (ocean[row][col] == true) {
        return;
    }
    ocean[row][col] = true;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int bfsQueueSize = heightsSize * heightsColSize;
    int bfsQueue[bfsQueueSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail++] = row * heightsColSize + col;
    while (bfsQueueHead != bfsQueueTail) {
        int row = bfsQueue[bfsQueueHead] / heightsColSize;
        int col = bfsQueue[bfsQueueHead] % heightsColSize;
        bfsQueueHead++;

        for (int i = 0; i < 4; i++) {
            int nextRow = row + directions[i][0];
            int nextCol = col + directions[i][1];
            if ((nextRow < 0) || (nextRow >= heightsSize) || (nextCol < 0) || (nextCol >= heightsColSize)) {
                continue;
            } else if (ocean[nextRow][nextCol] == true) {
                continue;
            }

            if (heights[nextRow][nextCol] >= heights[row][col]) {
                ocean[nextRow][nextCol] = true;
                bfsQueue[bfsQueueTail++] = nextRow * heightsColSize + nextCol;
            }
        }
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {
    int** pRetVal = NULL;

    (*returnSize) = 0;

    bool** pacific = (bool**)malloc(sizeof(bool*) * heightsSize);
    if (pacific == NULL) {
        perror("malloc");
        return pRetVal;
    }
    bool** atlantic = (bool**)malloc(sizeof(bool*) * heightsSize);
    if (atlantic == NULL) {
        perror("malloc");
        free(pacific);
        pacific = NULL;
        return pRetVal;
    }
    for (int i = 0; i < heightsSize; i++) {
        pacific[i] = (bool*)malloc(sizeof(bool) * heightsColSize[0]);
        if (pacific[i] == NULL) {
            perror("malloc");
            goto exit_pacificAtlantic;
        }
        atlantic[i] = (bool*)malloc(sizeof(bool) * heightsColSize[0]);
        if (atlantic[i] == NULL) {
            perror("malloc");
            goto exit_pacificAtlantic;
        }
        memset(pacific[i], 0, sizeof(bool) * heightsColSize[0]);
        memset(atlantic[i], 0, sizeof(bool) * heightsColSize[0]);
    }
    for (int i = 0; i < heightsSize; i++) {
        bfs(i, 0, pacific, heights, heightsSize, heightsColSize[0]);
    }
    for (int j = 1; j < heightsColSize[0]; j++) {
        bfs(0, j, pacific, heights, heightsSize, heightsColSize[0]);
    }
    for (int i = 0; i < heightsSize; i++) {
        bfs(i, heightsColSize[0] - 1, atlantic, heights, heightsSize, heightsColSize[0]);
    }
    for (int j = 0; j < heightsColSize[0] - 1; j++) {
        bfs(heightsSize - 1, j, atlantic, heights, heightsSize, heightsColSize[0]);
    }

    (*returnColumnSizes) = (int*)malloc(sizeof(int) * heightsSize * heightsColSize[0]);
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        goto exit_pacificAtlantic;
    }
    pRetVal = (int**)malloc(sizeof(int*) * heightsSize * heightsColSize[0]);
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_returnColumnSizes;
    }
    for (int i = 0; i < heightsSize; i++) {
        for (int j = 0; j < heightsColSize[0]; j++) {
            if ((pacific[i][j] && atlantic[i][j]) == false) {
                continue;
            }

            pRetVal[(*returnSize)] = (int*)malloc(sizeof(int) * 2);
            if (pRetVal[(*returnSize)] == NULL) {
                perror("malloc");
                goto exit_return;
            }
            (*returnColumnSizes)[(*returnSize)] = 2;
            pRetVal[(*returnSize)][0] = i;
            pRetVal[(*returnSize)][1] = j;
            (*returnSize)++;
        }
        if (pacific[i]) {
            free(pacific[i]);
            pacific[i] = NULL;
        }
        if (atlantic[i]) {
            free(atlantic[i]);
            atlantic[i] = NULL;
        }
    }
    if (pacific) {
        free(pacific);
        pacific = NULL;
    }
    if (atlantic) {
        free(atlantic);
        atlantic = NULL;
    }

    return pRetVal;

exit_return:
    for (int i = 0; i < heightsSize * heightsColSize[0]; i++) {
        if (pRetVal[i]) {
            free(pRetVal[i]);
            pRetVal[i] = NULL;
        }
    }
    if (pRetVal) {
        free(pRetVal);
        pRetVal = NULL;
    }

exit_returnColumnSizes:
    if ((*returnColumnSizes)) {
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
    }

exit_pacificAtlantic:
    for (int i = 0; i < heightsSize; i++) {
        if (pacific[i]) {
            free(pacific[i]);
            pacific[i] = NULL;
        }
        if (atlantic[i]) {
            free(atlantic[i]);
            atlantic[i] = NULL;
        }
    }
    if (pacific) {
        free(pacific);
        pacific = NULL;
    }
    if (atlantic) {
        free(atlantic);
        atlantic = NULL;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int heights[MAX_SIZE][MAX_SIZE];
        int heightsSize;
        int heightsColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}},
                     5,
                     {5, 5, 5, 5, 5},
                     0,
                     NULL},
                    {{{1}}, 1, {1}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
     *  Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
     *
     *  Input: heights = [[1]]
     *  Output: [[0,0]]
     */

    int** pHeights = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].heightsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].heights[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pHeights = (int**)malloc(testCase[i].heightsSize * sizeof(int*));
        if (pHeights == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            pHeights[j] = (int*)malloc(testCase[i].heightsColSize[j] * sizeof(int));
            if (pHeights[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pHeights[k]) {
                        free(pHeights[k]);
                        pHeights[k] = NULL;
                    }
                }
                free(pHeights);
                pHeights = NULL;
                return EXIT_FAILURE;
            }
            memset(pHeights[j], 0, testCase[i].heightsColSize[j] * sizeof(int));
            memcpy(pHeights[j], testCase[i].heights[j], testCase[i].heightsColSize[j] * sizeof(int));
        }
        pAnswer = pacificAtlantic(pHeights, testCase[i].heightsSize, testCase[i].heightsColSize,
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

        for (j = 0; j < testCase[i].heightsSize; ++j) {
            if (pHeights[j]) {
                free(pHeights[j]);
                pHeights[j] = NULL;
            }
        }
        free(pHeights);
        pHeights = NULL;
    }

    return EXIT_SUCCESS;
}
