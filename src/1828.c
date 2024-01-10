#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countPoints(int** points, int pointsSize, int* pointsColSize, int** queries, int queriesSize, int* queriesColSize,
                 int* returnSize) {
    int* retVal = NULL;

    //
    (*returnSize) = queriesSize;
    retVal = (int*)malloc(((*returnSize)) * sizeof(int));
    if (retVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return retVal;
    }
    memset(retVal, 0, (((*returnSize)) * sizeof(int)));

    //
    int originX, originY, radius;
    int x, y;
    int count;
    int i, j;
    for (i = 0; i < queriesSize; ++i) {
        count = 0;

        originX = queries[i][0];
        originY = queries[i][1];
        radius = queries[i][2];
        for (j = 0; j < pointsSize; ++j) {
            x = points[j][0];
            y = points[j][1];

            if (pow(abs(originX - x), 2) + pow(abs(originY - y), 2) <= pow(radius, 2)) {
                ++count;
            }
        }

        retVal[i] = count;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_POINTS_ROW (500)
#define MAX_POINTS_COL (2)
#define MAX_QUERIES_ROW (500)
#define MAX_QUERIES_COL (3)
    struct testCaseType {
        int points[MAX_POINTS_ROW][MAX_POINTS_COL];
        int pointsSize;
        int pointsColSize[MAX_POINTS_ROW];
        int queries[MAX_QUERIES_ROW][MAX_QUERIES_COL];
        int queriesSize;
        int queriesColSize[MAX_QUERIES_ROW];
        int returnSize;
    } testCase[] = {
        {{{1, 3}, {3, 3}, {5, 3}, {2, 2}}, 4, {2, 2, 2, 2}, {{2, 3, 1}, {4, 3, 1}, {1, 1, 2}}, 3, {3, 3, 3}, 0},
        {{{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}},
         5,
         {2, 2, 2, 2, 2},
         {{1, 2, 2}, {2, 2, 2}, {4, 3, 2}, {4, 3, 3}},
         4,
         {3, 3, 3, 3},
         0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pPoints = NULL;
    int** pQueries = NULL;
    int* answer = NULL;
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
        printf("], queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].queries[j][k]);
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
        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pPoints == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].pointsSize; ++j) {
                free(pPoints[j]);
            }
            free(pPoints);
            pPoints = NULL;
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pQueries[k]);
                    pQueries[k] = NULL;
                }
                free(pQueries);
                pQueries = NULL;
                for (j = 0; j < testCase[i].pointsSize; ++j) {
                    free(pPoints[j]);
                }
                free(pPoints);
                pPoints = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        answer = countPoints(pPoints, testCase[i].pointsSize, testCase[i].pointsColSize, pQueries,
                             testCase[i].queriesSize, testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), answer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].pointsSize; ++j) {
            free(pPoints[j]);
        }
        free(pPoints);
        pPoints = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            free(pQueries[j]);
        }
        free(pQueries);
        pQueries = NULL;
        free(answer);
        answer = NULL;
    }

    return EXIT_SUCCESS;
}
