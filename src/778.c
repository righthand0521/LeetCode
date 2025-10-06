#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool bfs(int** grid, int gridSize, int* gridColSize, int threshold) {
    bool retVal = false;

    if (grid[0][0] > threshold) {
        return retVal;
    }

    bool visited[gridSize][gridSize];
    memset(visited, false, sizeof(visited));
    visited[0][0] = true;

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int bfsQueue[gridSize * gridSize][2];
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail][0] = 0;
    bfsQueue[bfsQueueTail][1] = 0;
    bfsQueueTail++;

    int x, y, nextX, nextY;
    while (bfsQueueHead < bfsQueueTail) {
        x = bfsQueue[bfsQueueHead][0];
        y = bfsQueue[bfsQueueHead][1];
        bfsQueueHead++;

        for (int i = 0; i < 4; i++) {
            nextX = x + directions[i][0];
            nextY = y + directions[i][1];
            if ((nextX < 0) || (nextX >= gridSize) || (nextY < 0) || (nextY >= gridSize)) {
                continue;
            } else if (visited[nextX][nextY]) {
                continue;
            } else if (grid[nextX][nextY] > threshold) {
                continue;
            }

            if ((nextX == gridSize - 1) && (nextY == gridSize - 1)) {
                retVal = true;
                return retVal;
            }
            visited[nextX][nextY] = true;
            bfsQueue[bfsQueueTail][0] = nextX;
            bfsQueue[bfsQueueTail][1] = nextY;
            bfsQueueTail++;
        }
    }

    return retVal;
}
int swimInWater(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int middle;
    int left = 0;
    int right = gridSize * gridSize - 1;
    while (left < right) {
        middle = (left + right) / 2;
        if ((grid[0][0] <= middle) && (bfs(grid, gridSize, gridColSize, middle) == true)) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    retVal = left;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (50)
#define MAX_COLUMN (50)
    struct testCaseType {
        int grid[MAX_ROW][MAX_COLUMN];
        int gridSize;
        int gridColSize[MAX_ROW];
    } testCase[] = {
        {{{0, 2}, {1, 3}}, 2, {2, 2}},
        {{{0, 1, 2, 3, 4}, {24, 23, 22, 21, 5}, {12, 13, 14, 15, 16}, {11, 17, 18, 19, 20}, {10, 9, 8, 7, 6}},
         5,
         {5, 5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,2],[1,3]]
     *  Output: 3
     *
     *  Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
     *  Output: 16
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
        answer = swimInWater(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
