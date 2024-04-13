#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    int rowSize = matrixSize;
    if (rowSize == 0) {
        return 0;
    }
    int colSize = matrixColSize[0];

    int i, j;

    int left[rowSize][colSize];
    memset(left, 0, sizeof(left));
    for (i = 0; i < rowSize; i++) {
        for (j = 0; j < colSize; j++) {
            if (matrix[i][j] == '1') {
                left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
            }
        }
    }

    int up[rowSize], down[rowSize];
    int monotonicStack[rowSize];
    int monotonicStackTop = 0;
    int height, area;
    for (j = 0; j < colSize; j++) {
        memset(up, 0, sizeof(up));
        monotonicStackTop = 0;
        for (i = 0; i < rowSize; i++) {
            while ((monotonicStackTop > 0) && (left[monotonicStack[monotonicStackTop - 1]][j] >= left[i][j])) {
                monotonicStackTop--;
            }
            up[i] = monotonicStackTop == 0 ? -1 : monotonicStack[monotonicStackTop - 1];
            monotonicStack[monotonicStackTop++] = i;
        }

        memset(down, 0, sizeof(down));
        monotonicStackTop = 0;
        for (i = rowSize - 1; i >= 0; i--) {
            while ((monotonicStackTop > 0) && (left[monotonicStack[monotonicStackTop - 1]][j] >= left[i][j])) {
                monotonicStackTop--;
            }
            down[i] = monotonicStackTop == 0 ? rowSize : monotonicStack[monotonicStackTop - 1];
            monotonicStack[monotonicStackTop++] = i;
        }

        for (i = 0; i < rowSize; i++) {
            height = down[i] - up[i] - 1;
            area = height * left[i][j];
            retVal = fmax(retVal, area);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        char matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {
        {{{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}},
         4,
         {5, 5, 5, 5}},
        {{{'0'}}, 1, {1}},
        {{{'1'}}, 1, {1}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
     *  Output: 6
     *
     *  Input: matrix = [["0"]]
     *  Output: 0
     *
     *  Input: matrix = [["1"]]
     *  Output: 1
     */

    char** pMatrix = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s\"%c\"", (k == 0) ? "" : ",", testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMatrix = (char**)malloc(testCase[i].matrixSize * sizeof(char*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (char*)malloc(testCase[i].matrixColSize[j] * sizeof(char));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pMatrix[k]) {
                        free(pMatrix[k]);
                        pMatrix[k] = NULL;
                    }
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(char));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(char));
        }
        answer = maximalRectangle(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            if (pMatrix[j]) {
                free(pMatrix[j]);
                pMatrix[j] = NULL;
            }
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
