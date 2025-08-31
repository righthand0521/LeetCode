#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOARD_SIZE (9)
#define MAX_SPACES_SIZE (MAX_BOARD_SIZE * MAX_BOARD_SIZE)
int* spaces[MAX_SPACES_SIZE];
int spacesSize;
bool valid;
int line[MAX_BOARD_SIZE];
int column[MAX_BOARD_SIZE];
int block[3][3];
void flip(int i, int j, int digit) {
    line[i] ^= (1 << digit);
    column[j] ^= (1 << digit);
    block[i / 3][j / 3] ^= (1 << digit);
}
void dfs(char** board, int pos) {
    if (pos == spacesSize) {
        valid = true;
        return;
    }

    int i = spaces[pos][0];
    int j = spaces[pos][1];
    int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & (0x1ff);
    for (; mask && !valid; mask &= (mask - 1)) {
        int digitMask = mask & (-mask);
        int digit = __builtin_ctz(digitMask);
        flip(i, j, digit);
        board[i][j] = digit + '0' + 1;
        dfs(board, pos + 1);
        flip(i, j, digit);
    }
}
void solveSudoku(char** board, int boardSize, int* boardColSize) {
    memset(line, 0, sizeof(line));
    memset(column, 0, sizeof(column));
    memset(block, 0, sizeof(block));
    valid = false;
    spacesSize = 0;

    for (int i = 0; i < MAX_BOARD_SIZE; ++i) {
        for (int j = 0; j < MAX_BOARD_SIZE; ++j) {
            if (board[i][j] != '.') {
                int digit = board[i][j] - '0' - 1;
                flip(i, j, digit);
            }
        }
    }

    while (true) {
        int modified = false;
        for (int i = 0; i < MAX_BOARD_SIZE; ++i) {
            for (int j = 0; j < MAX_BOARD_SIZE; ++j) {
                if (board[i][j] != '.') {
                    continue;
                }
                int mask = ~(line[i] | column[j] | block[i / 3][j / 3]) & (0x1ff);
                if (!(mask & (mask - 1))) {
                    int digit = __builtin_ctz(mask);
                    flip(i, j, digit);
                    board[i][j] = digit + '0' + 1;
                    modified = true;
                }
            }
        }
        if (!modified) {
            break;
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '.') {
                spaces[spacesSize] = malloc(sizeof(int) * 2);
                spaces[spacesSize][0] = i;
                spaces[spacesSize++][1] = j;
            }
        }
    }

    dfs(board, 0);
}

int main(int argc, char** argv) {
#define BOARD_SIZE (9)
    struct testCaseType {
        char board[BOARD_SIZE][BOARD_SIZE];
        int boardSize;
        int boardColSize[BOARD_SIZE];
    } testCase[] = {{{{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                      {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                      {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                      {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                      {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                      {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                      {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                      {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}},
                     9,
                     {9, 9, 9, 9, 9, 9, 9, 9, 9}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: board = [
     *      ["5","3",".",".","7",".",".",".","."],
     *      ["6",".",".","1","9","5",".",".","."],
     *      [".","9","8",".",".",".",".","6","."],
     *      ["8",".",".",".","6",".",".",".","3"],
     *      ["4",".",".","8",".","3",".",".","1"],
     *      ["7",".",".",".","2",".",".",".","6"],
     *      [".","6",".",".",".",".","2","8","."],
     *      [".",".",".","4","1","9",".",".","5"],
     *      [".",".",".",".","8",".",".","7","9"]
     *  ]
     *  Output: [
     *      ["5","3","4","6","7","8","9","1","2"],
     *      ["6","7","2","1","9","5","3","4","8"],
     *      ["1","9","8","3","4","2","5","6","7"],
     *      ["8","5","9","7","6","1","4","2","3"],
     *      ["4","2","6","8","5","3","7","9","1"],
     *      ["7","1","3","9","2","4","8","5","6"],
     *      ["9","6","1","5","3","7","2","8","4"],
     *      ["2","8","7","4","1","9","6","3","5"],
     *      ["3","4","5","2","8","6","1","7","9"]
     *  ]
     */

    char** pBoard = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = [\n");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s  [", (j == 0) ? "" : ",\n");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%c", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("\n]\n");

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
        solveSudoku(pBoard, testCase[i].boardSize, testCase[i].boardColSize);
        printf("Output: [\n");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s  [", (j == 0) ? "" : ",\n");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%c", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("\n]\n");

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
