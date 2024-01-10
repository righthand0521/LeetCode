#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    bool retVal = false;

    // m == matrix.length, n == matrix[i].length, 1 <= n, m <= 300
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];

    /* Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
     *      0  1  2  3  4   |  0   1   2    3  4  |  0   1   2  3  4
     *  0   1  4  7 11 [15] |  1  [4] [7] [11] 15 |  1   4   7 11 15
     *  1   2  5  8 12  19  |  2   5   8   12  19 |  2  [5]  8 12 19
     *  2   3  6  9 16  22  |  3   6   9   16  22 |  3   6   9 16 22
     *  3  10 13 14 17  24  | 10  13  14   17  24 | 10  13  14 17 24
     *  4  18 21 23 26  30  | 18  21  23   26  30 | 18  21  23 26 30
     *
     * Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
     *      0  1  2  3  4   |  0  1  2  3   4  |  0  1  2   3   4 |  0   1    2   3  4 |   0   1  2  3  4
     *  0   1  4  7 11 [15] |  1  4  7 11  15  |  1  4  7  11  15 |  1   4    7  11 15 |   1   4  7 11 15
     *  1   2  5  8 12  19  |  2  5  8 12 [19] |  2  5  8  12  19 |  2   5    8  12 19 |   2   5  8 12 19
     *  2   3  6  9 16  22  |  3  6  9 16 [22] |  3  6  9 [16] 22 |  3   6    9  16 22 |   3   6  9 16 22
     *  3  10 13 14 17  24  | 10 13 14 17  24  | 10 13 14 [17] 24 | 10  13   14  17 24 |  10  13 14 17 24
     *  4  18 21 23 26  30  | 18 21 23 26  30  | 18 21 23 [26] 30 | 18 [21] [23] 26 30 | [18] 21 23 26 30
     */
    int value;
    int row = 0;
    int col = matrixCol - 1;
    while ((row < matrixRow) && (col >= 0)) {
        value = matrix[row][col];
        if (value == target) {
            retVal = true;
            break;
        } else if (value < target) {
            row++;
        } else if (value > target) {
            col--;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
        int target;
    } testCase[] = {
        {{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}},
         5,
         {5, 5, 5, 5, 5},
         3},
        {{{1, 4, 7, 11, 15}, {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}},
         5,
         {5, 5, 5, 5, 5},
         20}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
     *  Output: true
     *
     *  Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
     *  Output: false
     */

    int** pMatrix = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("], target = %d\n", testCase[i].target);

        pMatrix = (int**)malloc(testCase[i].matrixSize * sizeof(int*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (k = 0; k < testCase[i].matrixSize; ++k) {
            pMatrix[k] = (int*)malloc(testCase[i].matrixColSize[k] * sizeof(int));
            if (pMatrix[k] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].matrixSize; ++k) {
                    if (pMatrix[k]) {
                        free(pMatrix[k]);
                    }
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[k], 0, testCase[i].matrixColSize[k] * sizeof(int));
            memcpy(pMatrix[k], testCase[i].matrix[k], testCase[i].matrixColSize[k] * sizeof(int));
        }
        answer = searchMatrix(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize, testCase[i].target);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");

        for (k = 0; k < testCase[i].matrixSize; ++k) {
            if (pMatrix[k]) {
                free(pMatrix[k]);
            }
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
