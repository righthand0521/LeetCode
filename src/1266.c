#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minTimeToVisitAllPoints(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    int diffX, diffY;
    int i;
    for (i = 1; i < pointsSize; ++i) {
        diffX = abs(points[i - 1][0] - points[i][0]);
        diffY = abs(points[i - 1][1] - points[i][1]);
        retVal += fmax(diffX, diffY);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int points[MAX_SIZE][2];
        int pointsSize;
        int pointsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1}, {3, 4}, {-1, 0}}, 3, {2, 2, 2}}, {{{3, 2}, {-2, 2}}, 2, {2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[1,1],[3,4],[-1,0]]
     *  Output: 7
     *
     *  Input: points = [[3,2],[-2,2]]
     *  Output: 5
     */

    int** pPoints = NULL;
    int answer = 0;
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
        answer = minTimeToVisitAllPoints(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
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
