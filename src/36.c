#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    bool retVal = false;

    int i, j;
#define MAX_SIZE (9)
    int HASHTABLE[MAX_SIZE];
    int idx;

    // check each row
    for (i = 0; i < boardSize; ++i) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (j = 0; j < boardColSize[i]; ++j) {
            if (board[i][j] == '.') {
                continue;
            }
            idx = (board[i][j] - '0') - 1;
            if (HASHTABLE[idx] != 0) {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    // check each column
    for (j = 0; j < boardColSize[0]; ++j) {
        memset(HASHTABLE, 0, sizeof(HASHTABLE));
        for (i = 0; i < boardSize; ++i) {
            if (board[i][j] == '.') {
                continue;
            }
            idx = (board[i][j] - '0') - 1;
            if (HASHTABLE[idx] != 0) {
                return retVal;
            }
            ++HASHTABLE[idx];
        }
    }

    // check 3x3 sub-boxes
    int rowShift;
    int colShift;
    for (rowShift = 0; rowShift < boardSize; rowShift += 3) {
        for (colShift = 0; colShift < boardColSize[0]; colShift += 3) {
            memset(HASHTABLE, 0, sizeof(HASHTABLE));
            for (i = 0; i < 3; ++i) {
                for (j = 0; j < 3; ++j) {
                    if (board[i + rowShift][j + colShift] == '.') {
                        continue;
                    }
                    idx = (board[i + rowShift][j + colShift] - '0') - 1;
                    if (HASHTABLE[idx] != 0) {
                        return retVal;
                    }
                    ++HASHTABLE[idx];
                }
            }
        }
    }

    retVal = true;

    return retVal;
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
                     {9, 9, 9, 9, 9, 9, 9, 9, 9}},
                    {{{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
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
     *  Input: board =
     *  [["5","3",".",".","7",".",".",".","."]
     *  ,["6",".",".","1","9","5",".",".","."]
     *  ,[".","9","8",".",".",".",".","6","."]
     *  ,["8",".",".",".","6",".",".",".","3"]
     *  ,["4",".",".","8",".","3",".",".","1"]
     *  ,["7",".",".",".","2",".",".",".","6"]
     *  ,[".","6",".",".",".",".","2","8","."]
     *  ,[".",".",".","4","1","9",".",".","5"]
     *  ,[".",".",".",".","8",".",".","7","9"]]
     *  Output: true
     *
     *  Input: board =
     *  [["8","3",".",".","7",".",".",".","."]
     *  ,["6",".",".","1","9","5",".",".","."]
     *  ,[".","9","8",".",".",".",".","6","."]
     *  ,["8",".",".",".","6",".",".",".","3"]
     *  ,["4",".",".","8",".","3",".",".","1"]
     *  ,["7",".",".",".","2",".",".",".","6"]
     *  ,[".","6",".",".",".",".","2","8","."]
     *  ,[".",".",".","4","1","9",".",".","5"]
     *  ,[".",".",".",".","8",".",".","7","9"]]
     *  Output: false
     */

    char** pBoard = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = \n[");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : "\n,");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s%c", (k == 0) ? "" : ",", testCase[i].board[j][k]);
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
        answer = isValidSudoku(pBoard, testCase[i].boardSize, testCase[i].boardColSize);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

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
