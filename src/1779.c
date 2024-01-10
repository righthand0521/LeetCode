#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nearestValidPoint(int x, int y, int** points, int pointsSize, int* pointsColSize) {
    int retVal = -1;

    int distance;
    int minDistance = INT_MAX;
    int i;
    for (i = pointsSize - 1; i >= 0; --i) {
        if ((x != points[i][0]) && (y != points[i][1])) {
            continue;
        } else if ((x == points[i][0]) && (y == points[i][1])) {
            distance = 0;
        } else if (x == points[i][0]) {
            distance = abs(y - points[i][1]);
        } else if (y == points[i][1]) {
            distance = abs(x - points[i][0]);
        }

        if (distance <= minDistance) {
            minDistance = distance;
            retVal = i;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW (10000)
#define MAX_COL (2)
    struct testCaseType {
        int x;
        int y;
        int points[MAX_ROW][MAX_COL];
        int pointsSize;
        int pointsColSize[MAX_ROW];
    } testCase[] = {{3, 4, {{1, 2}, {3, 1}, {2, 4}, {2, 3}, {4, 4}}, 5, {2, 2, 2, 2, 2}},
                    {3, 4, {{3, 4}}, 1, {2}},
                    {3, 4, {{2, 3}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pPoints = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: x = %d, y = %d, points = [", testCase[i].x, testCase[i].y);
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
        answer =
            nearestValidPoint(testCase[i].x, testCase[i].y, pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].pointsSize; ++j) {
            free(pPoints[j]);
        }
        free(pPoints);
        pPoints = NULL;
    }

    return EXIT_SUCCESS;
}
