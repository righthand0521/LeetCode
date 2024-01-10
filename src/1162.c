#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/as-far-from-land-as-possible/solutions/233420/an-bfsmo-ban-lai-tao-jiu-xing-liao-by-yjgna/
struct node {
    int row;
    int col;
};
int maxDistance(int** grid, int gridSize, int* gridColSize) {
    int retVal = -1;  // If no land or water exists in the grid, return -1.

    int i, j;

    //
    int maxRow = gridSize;
    int maxCol = gridColSize[0];

    struct node bfsQueue[maxRow * maxCol];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueCount = 0;

#define BFS_VISIT (1)
    int bfsVisit[maxRow][maxCol];
    memset(bfsVisit, 0, sizeof(bfsVisit));

    //
    for (i = 0; i < maxRow; ++i) {
        for (j = 0; j < maxCol; ++j) {
            // 0 represents water and 1 represents land
            if (grid[i][j] != 1) {
                continue;
            }

            bfsQueue[bfsQueueCount].row = i;
            bfsQueue[bfsQueueCount].col = j;
            ++bfsQueueCount;
            bfsVisit[i][j] = BFS_VISIT;
        }
    }
    if ((bfsQueueCount == 0) || (bfsQueueCount == (maxRow * maxCol))) {
        return retVal;
    }

    // Breadth-First Search
    int tmp;
    int row, col;
    int bfsQueueRun = 0;
    while (bfsQueueRun != bfsQueueCount) {
        tmp = bfsQueueCount;
        for (i = bfsQueueRun; i < tmp; ++i) {
            row = bfsQueue[i].row;
            col = bfsQueue[i].col;

            // up
            if ((row > 0) && (bfsVisit[row - 1][col] == 0) && (grid[row - 1][col] == 0)) {
                bfsQueue[bfsQueueCount].row = row - 1;
                bfsQueue[bfsQueueCount].col = col;
                bfsQueueCount++;
                bfsVisit[row - 1][col] = BFS_VISIT;
            }

            // down
            if ((row < maxRow - 1) && (bfsVisit[row + 1][col] == 0) && (grid[row + 1][col] == 0)) {
                bfsQueue[bfsQueueCount].row = row + 1;
                bfsQueue[bfsQueueCount].col = col;
                bfsQueueCount++;
                bfsVisit[row + 1][col] = BFS_VISIT;
            }

            // left
            if ((col > 0) && (bfsVisit[row][col - 1] == 0) && (grid[row][col - 1] == 0)) {
                bfsQueue[bfsQueueCount].row = row;
                bfsQueue[bfsQueueCount].col = col - 1;
                bfsQueueCount++;
                bfsVisit[row][col - 1] = BFS_VISIT;
            }

            // right
            if ((col < maxCol - 1) && (bfsVisit[row][col + 1] == 0) && (grid[row][col + 1] == 0)) {
                bfsQueue[bfsQueueCount].row = row;
                bfsQueue[bfsQueueCount].col = col + 1;
                bfsQueueCount++;
                bfsVisit[row][col + 1] = BFS_VISIT;
            }
        }
        retVal++;

        bfsQueueRun = tmp;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}, 3, {3, 3, 3}},
                    {{{1, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pGrid = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].gridColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].grid[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pGrid = (int**)malloc(testCase[i].gridSize * sizeof(int*));
        if (pGrid == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].gridSize; ++j) {
            pGrid[j] = (int*)malloc(testCase[i].gridColSize[j] * sizeof(int));
            if (pGrid[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    if (pGrid[k]) {
                        free(pGrid[k]);
                    }
                }
                free(pGrid);
                pGrid = NULL;
                return EXIT_FAILURE;
            }
            memset(pGrid[j], 0, testCase[i].gridColSize[j] * sizeof(int));
            memcpy(pGrid[j], testCase[i].grid[j], testCase[i].gridColSize[j] * sizeof(int));
        }

        answer = maxDistance(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].gridSize; ++j) {
            if (pGrid[j]) {
                free(pGrid[j]);
                pGrid[j] = NULL;
            }
        }
        free(pGrid);
        pGrid = NULL;
    }

    return EXIT_SUCCESS;
}
