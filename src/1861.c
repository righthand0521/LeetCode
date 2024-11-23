#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** rotateTheBox(char** box, int boxSize, int* boxColSize, int* returnSize, int** returnColumnSizes) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j;

    (*returnColumnSizes) = (int*)malloc(boxColSize[0] * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal = (char**)malloc(boxColSize[0] * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        return pRetVal;
    }
    for (i = 0; i < boxColSize[0]; ++i) {
        pRetVal[i] = (char*)malloc(boxSize * sizeof(char));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            return pRetVal;
        }
    }
    for (i = 0; i < boxColSize[0]; ++i) {
        for (j = 0; j < boxSize; ++j) {
            pRetVal[i][j] = '.';
        }
        (*returnColumnSizes)[i] = boxSize;
    }
    (*returnSize) = boxColSize[0];

    // Apply gravity to let stones fall to the lowest possible empty cell in each column
    int lowestRowWithEmptyCell;
    for (i = 0; i < boxSize; i++) {
        lowestRowWithEmptyCell = boxColSize[0] - 1;

        // Process each cell in row 'i' in reversed order
        for (j = boxColSize[0] - 1; j >= 0; j--) {
            // Found a stone - let it fall to the lowest empty cell
            if (box[i][j] == '#') {
                // Place it in the correct position in the rotated grid
                pRetVal[lowestRowWithEmptyCell][boxSize - i - 1] = '#';
                // (Optional - already initialized to '.') pRetVal[j][boxSize - i - 1] = '.';
                lowestRowWithEmptyCell--;
            }

            // Found an obstacle - reset 'lowestRowWithEmptyCell' to the row directly above it
            if (box[i][j] == '*') {
                // Place the obstacle in the correct position in the rotated grid
                pRetVal[j][boxSize - i - 1] = '*';
                lowestRowWithEmptyCell = j - 1;
            }
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500)
    struct testCaseType {
        char box[MAX_SIZE][MAX_SIZE];
        int boxSize;
        int boxColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{'#', '.', '#'}}, 3, {1, 1, 1}, 0, NULL},
                    {{{'#', '.', '*', '.'}, {'#', '#', '*', '.'}}, 2, {4, 4}, 0, NULL},
                    {{{'#', '#', '*', '.', '*', '.'}, {'#', '#', '#', '*', '.', '.'}, {'#', '#', '#', '.', '#', '.'}},
                     3,
                     {6, 6, 6},
                     0,
                     NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: box = [["#",".","#"]]
     *  Output: [["."],["#"],["#"]]
     *
     *  Input: box = [["#",".","*","."],["#","#","*","."]]
     *  Output: [["#","."],["#","#"],["*","*"],[".","."]]
     *
     *  Input: box = [["#","#","*",".","*","."],["#","#","#","*",".","."],["#","#","#",".","#","."]]
     *  Output: [[".","#","#"],[".","#","#"],["#","#","*"],["#","*","."],["#",".","*"],["#",".","."]]
     */

    char** pBox = NULL;
    char** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: box = [");
        for (j = 0; j < testCase[i].boxSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].boxColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0 ? "" : ","), testCase[i].box[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBox = (char**)malloc(testCase[i].boxSize * sizeof(char*));
        if (pBox == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].boxSize; ++j) {
            pBox[j] = (char*)malloc(testCase[i].boxColSize[j] * sizeof(char));
            if (pBox[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pBox[k]);
                }
                free(pBox);
                return EXIT_FAILURE;
            }
            memset(pBox[j], 0, (testCase[i].boxColSize[j] * sizeof(char)));
            memcpy(pBox[j], testCase[i].box[j], (testCase[i].boxColSize[j] * sizeof(char)));
        }

        pAnswer = rotateTheBox(pBox, testCase[i].boxSize, testCase[i].boxColSize, &testCase[i].returnSize,
                               &(testCase[i].returnColumnSizes));
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%c\"", (k == 0 ? "" : ","), pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].boxSize; ++j) {
            free(pBox[j]);
            pBox[j] = NULL;
        }
        free(pBox);
        pBox = NULL;
    }

    return EXIT_SUCCESS;
}
