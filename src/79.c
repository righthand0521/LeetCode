#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool dfs(char** board, int boardSize, int* boardColSize, char* word, int row, int col, int idx) {
    int retVal = false;

    // 1 <= word.length <= 15
    int wordSize = strlen(word);
    if (idx == wordSize) {
        retVal = true;
        return retVal;
    }

    // m == board.length, n = board[i].length, 1 <= m, n <= 6
    if ((row < 0) || (row > (boardSize - 1))) {
        return retVal;
    } else if ((col < 0) || (col > (boardColSize[row] - 1))) {
        return retVal;
    }

    if (board[row][col] != word[idx]) {
        return retVal;
    }

    char tmp = board[row][col];
    board[row][col] = ' ';
    retVal = dfs(board, boardSize, boardColSize, word, row - 1, col, idx + 1);
    retVal |= dfs(board, boardSize, boardColSize, word, row + 1, col, idx + 1);
    retVal |= dfs(board, boardSize, boardColSize, word, row, col - 1, idx + 1);
    retVal |= dfs(board, boardSize, boardColSize, word, row, col + 1, idx + 1);
    board[row][col] = tmp;

    return retVal;
}
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int retVal = false;

    int row, col;
    for (row = 0; row < boardSize; ++row) {
        for (col = 0; col < boardColSize[row]; ++col) {
            retVal = dfs(board, boardSize, boardColSize, word, row, col, 0);
            if (retVal == true) {
                return retVal;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10)
    struct testCaseType {
        char board[MAX_SIZE][MAX_SIZE];
        int boardSize;
        int boardColSize[MAX_SIZE];
        char* word;
    } testCase[] = {{{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, 3, {4, 4, 4}, "ABCCED"},
                    {{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, 3, {4, 4, 4}, "SEE"},
                    {{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, 3, {4, 4, 4}, "ABCB"},
                    {{{'A', 'A'}}, 2, {2}, "AAA"},
                    {{{'A'}}, 1, {1}, "A"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
     *  Output: true
     *
     *  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
     *  Output: true
     *
     *  Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
     *  Output: false
     *
     *  Input: board = [["A","A"]], word = "AAA"
     *  Output: false
     *
     *  Input: board = [["A"]], word = "A"
     *  Output: true
     */

    char** pBoard = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: board = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0 ? "" : ","), testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("], word = \"%s\"\n", testCase[i].word);

        pBoard = (char**)malloc(testCase[i].boardSize * sizeof(char*));
        if (pBoard == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].boardSize; ++j) {
            pBoard[j] = (char*)malloc(testCase[i].boardColSize[j] * sizeof(char));
            if (pBoard[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pBoard[k]);
                    pBoard[k] = NULL;
                }
                free(pBoard);
                pBoard = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoard[j], 0, (testCase[i].boardColSize[j] * sizeof(char)));
            memcpy(pBoard[j], testCase[i].board[j], (testCase[i].boardColSize[j] * sizeof(char)));
        }
        answer = exist(pBoard, testCase[i].boardSize, testCase[i].boardColSize, testCase[i].word);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].boardSize; ++j) {
            free(pBoard[j]);
            pBoard[j] = NULL;
        }
        free(pBoard);
        pBoard = NULL;
    }

    return EXIT_SUCCESS;
}
