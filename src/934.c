#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shortestBridge(int** grid, int gridSize, int* gridColSize) {
    int retVal = 0;

    int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    int i;
    int x, y, row, col;

    //
    int bfsQueue1[gridSize * gridSize];
    memset(bfsQueue1, 0, sizeof(bfsQueue1));
    int bfsQueue1Head = 0;
    int bfsQueue1Tail = 0;
    int bfsQueue2[gridSize * gridSize];
    memset(bfsQueue2, 0, sizeof(bfsQueue2));
    int bfsQueue2Head = 0;
    int bfsQueue2Tail = 0;
    int island1x = 0;
    int island1y = 0;
    for (x = 0; x < gridSize; ++x) {
        for (y = 0; y < gridSize; ++y) {
            if (grid[x][y] == 1) {
                island1x = x;
                island1y = y;
                break;
            }
        }
    }
    bfsQueue1[bfsQueue1Head++] = island1x * gridSize + island1y;
    bfsQueue2[bfsQueue2Head++] = island1x * gridSize + island1y;
    grid[island1x][island1y] = 2;

    //
    while (bfsQueue1Head > bfsQueue1Tail) {
        x = bfsQueue1[bfsQueue1Tail] / gridSize;
        y = bfsQueue1[bfsQueue1Tail] % gridSize;
        ++bfsQueue1Tail;

        for (i = 0; i < 4; ++i) {
            row = x + direction[i][0];
            col = y + direction[i][1];
            if ((0 <= row) && (row < gridSize) && (0 <= col) && (col < gridSize)) {
                if (grid[row][col] == 1) {
                    bfsQueue1[bfsQueue1Head++] = row * gridSize + col;
                    bfsQueue2[bfsQueue2Head++] = row * gridSize + col;
                    grid[row][col] = 2;
                }
            }
        }
    }

    //
    int times;
    int bfsQueue2Size;
    while (bfsQueue2Head > bfsQueue2Tail) {
        bfsQueue2Size = bfsQueue2Head - bfsQueue2Tail;
        for (times = 0; times < bfsQueue2Size; ++times) {
            x = bfsQueue2[bfsQueue2Tail] / gridSize;
            y = bfsQueue2[bfsQueue2Tail] % gridSize;
            ++bfsQueue2Tail;

            for (i = 0; i < 4; ++i) {
                row = x + direction[i][0];
                col = y + direction[i][1];
                if ((0 <= row) && (row < gridSize) && (0 <= col) && (col < gridSize)) {
                    if (grid[row][col] == 1) {
                        return retVal;
                    } else if (grid[row][col] == 0) {
                        bfsQueue2[bfsQueue2Head++] = row * gridSize + col;
                        grid[row][col] = -1;
                    }
                }
            }
        }
        ++retVal;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int grid[MAX_SIZE][MAX_SIZE];
        int gridSize;
        int gridColSize[MAX_SIZE];
    } testCase[] = {
        {{{0, 1}, {1, 0}}, 2, {2, 2}},
        {{{0, 1, 0}, {0, 0, 0}, {0, 0, 1}}, 3, {3, 3, 3}},
        {{{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}}, 5, {5, 5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: grid = [[0,1],[1,0]]
     *  Output: 1
     *
     *  Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
     *  Output: 2
     *
     *  Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
     *  Output: 1
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
        answer = shortestBridge(pGrid, testCase[i].gridSize, testCase[i].gridColSize);
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
