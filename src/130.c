#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
void solve(char** board, int boardSize, int* boardColSize) {
    if (boardSize == 0) {
        return;
    }
    int rowSize = boardSize;
    int colSize = boardColSize[0];

    //
    int i, j;
    int bfsQueueHead = 0;
    int bfsQueueTail = 0;
    int bfsQueueSize = rowSize * colSize;
    int** bfsQueue = (int**)malloc(bfsQueueSize * sizeof(int*));
    if (bfsQueue == NULL) {
        perror("malloc");
        return;
    }
    for (i = 0; i < bfsQueueSize; i++) {
        bfsQueue[i] = (int*)malloc(2 * sizeof(int));
        if (bfsQueue[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; j++) {
                free(bfsQueue[j]);
                bfsQueue[j] = NULL;
            }
            free(bfsQueue);
            bfsQueue = NULL;
            return;
        }
        memset(bfsQueue[i], 0, (2 * sizeof(int)));
    }

    //
    for (i = 0; i < rowSize; i++) {
        if (board[i][0] == 'O') {
            board[i][0] = 'A';
            bfsQueue[bfsQueueTail][0] = i;
            bfsQueue[bfsQueueTail][1] = 0;
            bfsQueueTail++;
        }
        if (board[i][colSize - 1] == 'O') {
            board[i][colSize - 1] = 'A';
            bfsQueue[bfsQueueTail][0] = i;
            bfsQueue[bfsQueueTail][1] = colSize - 1;
            bfsQueueTail++;
        }
    }
    for (i = 1; i < colSize - 1; i++) {
        if (board[0][i] == 'O') {
            board[0][i] = 'A';
            bfsQueue[bfsQueueTail][0] = 0;
            bfsQueue[bfsQueueTail][1] = i;
            bfsQueueTail++;
        }
        if (board[rowSize - 1][i] == 'O') {
            board[rowSize - 1][i] = 'A';
            bfsQueue[bfsQueueTail][0] = rowSize - 1;
            bfsQueue[bfsQueueTail][1] = i;
            bfsQueueTail++;
        }
    }

    //
    int row, col, x, y;
    while (bfsQueueHead < bfsQueueTail) {
        row = bfsQueue[bfsQueueHead][0];
        col = bfsQueue[bfsQueueHead][1];
        bfsQueueHead++;
        for (i = 0; i < 4; i++) {
            x = row + dx[i];
            y = col + dy[i];
            if ((x < 0) || (y < 0) || (x >= rowSize) || (y >= colSize) || (board[x][y] != 'O')) {
                continue;
            }
            board[x][y] = 'A';
            bfsQueue[bfsQueueTail][0] = x;
            bfsQueue[bfsQueueTail][1] = y;
            bfsQueueTail++;
        }
    }

    //
    for (i = 0; i < rowSize; i++) {
        for (j = 0; j < colSize; j++) {
            if (board[i][j] == 'A') {
                board[i][j] = 'O';
            } else if (board[i][j] == 'O') {
                board[i][j] = 'X';
            }
        }
    }

    //
    for (i = 0; i < bfsQueueSize; i++) {
        free(bfsQueue[i]);
        bfsQueue[i] = NULL;
    }
    free(bfsQueue);
    bfsQueue = NULL;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char board[MAX_SIZE][MAX_SIZE];
        int boardSize;
        int boardColSize[MAX_SIZE];
    } testCase[] = {
        {{{'X', 'X', 'X', 'X'}, {'X', '0', '0', 'X'}, {'X', 'X', '0', 'X'}, {'X', '0', 'X', 'X'}}, 4, {4, 4, 4, 4}},
        {{{'X'}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
     *  Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
     *
     *  Input: board = [["X"]]
     *  Output: [["X"]]
     */

    char** pBoard = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBoard = (char**)malloc(testCase[i].boardSize * sizeof(char*));
        if (pBoard == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (k = 0; k < testCase[i].boardSize; ++k) {
            pBoard[k] = (char*)malloc(testCase[i].boardColSize[k] * sizeof(char));
            if (pBoard[k] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].boardSize; ++k) {
                    if (pBoard[k]) {
                        free(pBoard[k]);
                    }
                }
                free(pBoard);
                pBoard = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoard[k], 0, testCase[i].boardColSize[k] * sizeof(char));
            memcpy(pBoard[k], testCase[i].board[k], testCase[i].boardColSize[k] * sizeof(char));
        }
        solve(pBoard, testCase[i].boardSize, testCase[i].boardColSize);
        printf("Output: = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0) ? "" : ",", pBoard[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (k = 0; k < testCase[i].boardSize; ++k) {
            if (pBoard[k]) {
                free(pBoard[k]);
            }
        }
        free(pBoard);
        pBoard = NULL;
    }

    return EXIT_SUCCESS;
}
