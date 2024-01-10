#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/last-day-where-you-can-still-cross/solutions/1808976/by-ambition-20-4hxw/
typedef struct {
    int x;
    int y;
} Position;
bool bfs(int row, int col, int** pGraph, int startCol) {
    bool retVal = false;

    Position directions[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    //
    Position startPosition = {1, startCol};

    int bfsHead = 0;
    int bfsTail = 0;
    int bfsQueueSize = row * col;
    Position* bfsQueue = (Position*)malloc(bfsQueueSize * sizeof(Position));
    if (bfsQueue == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(bfsQueue, 0, (bfsQueueSize * sizeof(Position)));
    bfsQueue[bfsTail++] = startPosition;

    //
    Position currentPosition, nextPosition;
    int i, j;
    while (bfsHead < bfsTail) {
        bfsQueueSize = bfsTail - bfsHead;

        for (i = 0; i < bfsQueueSize; ++i) {
            currentPosition = bfsQueue[bfsHead++];

            for (j = 0; j < 4; ++j) {
                nextPosition.x = currentPosition.x + directions[j].x;
                nextPosition.y = currentPosition.y + directions[j].y;

                if ((nextPosition.x < 1) || (nextPosition.x > row)) {
                    continue;
                } else if ((nextPosition.y < 1) || (nextPosition.y > col)) {
                    continue;
                } else if (pGraph[nextPosition.x][nextPosition.y] == 1) {
                    continue;
                }

                if (nextPosition.x == row) {
                    retVal = true;
                    goto exitLabel;
                }
                pGraph[nextPosition.x][nextPosition.y] = 1;
                bfsQueue[bfsTail++] = nextPosition;
            }
        }
    }

exitLabel:
    free(bfsQueue);
    bfsQueue = NULL;

    return retVal;
}
int latestDayToCross(int row, int col, int** cells, int cellsSize, int* cellsColSize) {
    int retVal = 0;

    int i, j;

    //
    int graphSize = row + 1;
    int graphColSize = col + 1;
    int** pGraph = (int**)malloc(graphSize * sizeof(int*));
    if (pGraph == NULL) {
        perror("malloc");
        return retVal;
    }
    for (i = 0; i < graphSize; ++i) {
        pGraph[i] = (int*)malloc(graphColSize * sizeof(int));
        if (pGraph[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pGraph[j]);
                pGraph[j] = NULL;
            }
            free(pGraph);
            pGraph = NULL;
            return retVal;
        }
        memset(pGraph[i], 0, (graphColSize * sizeof(int)));
    }

    //
    bool flag;
    int middle;
    int left = 0;
    int right = row * col;
    while (left <= right) {
        middle = left + ((right - left) >> 1);

        flag = false;
        for (i = 0; i < row + 1; ++i) {
            memset(pGraph[i], 0, (graphColSize * sizeof(int)));
        }
        for (i = 0; i < middle; ++i) {
            pGraph[cells[i][0]][cells[i][1]] = 1;
        }
        for (j = 1; j < graphColSize; ++j) {
            if (pGraph[1][j] == 1) {
                continue;
            }
            pGraph[1][j] = 1;

            if (bfs(row, col, pGraph, j) == true) {
                flag = true;
                break;
            }
        }

        if (flag == false) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    retVal = right;

    //
    for (i = 0; i < graphSize; ++i) {
        free(pGraph[i]);
        pGraph[i] = NULL;
    }
    free(pGraph);
    pGraph = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (200)
#define MAX_COLUMN (200)
    struct testCaseType {
        int row;
        int col;
        int cells[MAX_ROW][MAX_COLUMN];
        int cellsSize;
        int cellsColSize[MAX_ROW];
    } testCase[] = {{2, 2, {{1, 1}, {2, 1}, {1, 2}, {2, 2}}, 4, {2, 2, 2, 2}},
                    {2, 2, {{1, 1}, {1, 2}, {2, 1}, {2, 2}}, 4, {2, 2, 2, 2}},
                    {3,
                     3,
                     {{1, 2}, {2, 1}, {3, 3}, {2, 2}, {1, 1}, {1, 3}, {2, 3}, {3, 2}, {3, 1}},
                     9,
                     {2, 2, 2, 2, 2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
     *  Output: 2
     *
     *  Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
     *  Output: 1
     *
     *  Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
     *  Output: 3
     */

    int** pCells = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: row = %d, col = %d, cells = [", testCase[i].row, testCase[i].col);
        for (j = 0; j < testCase[i].cellsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].cellsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].cells[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pCells = (int**)malloc(testCase[i].cellsSize * sizeof(int*));
        if (pCells == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].cellsSize; ++j) {
            pCells[j] = (int*)malloc(testCase[i].cellsColSize[j] * sizeof(int));
            if (pCells[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pCells[k]);
                }
                free(pCells);
                return EXIT_FAILURE;
            }
            memset(pCells[j], 0, (testCase[i].cellsColSize[j] * sizeof(int)));
            memcpy(pCells[j], testCase[i].cells[j], (testCase[i].cellsColSize[j] * sizeof(int)));
        }
        answer =
            latestDayToCross(testCase[i].row, testCase[i].col, pCells, testCase[i].cellsSize, testCase[i].cellsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].cellsSize; ++j) {
            free(pCells[j]);
        }
        free(pCells);
        pCells = NULL;
    }

    return EXIT_SUCCESS;
}
