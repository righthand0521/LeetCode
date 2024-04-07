#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getNextBoardValue(int** board, int boardSize, int num) {
    int retVal = -1;

    if (board == NULL) {
        return retVal;
    }

    int x = (num - 1) / boardSize;
    int y = (num - 1) % boardSize;

    if (x % 2 != 0) {
        y = (boardSize - 1) - y;
    }
    x = (boardSize - 1) - x;
    retVal = board[x][y];

    return retVal;
}
int snakesAndLadders(int** board, int boardSize, int* boardColSize) {
    int retVal = -1;

    if ((board == NULL) || (boardSize == 0) || (boardColSize == NULL)) {
        return retVal;
    }

    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueueSize = boardSize * boardSize;
    int bfsQueue[bfsQueueSize];
    memset(bfsQueue, 0, sizeof(bfsQueue));
    bfsQueue[bfsQueueTail++] = 1;

    int visitedSize = boardSize * boardSize + 1;
    int visited[visitedSize];
    memset(visited, 0, sizeof(visited));

    int cur = 0;
    int next = 0;
    int minStep = 0;
    int layerNum = 0;
    int i, j;
    while (bfsQueueTail != bfsQueueHead) {
        layerNum = bfsQueueTail - bfsQueueHead;
        for (i = 0; i < layerNum; ++i) {
            cur = bfsQueue[bfsQueueHead++];
            if (cur == (visitedSize - 1)) {
                retVal = minStep;
                return retVal;
            }

            for (j = 1; (j <= 6 && cur + j < visitedSize); ++j) {
                next = getNextBoardValue(board, boardSize, cur + j);
                if (next == -1) {
                    next = cur + j;
                }

                if (visited[next]) {
                    continue;
                }
                visited[next] = true;
                bfsQueue[bfsQueueTail++] = next;
            }
        }

        minStep++;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        int board[MAX_SIZE][MAX_SIZE];
        int boardSize;
        int boardColSize[MAX_SIZE];
    } testCase[] = {{{{-1, -1, -1, -1, -1, -1},
                      {-1, -1, -1, -1, -1, -1},
                      {-1, -1, -1, -1, -1, -1},
                      {-1, 35, -1, -1, 13, -1},
                      {-1, -1, -1, -1, -1, -1},
                      {-1, 15, -1, -1, -1, -1}},
                     6,
                     {6, 6, 6, 6, 6, 6}},
                    {{{-1, -1}, {-1, 3}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: board = [
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,35,-1,-1,13,-1],
     *      [-1,-1,-1,-1,-1,-1],
     *      [-1,15,-1,-1,-1,-1]
     *  ]
     *  Output: 4
     *
     *  Input: board = [[-1,-1],[-1,3]]
     *  Output: 1
     */

    int** pBoard = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBoard = (int**)malloc(testCase[i].boardSize * sizeof(int*));
        if (pBoard == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].boardSize; ++j) {
            pBoard[j] = (int*)malloc(testCase[i].boardColSize[j] * sizeof(int));
            if (pBoard[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pBoard[k]) {
                        free(pBoard[k]);
                        pBoard[k] = NULL;
                    }
                }
                free(pBoard);
                pBoard = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoard[j], 0, testCase[i].boardColSize[j] * sizeof(int));
            memcpy(pBoard[j], testCase[i].board[j], testCase[i].boardColSize[j] * sizeof(int));
        }
        answer = snakesAndLadders(pBoard, testCase[i].boardSize, testCase[i].boardColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].boardSize; ++j) {
            if (pBoard[j]) {
                free(pBoard[j]);
                pBoard[j] = NULL;
            }
        }
        free(pBoard);
        pBoard = NULL;
    }

    return EXIT_SUCCESS;
}
