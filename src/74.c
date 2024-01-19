#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BINARY_SEARCH (0)
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    bool retVal = false;

    // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 100
    int matrixRow = matrixSize;
    int matrixCol = matrixColSize[0];

#if (BINARY_SEARCH)
    int middle, middleValue;
    int left = 0;
    int right = matrixRow * matrixCol - 1;
    while (left <= right) {
        middle = left + (right - left) / 2;

        middleValue = matrix[middle / matrixCol][middle % matrixCol];
        if (middleValue == target) {
            retVal = true;
            break;
        } else if (middleValue < target) {
            left = middle + 1;
        } else if (middleValue > target) {
            right = middle - 1;
        }
    }
#else
    /* Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3; Output: true
     *      0  1  2   3  |  0  1  2   3  |  0  1   2  3
     *  0   1  3  5  [7] |  1  3 [5]  7  |  1 [3]  5  7
     *  1  10 11 16  20  | 10 11 16  20  | 10 11  16 20
     *  2  23 30 34  60  | 23 30 34  60  | 23 30  34 60
     *
     * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13; Output: false
     *      0  1  2   3  |  0  1  2   3  |  0   1   2   3 |  0   1   2  3 |  0   1   2  3 |   0   1  2  3
     *  0   1  3  5  [7] |  1  3  5   7  |  1   3   5   7 |  1   3   5  7 |  1   3   5  7 |   1   3  5  7
     *  1  10 11 16  20  | 10 11 16 [20] | 10  11 [16] 20 | 10 [11] 16 20 | 10  11  16 20 |  10  11 16 20
     *  2  23 30 34  60  | 23 30 34  60  | 23  30  34  60 | 23  30  34 60 | 23 [30] 34 60 | [23] 30 34 60
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
#endif

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
        int target;
    } testCase[] = {{{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 3, {4, 4, 4}, 3},
                    {{{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}}, 3, {4, 4, 4}, 13},
                    {{{1}}, 1, {1}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
     *  Output: true
     *
     *  Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
     *  Output: false
     *
     *  Input: matrix = [[1]], target = 0
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
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (int*)malloc(testCase[i].matrixColSize[j] * sizeof(int));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pMatrix[k]);
                    pMatrix[k] = NULL;
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, (testCase[i].matrixColSize[j] * sizeof(int)));
            memcpy(pMatrix[j], testCase[i].matrix[j], (testCase[i].matrixColSize[j] * sizeof(int)));
        }
        answer = searchMatrix(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize, testCase[i].target);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            free(pMatrix[j]);
            pMatrix[j] = NULL;
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
