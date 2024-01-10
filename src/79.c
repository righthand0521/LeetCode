#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool dfs(char** board, int i, int j, int boardSize, int* boardColSize, char* word, int wordIdx) {
    int retVal = false;

    if (wordIdx == strlen(word)) {
        retVal = true;
        return retVal;
    }

    if (((i < 0) || (i > boardSize - 1)) || ((j < 0) || (j > boardColSize[i] - 1)) || (board[i][j] != word[wordIdx])) {
        return retVal;
    }

    char tmp = board[i][j];
    board[i][j] = ' ';

    retVal = dfs(board, i - 1, j, boardSize, boardColSize, word, wordIdx + 1);
    retVal |= dfs(board, i + 1, j, boardSize, boardColSize, word, wordIdx + 1);
    retVal |= dfs(board, i, j - 1, boardSize, boardColSize, word, wordIdx + 1);
    retVal |= dfs(board, i, j + 1, boardSize, boardColSize, word, wordIdx + 1);

    board[i][j] = tmp;

    return retVal;
}
bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int retVal = false;

    if ((board == NULL) || (boardSize == 0) || (boardColSize == NULL)) {
        return retVal;
    } else if (word == NULL) {
        retVal = true;
        return retVal;
    }

    int i, j;
    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardColSize[i]; ++j) {
            retVal = dfs(board, i, j, boardSize, boardColSize, word, 0);
            if (retVal == true) {
                return retVal;
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char board[MAX_SIZE][MAX_SIZE];
        int boardSize;
        int boardColSize[MAX_SIZE];
        char* word;
    } testCase[] = {{{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, 3, {4, 4, 4}, "ABCCED"},
                    {{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, 3, {4, 4, 4}, "SEE"},
                    {{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, 3, {4, 4, 4}, "ABCB"},
                    {{{'a', 'a'}}, 2, {2}, "aaa"},
                    {{{'a'}}, 1, {1}, "a"}

    };
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

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
