#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    int retVal = 0;

    int rowSize = heightMapSize;
    int colSize = heightMapColSize[0];
    int i, j;

    int maxHeight = 0;
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            maxHeight = fmax(maxHeight, heightMap[i][j]);
        }
    }

    int water[rowSize][colSize];
    memset(water, 0, sizeof(water));
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            water[i][j] = maxHeight;
        }
    }

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueueSize = rowSize * colSize * 8;
    int bfsQueue[bfsQueueSize][2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            if ((i != 0) && (i != rowSize - 1) && (j != 0) && (j != colSize - 1)) {
                continue;
            }

            if (water[i][j] > heightMap[i][j]) {
                water[i][j] = heightMap[i][j];
                bfsQueue[bfsQueueTail][0] = i;
                bfsQueue[bfsQueueTail][1] = j;
                bfsQueueTail++;
            }
        }
    }

    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int x, y, nx, ny;
    while (bfsQueueHead < bfsQueueTail) {
        x = bfsQueue[bfsQueueHead][0];
        y = bfsQueue[bfsQueueHead][1];
        bfsQueueHead++;

        for (i = 0; i < 4; ++i) {
            nx = x + direction[i][0];
            ny = y + direction[i][1];
            if ((nx < 0) || (nx >= rowSize) || (ny < 0) || (ny >= colSize)) {
                continue;
            }

            if ((water[x][y] < water[nx][ny]) && (water[nx][ny] > heightMap[nx][ny])) {
                water[nx][ny] = fmax(water[x][y], heightMap[nx][ny]);
                bfsQueue[bfsQueueTail][0] = nx;
                bfsQueue[bfsQueueTail][1] = ny;
                bfsQueueTail++;
            }
        }
    }

    for (i = 0; i < rowSize; ++i) {
        for (j = 0; j < colSize; ++j) {
            retVal = retVal + water[i][j] - heightMap[i][j];
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int heightMap[MAX_SIZE][MAX_SIZE];
        int heightMapSize;
        int heightMapColSize[MAX_SIZE];
    } testCase[] = {
        {{{1, 4, 3, 1, 3, 2}, {3, 2, 1, 3, 2, 4}, {2, 3, 3, 2, 3, 1}}, 3, {6, 6, 6}},
        {{{3, 3, 3, 3, 3}, {3, 2, 2, 2, 3}, {3, 2, 1, 2, 3}, {3, 2, 2, 2, 3}, {3, 3, 3, 3, 3}}, 5, {5, 5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
     *  Output: 4
     *
     *  Input: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
     *  Output: 10
     */

    int** pHeightMap = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("heightMap = [");
        for (j = 0; j < testCase[i].heightMapSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].heightMapColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].heightMap[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pHeightMap = (int**)malloc(testCase[i].heightMapSize * sizeof(int*));
        if (pHeightMap == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pHeightMap, 0, testCase[i].heightMapSize * sizeof(int*));
        for (j = 0; j < testCase[i].heightMapSize; ++j) {
            pHeightMap[j] = (int*)malloc(testCase[i].heightMapColSize[j] * sizeof(int));
            if (pHeightMap[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pHeightMap[k]);
                    pHeightMap[k] = NULL;
                }
                free(pHeightMap);
                pHeightMap = NULL;
            }
            memset(pHeightMap[j], 0, (testCase[i].heightMapColSize[j] * sizeof(int)));
            memcpy(pHeightMap[j], testCase[i].heightMap[j], (testCase[i].heightMapColSize[j] * sizeof(int)));
        }
        answer = trapRainWater(pHeightMap, testCase[i].heightMapSize, testCase[i].heightMapColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].heightMapSize; ++j) {
            free(pHeightMap[j]);
            pHeightMap[j] = NULL;
        }
        free(pHeightMap);
        pHeightMap = NULL;
    }

    return EXIT_SUCCESS;
}
