#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bfs(int** grid, int rowSize, int colSize, bool** pVisited, int row, int col) {
    int retVal = 0;

    int bfsQueueSize = 4 * rowSize * colSize;
    int bfsQueue[bfsQueueSize][2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueFront = 0;
    int bfsQueueRear = 0;
    bfsQueue[bfsQueueRear][0] = row;
    bfsQueue[bfsQueueRear][1] = col;
    bfsQueueRear++;

    pVisited[row][col] = true;

    const int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int x, y, nextX, nextY;
    while (bfsQueueFront < bfsQueueRear) {
        x = bfsQueue[bfsQueueFront][0];
        y = bfsQueue[bfsQueueFront][1];
        bfsQueueFront++;

        retVal += grid[x][y];

        for (int dir = 0; dir < 4; ++dir) {
            nextX = x + directions[dir][0];
            nextY = y + directions[dir][1];
            if ((nextX < 0) || (nextX >= rowSize) || (nextY < 0) || (nextY >= colSize)) {
                continue;
            }

            if ((grid[nextX][nextY] != 0) && (pVisited[nextX][nextY] == false)) {
                bfsQueue[bfsQueueRear][0] = nextX;
                bfsQueue[bfsQueueRear][1] = nextY;
                bfsQueueRear++;
                pVisited[nextX][nextY] = true;
            }
        }
    }

    return retVal;
}
int findMaxFish(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    bool** pVisited = (bool**)malloc(rowSize * sizeof(bool*));
    if (pVisited == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < rowSize; ++i) {
        pVisited[i] = (bool*)malloc(colSize * sizeof(bool));
        if (pVisited[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; ++j) {
                free(pVisited[j]);
                pVisited[j] = NULL;
            }
            free(pVisited);
            pVisited = NULL;
            return retVal;
        }
        memset(pVisited[i], false, (colSize * sizeof(bool)));
    }
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            if ((grid[i][j] != 0) && (pVisited[i][j] == false)) {
                retVal = fmax(retVal, bfs(grid, rowSize, colSize, pVisited, i, j));
            }
        }
    }

    //
    for (int i = 0; i < rowSize; ++i) {
        free(pVisited[i]);
        pVisited[i] = NULL;
    }
    free(pVisited);
    pVisited = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (10)
#define MAX_COLUMN (10)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{0, 2, 1, 0}, {4, 0, 0, 3}, {1, 0, 0, 4}, {0, 3, 2, 0}}, 4, {4, 4, 4, 4}},
                    {{{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}}, 4, {4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
     *  Output: 7
     *
     *  Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
     *  Output: 1
     */

    int** pGrid = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
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
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }
        answer = findMaxFish(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
