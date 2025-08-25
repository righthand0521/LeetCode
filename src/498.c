#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int rowSize = matSize;
    int colSize = matColSize[0];
    if ((rowSize == 0) || (colSize == 0)) {
        return pRetVal;
    }

    pRetVal = (int*)malloc((rowSize * colSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (rowSize * colSize) * sizeof(int));

    int row = 0;
    int column = 0;
    int direction = 1;
    while ((row < rowSize) && (column < colSize)) {
        pRetVal[(*returnSize)++] = mat[row][column];

        // Move along in the current diagonal depending upon the current direction.[i, j]->[i - 1, j + 1]
        // if going up and [ i, j ]->[i + 1][j - 1] if going down.
        int nextRow = row + ((direction == 1) ? (-1) : (1));
        int nextColumn = column + ((direction == 1) ? (1) : (-1));

        // Checking if the next element in the diagonal is within the bounds of the mat or not.
        // If it's not within the bounds, we have to find the next head.
        if ((nextRow < 0) || (nextRow == rowSize) || (nextColumn < 0) || (nextColumn == colSize)) {
            // If the current diagonal was going in the upwards direction.
            if (direction) {
                // For an upwards going diagonal having[i, j] as its tail
                // If[i, j + 1] is within bounds, then it becomes the next head.Otherwise, the element directly
                // below i.e.the element[i + 1, j] becomes the next head
                row += (column == colSize - 1);
                column += (column < colSize - 1);
            } else {
                // For a downwards going diagonal having[i, j] as its tail
                // if [i + 1, j] is within bounds, then it becomes the next head.Otherwise, the element directly
                // below i.e.the element[i, j + 1] becomes the next head
                column += (row == rowSize - 1);
                row += (row < rowSize - 1);
            }

            // Flip the direction
            direction = 1 - direction;
        } else {
            row = nextRow;
            column = nextColumn;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e3)
    struct testCaseType {
        int mat[MAX_SIZE][MAX_SIZE];
        int matSize;
        int matColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 3, {3, 3, 3}, 0}, {{{1, 2}, {3, 4}}, 2, {2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
     *  Output: [1,2,4,7,5,3,6,8,9]
     *
     *  Input: mat = [[1,2],[3,4]]
     *  Output: [1,2,3,4]
     */

    int** pMat = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: mat =  [");
        for (j = 0; j < testCase[i].matSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].matColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].mat[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMat = (int**)malloc(testCase[i].matSize * sizeof(int*));
        if (pMat == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matSize; ++j) {
            pMat[j] = (int*)malloc(testCase[i].matColSize[j] * sizeof(int));
            if (pMat[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pMat[k]) {
                        free(pMat[k]);
                        pMat[k] = NULL;
                    }
                }
                free(pMat);
                pMat = NULL;
                return EXIT_FAILURE;
            }
            memset(pMat[j], 0, testCase[i].matColSize[j] * sizeof(int));
            memcpy(pMat[j], testCase[i].mat[j], testCase[i].matColSize[j] * sizeof(int));
        }
        pAnswer = findDiagonalOrder(pMat, testCase[i].matSize, testCase[i].matColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].matSize; ++j) {
            if (pMat[j]) {
                free(pMat[j]);
                pMat[j] = NULL;
            }
        }
        free(pMat);
        pMat = NULL;
    }

    return EXIT_SUCCESS;
}
