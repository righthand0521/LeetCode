#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minCost(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int rowSize = gridSize;
    int colSize = gridColSize[0];

    // Track minimum cost to reach each cell
    int minCost[rowSize][colSize];
    memset(minCost, 0, sizeof(minCost));
    for (int i = 0; i < rowSize; i++) {
        for (int j = 0; j < colSize; j++) {
            minCost[i][j] = INT_MAX;
        }
    }
    minCost[0][0] = 0;

    // Direction vectors: right, left, down, up (matching grid values 1,2,3,4)
    int direction[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    // Use deque for 0-1 BFS - add zero cost moves to front, cost=1 to back
    int bfsQueueFront = rowSize * colSize;
    int bfsQueueBack = rowSize * colSize;
    int bfsQueueSize = bfsQueueFront + bfsQueueBack + 1;
    int bfsQueue[bfsQueueSize][2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueueFront--;
    bfsQueue[bfsQueueFront][0] = 0;
    bfsQueue[bfsQueueFront][1] = 0;

    int row, col, newRow, newCol, cost;
    while (bfsQueueFront != bfsQueueBack) {
        row = bfsQueue[bfsQueueFront][0];
        col = bfsQueue[bfsQueueFront][1];
        bfsQueueFront++;

        for (int dir = 0; dir < 4; dir++) {
            newRow = row + direction[dir][0];
            newCol = col + direction[dir][1];
            if ((newRow < 0) || (newRow >= rowSize) || (newCol < 0) || (newCol >= colSize)) {
                continue;
            }

            cost = (grid[row][col] != (dir + 1)) ? (1) : (0);
            if (minCost[row][col] + cost >= minCost[newRow][newCol]) {
                continue;
            }

            minCost[newRow][newCol] = minCost[row][col] + cost;

            // Add to back if cost=1, front if cost=0
            if (cost == 1) {
                bfsQueueBack++;
                bfsQueue[bfsQueueBack][0] = newRow;
                bfsQueue[bfsQueueBack][1] = newCol;
            } else {
                bfsQueueFront--;
                bfsQueue[bfsQueueFront][0] = newRow;
                bfsQueue[bfsQueueFront][1] = newCol;
            }
        }
    }

    retVal = minCost[rowSize - 1][colSize - 1];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (100)
#define MAX_COLUMN (100)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {{{{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}}, 4, {4, 4, 4, 4}},
                    {{{1, 1, 3}, {3, 2, 2}, {1, 1, 4}}, 3, {3, 3, 3}},
                    {{{1, 2}, {4, 3}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
     *  Output: 3
     *
     *  Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
     *  Output: 0
     *
     *  Input: grid = [[1,2],[4,3]]
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
        answer = minCost(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
