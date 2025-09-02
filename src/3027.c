#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray(const void* a1, const void* a2) {
    const int* p1 = *(const int**)a1;
    const int* p2 = *(const int**)a2;

    // ascending order
    if (p1[0] == p2[0]) {
        return (p1[1] < p2[1]);
    }
    return (p1[0] > p2[0]);
}
int numberOfPairs(int** points, int pointsSize, int* pointsColSize) {
    int retVal = 0;

    qsort(points, pointsSize, sizeof(int*), compareIntArray);

    int *pointA, *pointB;
    int xMin, xMax, yMin, yMax;
    for (int i = 0; i < pointsSize - 1; i++) {
        pointA = points[i];
        xMin = pointA[0] - 1;
        xMax = INT_MAX;
        yMin = INT_MIN;
        yMax = pointA[1] + 1;

        for (int j = i + 1; j < pointsSize; j++) {
            pointB = points[j];
            if ((pointB[0] > xMin) && (pointB[0] < xMax) && (pointB[1] > yMin) && (pointB[1] < yMax)) {
                retVal++;
                xMin = pointB[0];
                yMin = pointB[1];
            }
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int points[MAX_SIZE][2];
        int pointsSize;
        int pointsColSize[MAX_SIZE];
    } testCase[] = {{{{1, 1}, {2, 2}, {3, 3}}, 3, {2, 2, 2}},
                    {{{6, 2}, {4, 4}, {2, 6}}, 3, {2, 2, 2}},
                    {{{3, 1}, {1, 3}, {1, 1}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: points = [[1,1],[2,2],[3,3]]
     *  Output: 0
     *
     *  Input: points = [[6,2],[4,4],[2,6]]
     *  Output: 2
     *
     *  Input: points = [[3,1],[1,3],[1,1]]
     *  Output: 2
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
        answer = numberOfPairs(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize);
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
