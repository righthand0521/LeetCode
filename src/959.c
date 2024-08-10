#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int Directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
void floodFill(int** expandedGrid, int expandedGridSize, int x, int y) {
    expandedGrid[x][y] = 1;

    int bfsQueueSize = expandedGridSize * expandedGridSize;
    int bfsQueue[bfsQueueSize][2];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    bfsQueue[bfsQueueTail][0] = x;
    bfsQueue[bfsQueueTail][1] = y;
    bfsQueueTail++;

    int row, col;
    int currentRow, currentCol;
    int i;
    while (bfsQueueHead < bfsQueueTail) {
        currentRow = bfsQueue[bfsQueueHead][0];
        currentCol = bfsQueue[bfsQueueHead][1];
        bfsQueueHead++;

        for (i = 0; i < 4; ++i) {
            row = Directions[i][0] + currentRow;
            col = Directions[i][1] + currentCol;
            if ((row < 0) || (row >= expandedGridSize)) {
                continue;
            } else if ((col < 0) || (col >= expandedGridSize)) {
                continue;
            } else if (expandedGrid[row][col] != 0) {
                continue;
            }

            expandedGrid[row][col] = 1;
            bfsQueue[bfsQueueTail][0] = row;
            bfsQueue[bfsQueueTail][1] = col;
            bfsQueueTail++;
        }
    }
}
int regionsBySlashes(char** grid, int gridSize) {
    int retVal = 0;

    //
    int expandedGridSize = gridSize * 3;
    int** pExpandedGrid = (int**)malloc(expandedGridSize * sizeof(int*));
    if (pExpandedGrid == NULL) {
        perror("malloc");
        return retVal;
    }
    int i, j;
    for (i = 0; i < expandedGridSize; ++i) {
        pExpandedGrid[i] = (int*)malloc(expandedGridSize * sizeof(int));
        if (pExpandedGrid[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pExpandedGrid[j]);
                pExpandedGrid[j] = NULL;
            }
            free(pExpandedGrid);
            pExpandedGrid = NULL;
            return retVal;
        }
        memset(pExpandedGrid[i], 0, (expandedGridSize * sizeof(int)));
    }

    //
    int row, col;
    int x, y;
    for (x = 0; x < gridSize; ++x) {
        for (y = 0; y < gridSize; ++y) {
            row = x * 3;
            col = y * 3;
            if (grid[x][y] == '\\') {
                pExpandedGrid[row][col] = 1;
                pExpandedGrid[row + 1][col + 1] = 1;
                pExpandedGrid[row + 2][col + 2] = 1;
            } else if (grid[x][y] == '/') {
                pExpandedGrid[row][col + 2] = 1;
                pExpandedGrid[row + 1][col + 1] = 1;
                pExpandedGrid[row + 2][col] = 1;
            }
        }
    }

    //
    for (x = 0; x < expandedGridSize; ++x) {
        for (y = 0; y < expandedGridSize; ++y) {
            if (pExpandedGrid[x][y] == 0) {
                floodFill(pExpandedGrid, expandedGridSize, x, y);
                retVal++;
            }
        }
    }

    //
    for (i = 0; i < expandedGridSize; ++i) {
        free(pExpandedGrid[i]);
        pExpandedGrid[i] = NULL;
    }
    free(pExpandedGrid);
    pExpandedGrid = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (30)
    struct testCaseType {
        char* grid[MAX_SIZE];
        int gridSize;
    } testCase[] = {{{" /", "/ "}, 2}, {{" /", "  "}, 2}, {{"/\\", "\\/"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [" /","/ "]
     *  Output: 2
     *
     *  Input: grid = [" /","  "]
     *  Output: 1
     *
     *  Input: grid = ["/\\","\\/"]
     *  Output: 5
     */

    int answer = 0;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: grid = [");
        for (j = 0; j < testCase[i].gridSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].grid[j]);
        }
        printf("]\n");

        answer = regionsBySlashes(testCase[i].grid, testCase[i].gridSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
