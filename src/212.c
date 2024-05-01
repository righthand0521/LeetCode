#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// board[i][j] is a lowercase English letter.
#define TRIE_WIDTH (26)
struct TrieNode {
    char* str;
    struct TrieNode* child[TRIE_WIDTH];
};
struct TrieNode* createNode() {
    struct TrieNode* pNew = (struct TrieNode*)calloc(1, sizeof(struct TrieNode));
    if (pNew == NULL) {
        perror("perror");
    }

    return pNew;
}
void freeNode(struct TrieNode* pRoot) {
    if (pRoot == NULL) {
        return;
    }

    int i;
    for (i = 0; i < TRIE_WIDTH; ++i) {
        freeNode(pRoot->child[i]);
    }

    free(pRoot);
}
struct TrieNode* addNode(struct TrieNode* pRoot, char* pWord) {
    struct TrieNode* pCurrent = pRoot;

    int idx;
    int i;
    for (i = 0; pWord[i] != '\0'; ++i) {
        idx = pWord[i] - 'a';
        if (pCurrent->child[idx] == NULL) {
            pCurrent->child[idx] = createNode();
        }
        pCurrent = pCurrent->child[idx];
    }
    pCurrent->str = pWord;

    return pRoot;
}
// Depth-First Search
#define VISITED (-1)
void dfs(struct TrieNode* pRoot, char** board, int boardRow, int boardCol, int row, int col, char** retVal,
         int* returnSize) {
    // Exceed boundary
    if ((row == boardRow) || (row < 0)) {
        return;
    } else if ((col == boardCol) || (col < 0)) {
        return;
    }

    // Current board has been visited
    if (board[row][col] == VISITED) {
        return;
    }

    // This string path is not in the trie
    if ((pRoot->child[board[row][col] - 'a']) == NULL) {
        return;
    }

    pRoot = pRoot->child[board[row][col] - 'a'];
    if (pRoot->str) {
        retVal[*returnSize] = pRoot->str;
        (*returnSize) += 1;
        pRoot->str = NULL;
    }

    char tmp = board[row][col];
    board[row][col] = VISITED;
    dfs(pRoot, board, boardRow, boardCol, row + 1, col, retVal, returnSize);
    dfs(pRoot, board, boardRow, boardCol, row - 1, col, retVal, returnSize);
    dfs(pRoot, board, boardRow, boardCol, row, col + 1, retVal, returnSize);
    dfs(pRoot, board, boardRow, boardCol, row, col - 1, retVal, returnSize);
    board[row][col] = tmp;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize) {
    char** pRetVal = NULL;
    (*returnSize) = 0;

    pRetVal = malloc(sizeof(char*) * wordsSize);
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sizeof(char*) * wordsSize));

    int i, j;

    struct TrieNode* pRoot = createNode();
    if (pRoot == NULL) {
        return pRetVal;
    }
    for (i = 0; i < wordsSize; ++i) {
        pRoot = addNode(pRoot, words[i]);
    }

    for (i = 0; i < boardSize; ++i) {
        for (j = 0; j < boardColSize[i]; ++j) {
            dfs(pRoot, board, boardSize, boardColSize[i], i, j, pRetVal, returnSize);
        }
    }

    freeNode(pRoot);

    return pRetVal;
}

int main(int argc, char** argv) {
#define BOARD_SIZE (12)
#define WORDS_LENGTH (3 * 10000)
    struct testCaseType {
        char* board[BOARD_SIZE];
        int boardSize;
        int boardColSize[BOARD_SIZE];
        char* words[WORDS_LENGTH];
        int wordsSize;
        int returnSize;
    } testCase[] = {{{"oaan", "etae", "ihkr", "iflv"}, 4, {4, 4, 4, 4}, {"oath", "pea", "eat", "rain"}, 4, 0},
                    {{"ab", "cd"}, 2, {2, 2}, {"abcb"}, 1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]],
     *          words = ["oath","pea","eat","rain"]
     *  Output: ["eat","oath"]
     *
     *  Input: board = [["a","b"],["c","d"]], words = ["abcb"]
     *  Output: []
     */

    char** pBoard = NULL;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        //
        printf("Input: board = [");
        for (j = 0; j < testCase[i].boardSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].boardColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0) ? "" : ",", testCase[i].board[j][k]);
            }
            printf("]");
        }
        printf("], words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        //
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
                    if (pBoard[k]) {
                        free(pBoard[k]);
                        pBoard[k] = NULL;
                    }
                }
                free(pBoard);
                pBoard = NULL;
                return EXIT_FAILURE;
            }
            memset(pBoard[j], 0, testCase[i].boardColSize[j] * sizeof(char));
            memcpy(pBoard[j], testCase[i].board[j], testCase[i].boardColSize[j] * sizeof(char));
        }
        pAnswer = findWords(pBoard, testCase[i].boardSize, testCase[i].boardColSize, testCase[i].words,
                            testCase[i].wordsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        //
        printf("\n");

        //
        for (j = 0; j < testCase[i].boardSize; ++j) {
            if (pBoard[j]) {
                free(pBoard[j]);
            }
        }
        free(pBoard);
        pBoard = NULL;
        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
