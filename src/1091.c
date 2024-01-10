#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortestPathBinaryMatrix(int** grid, int gridSize, int* gridColSize) {
    int retVal = -1;

    if (grid[0][0] == 1) {
        return retVal;
    }

    int visitDistance[gridSize][gridSize];
    memset(visitDistance, 0, sizeof(visitDistance));
    int i, j;
    for (i = 0; i < gridSize; ++i) {
        for (j = 0; j < gridSize; ++j) {
            visitDistance[i][j] = INT_MAX;
        }
    }
    visitDistance[0][0] = 1;

    int direction[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int directionSize = sizeof(direction) / sizeof(direction[0]);

    int bfsQueue[gridSize * gridSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueHead++] = 0 * gridSize + 0;

    int row, col;
    int x, y;
    while (bfsQueueHead > bfsQueueTail) {
        x = bfsQueue[bfsQueueTail] / gridSize;
        y = bfsQueue[bfsQueueTail] % gridSize;
        ++bfsQueueTail;
        if ((x == gridSize - 1) && (y == gridSize - 1)) {
            retVal = visitDistance[x][y];
            break;
        }

        for (i = 0; i < directionSize; ++i) {
            row = x + direction[i][0];
            col = y + direction[i][1];
            if ((row < 0) || (row >= gridSize) || (col < 0) || (col >= gridSize)) {
                continue;
            }

            if ((grid[row][col] == 1) || (visitDistance[row][col] <= visitDistance[x][y] + 1)) {
                continue;
            }
            visitDistance[row][col] = visitDistance[x][y] + 1;
            bfsQueue[bfsQueueHead++] = row * gridSize + col;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1}, {1, 0}}, 2, {2, 2}},
                    {{{0, 0, 0}, {1, 1, 0}, {1, 1, 0}}, 3, {3, 3, 3}},
                    {{{1, 0, 0}, {1, 1, 0}, {1, 1, 0}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1],[1,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
     *  Output: 4
     *
     *  Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
     *  Output: -1
     */

    int** pGrid = NULL;
    int answer;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGrid = (int**)malloc(testCase[i].gridSize * sizeof(int*));
        if (pGrid == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = (int*)malloc(testCase[i].gridColSize[j] * sizeof(int));
            if (pGrid[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pGrid[k]);
                    pGrid[k] = NULL;
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, (testCase[i].gridColSize[j] * sizeof(int)));
            memcpy(pGrid[j], testCase[i].grid[j], (testCase[i].gridColSize[j] * sizeof(int)));
        }
        answer = shortestPathBinaryMatrix(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            free(pGrid[j]);
            pGrid[j] = NULL;
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
