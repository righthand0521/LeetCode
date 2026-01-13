#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(double limit_y, int** squares, int squaresSize, double totalArea) {
    bool retVal = false;

    double area = 0.0;
    int y, l;
    for (int i = 0; i < squaresSize; i++) {
        y = squares[i][1];
        l = squares[i][2];
        if (y < limit_y) {
            area += ((double)l * fmin(l, limit_y - y));
        }
    }
    retVal = (area >= totalArea / 2.0);

    return retVal;
}
double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double retVal = 0;

    double maxY = 0.0;
    double totalArea = 0.0;
    double y, l;
    for (int i = 0; i < squaresSize; i++) {
        y = squares[i][1];
        l = squares[i][2];
        totalArea += (double)l * l;
        if (y + l > maxY) {
            maxY = y + l;
        }
    }

    double eps = 1e-5;
    double left = 0.0;
    double right = maxY;
    double middle;
    while (fabs(right - left) > eps) {
        middle = (right + left) / 2.0;
        if (check(middle, squares, squaresSize, totalArea)) {
            right = middle;
        } else {
            left = middle;
        }
    }
    retVal = right;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        int squares[MAX_SIZE][3];
        int squaresSize;
        int squaresColSize[MAX_SIZE];
    } testCase[] = {{{{0, 0, 1}, {2, 2, 1}}, 2, {3, 3}}, {{{0, 0, 2}, {1, 1, 1}}, 2, {3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: squares = [[0,0,1],[2,2,1]]
     *  Output: 1.00000
     *
     *  Input: squares = [[0,0,2],[1,1,1]]
     *  Output: 1.16667
     */

    int** pSquares = NULL;
    double answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("squares = [");
        for (j = 0; j < testCase[i].squaresSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].squaresColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].squares[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pSquares = (int**)malloc(testCase[i].squaresSize * sizeof(int*));
        if (pSquares == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pSquares, 0, testCase[i].squaresSize * sizeof(int*));
        for (j = 0; j < testCase[i].squaresSize; ++j) {
            pSquares[j] = (int*)malloc(testCase[i].squaresColSize[j] * sizeof(int));
            if (pSquares[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pSquares[k]);
                    pSquares[k] = NULL;
                }
                free(pSquares);
                pSquares = NULL;
            }
            memset(pSquares[j], 0, (testCase[i].squaresColSize[j] * sizeof(int)));
            memcpy(pSquares[j], testCase[i].squares[j], (testCase[i].squaresColSize[j] * sizeof(int)));
        }
        answer = separateSquares(pSquares, testCase[i].squaresSize, testCase[i].squaresColSize);
        printf("Output: %.5f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].squaresSize; ++j) {
            free(pSquares[j]);
            pSquares[j] = NULL;
        }
        free(pSquares);
        pSquares = NULL;
    }

    return EXIT_SUCCESS;
}
