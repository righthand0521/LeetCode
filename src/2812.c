#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
bool enable(int** grid, int gridSize, int* gridColSize, int target) {
    bool retVal = false;

    if (grid[0][0] < target) {
        return retVal;
    }

    int queueSize = gridSize * gridColSize[0];
    int queue[queueSize][2];
    memset(queue, 0, sizeof(queueSize));
    int queueHead = 0;
    int queueTail = 0;
    queue[queueTail][0] = 0;
    queue[queueTail][1] = 0;
    queueTail++;

    int pathSize = gridSize * gridColSize[0];
    int path[pathSize];
    memset(path, 0, sizeof(path));
    path[0] = 1;

    int diffX, diffY;
    int currentX, currentY;
    int i;
    while (queueHead < queueTail) {
        currentX = queue[queueHead][0];
        currentY = queue[queueHead][1];
        queueHead++;
        if ((currentX == gridSize - 1) && (currentY == gridColSize[0] - 1)) {
            retVal = true;
            break;
        }

        for (i = 0; i < 4; i++) {
            diffX = currentX + direction[i][0];
            diffY = currentY + direction[i][1];
            if ((diffX < 0) || (diffX >= gridSize) || (diffY < 0) || (diffY >= gridColSize[0]) ||
                (grid[diffX][diffY] < target) || (path[diffX * gridColSize[0] + diffY] == 1)) {
                continue;
            }

            path[diffX * gridColSize[0] + diffY] = 1;
            queue[queueTail][0] = diffX;
            queue[queueTail][1] = diffY;
            queueTail++;
        }
    }

    return retVal;
}
int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    if ((grid[0][0] == 1) || (grid[gridSize - 1][gridColSize[0] - 1] == 1)) {
        return retVal;
    }

    int i, j;

    int multiSourceQueueSize = gridSize * gridColSize[0];
    int multiSourceQueue[multiSourceQueueSize][2];
    memset(multiSourceQueue, 0, sizeof(multiSourceQueue));
    int multiSourceQueueHead = 0;
    int multiSourceQueueTail = 0;
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridColSize[0]; j++) {
            if (grid[i][j] == 1) {
                grid[i][j] = 0;
                multiSourceQueue[multiSourceQueueTail][0] = i;
                multiSourceQueue[multiSourceQueueTail][1] = j;
                multiSourceQueueTail++;
            } else {
                grid[i][j] = -1;
            }
        }
    }

    int diffX, diffY;
    int currentX, currentY;
    while (multiSourceQueueHead < multiSourceQueueTail) {
        currentX = multiSourceQueue[multiSourceQueueHead][0];
        currentY = multiSourceQueue[multiSourceQueueHead][1];
        multiSourceQueueHead++;

        for (i = 0; i < 4; i++) {
            diffX = currentX + direction[i][0];
            diffY = currentY + direction[i][1];
            if ((diffX < 0) || (diffX >= gridSize) || (diffY < 0) || (diffY >= gridColSize[0]) ||
                (grid[diffX][diffY] >= 0)) {
                continue;
            }
            grid[diffX][diffY] = grid[currentX][currentY] + 1;
            multiSourceQueue[multiSourceQueueTail][0] = diffX;
            multiSourceQueue[multiSourceQueueTail][1] = diffY;
            multiSourceQueueTail++;
        }
    }

    int left = 0;
    int right = fmin(gridSize, gridColSize[0]);
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;

        if (enable(grid, gridSize, gridColSize, middle) == true) {
            left = middle + 1;
            retVal = middle;
        } else {
            right = middle - 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (400)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {{{{1, 0, 0}, {0, 0, 0}, {0, 0, 1}}, 3, {3, 3, 3}},
                    {{{0, 0, 1}, {0, 0, 0}, {0, 0, 0}}, 3, {3, 3, 3}},
                    {{{0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}}, 4, {4, 4, 4, 4}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
     *  Output: 0
     *
     *  Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
     *  Output: 2
     *
     *  Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
     *  Output: 2
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
        answer = maximumSafenessFactor(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
