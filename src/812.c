#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double triangleArea(int x1, int y1, int x2, int y2, int x3, int y3) {
    double retVal = 0.5 * abs((x1 * y2) + (x2 * y3) + (x3 * y1) - (x1 * y3) - (x2 * y1) - (x3 * y2));

    return retVal;
}
double largestTriangleArea(int** points, int pointsSize, int* pointsColSize) {
    double retVal = 0;

    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            for (int k = j + 1; k < pointsSize; k++) {
                retVal = fmax(retVal, triangleArea(points[i][0], points[i][1], points[j][0], points[j][1], points[k][0],
                                                   points[k][1]));
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (50)
#define MAX_COL (2)
    struct testCaseType {
        int points[MAX_ROW][MAX_COL];
        int pointsSize;
        int pointsColSize[MAX_ROW];
    } testCase[] = {{{{0, 0}, {0, 1}, {1, 0}, {0, 2}, {2, 0}}, 5, {2, 2, 2, 2, 2}},
                    {{{1, 0}, {0, 0}, {0, 1}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
     *  Output: 2.00000
     *
     *  Input: points = [[1,0],[0,0],[0,1]]
     *  Output: 0.50000
     */

    int** pPoints = NULL;
    double answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: points = [");
        for (j = 0; j < testCase[i].pointsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pointsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].points[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPoints = (int**)malloc(testCase[i].pointsSize * sizeof(int*));
        if (pPoints == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pointsSize; ++j) {
            pPoints[j] = (int*)malloc(testCase[i].pointsColSize[j] * sizeof(int));
            if (pPoints[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPoints[k]);
                    pPoints[k] = NULL;
                }
                free(pPoints);
                pPoints = NULL;
                return EXIT_FAILURE;
            }
            memset(pPoints[j], 0, testCase[i].pointsColSize[j] * sizeof(int));
            memcpy(pPoints[j], testCase[i].points[j], testCase[i].pointsColSize[j] * sizeof(int));
        }
        answer = largestTriangleArea(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
        printf("Output: %.5f\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pointsSize; ++j) {
            free(pPoints[j]);
        }
        free(pPoints);
        pPoints = NULL;
    }

    return EXIT_SUCCESS;
}
