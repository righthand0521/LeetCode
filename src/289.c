#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gameOfLife(int** board, int boardSize, int* boardColSize) {
    // m == board.length, n == board[i].length, 1 <= m, n <= 25
    int rowSize = boardSize;
    int colSize = boardColSize[0];
    int x, y;
    int i, j;

    int backup[rowSize][colSize];
    memset(backup, 0, sizeof(backup));
    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            backup[x][y] = board[x][y];
        }
    }

    int live, neighborX, neighborY;
    for (x = 0; x < rowSize; ++x) {
        for (y = 0; y < colSize; ++y) {
            live = 0;
            for (i = -1; i <= 1; ++i) {
                neighborX = x + i;
                if ((neighborX < 0) || (neighborX >= rowSize)) {
                    continue;
                }

                for (j = -1; j <= 1; ++j) {
                    if ((i == 0) && (j == 0)) {
                        continue;
                    }

                    neighborY = y + j;
                    if ((neighborY < 0) || (neighborY >= colSize)) {
                        continue;
                    }

                    if (backup[neighborX][neighborY] == 1) {
                        ++live;
                    }
                }
            }

            if (backup[x][y] == 1) {
                if ((live < 2) || (live > 3)) {
                    board[x][y] = 0;
                }
            } else if (backup[x][y] == 0) {
                if (live == 3) {
                    board[x][y] = 1;
                }
            }
        }
    }
}

int main(int argc, char** argv) {
#define MAX_SIZE (25)
    struct testCaseType {
        int board[MAX_SIZE][MAX_SIZE];
        int boardSize;
        int boardColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}}, 4, {3, 3, 3, 3}}, {{{1, 1}, {1, 0}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
     *  Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
     *
     *  Input: board = [[1,1],[1,0]]
     *  Output: [[1,1],[1,1]]
     */

    int** pBoard = NULL;
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
        gameOfLife(pBoard, testCase[i].boardSize, testCase[i].boardColSize);

        printf("Output: [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pBoard[j][k]);
            }
            printf("]");
        }
        printf("]\n");

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
