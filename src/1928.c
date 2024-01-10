#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constraints
 *  n == passingFees.length
 *  2 <= n <= 1000
 *  1 <= passingFees[j] <= 1000
 */
#define MAX_PASSINGFEES (1000 * 1000 + 1)
int minCost(int maxTime, int** edges, int edgesSize, int* edgesColSize, int* passingFees, int passingFeesSize) {
    int retVal = -1;

    int i, j;

    int fee[(maxTime + 1)][passingFeesSize];
    for (i = 0; i < (maxTime + 1); ++i) {
        for (j = 0; j < passingFeesSize; ++j) {
            fee[i][j] = MAX_PASSINGFEES;
        }
    }
    fee[0][0] = passingFees[0];

    int x, y, time;
    for (int i = 1; i <= maxTime; ++i) {
        for (j = 0; j < edgesSize; ++j) {
            x = edges[j][0];
            y = edges[j][1];
            time = edges[j][2];
            if (time <= i) {
                fee[i][x] = fmin(fee[i][x], fee[i - time][y] + passingFees[x]);
                fee[i][y] = fmin(fee[i][y], fee[i - time][x] + passingFees[y]);
            }
        }
    }

    int minFee = MAX_PASSINGFEES;
    for (i = 1; i <= maxTime; ++i) {
        minFee = fmin(minFee, fee[i][passingFeesSize - 1]);
    }

    if (minFee != MAX_PASSINGFEES) {
        retVal = minFee;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int maxTime;
        int edges[MAX_SIZE][3];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int passingFees[MAX_SIZE];
        int passingFeesSize;
    } testCase[] = {{30,
                     {{0, 1, 10}, {1, 2, 10}, {2, 5, 10}, {0, 3, 1}, {3, 4, 10}, {4, 5, 15}},
                     6,
                     {3, 3, 3, 3, 3, 3},
                     {5, 1, 2, 20, 20, 3},
                     6},
                    {29,
                     {{0, 1, 10}, {1, 2, 10}, {2, 5, 10}, {0, 3, 1}, {3, 4, 10}, {4, 5, 15}},
                     6,
                     {3, 3, 3, 3, 3, 3},
                     {5, 1, 2, 20, 20, 3},
                     6},
                    {25,
                     {{0, 1, 10}, {1, 2, 10}, {2, 5, 10}, {0, 3, 1}, {3, 4, 10}, {4, 5, 15}},
                     6,
                     {3, 3, 3, 3, 3, 3},
                     {5, 1, 2, 20, 20, 3},
                     6}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: maxTime = %d, edges = [", testCase[i].maxTime);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("], passingFees = [");
        for (j = 0; j < testCase[i].passingFeesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].passingFees[j]);
        }
        printf("]\n");

        pEdges = (int**)malloc(testCase[i].edgesSize * sizeof(int*));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int*)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pEdges[k]) {
                        free(pEdges[k]);
                        pEdges[k] = NULL;
                    }
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, testCase[i].edgesColSize[j] * sizeof(int));
            memcpy(pEdges[j], testCase[i].edges[j], testCase[i].edgesColSize[j] * sizeof(int));
        }
        answer = minCost(testCase[i].maxTime, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                         testCase[i].passingFees, testCase[i].passingFeesSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            if (pEdges[j]) {
                free(pEdges[j]);
                pEdges[j] = NULL;
            }
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
