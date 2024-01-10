#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maximalNetworkRank(int n, int** roads, int roadsSize, int* roadsColSize) {
    int retVal = 0;

    int i, j;

    int connect[n][n];
    memset(connect, 0, sizeof(connect));
    int degree[n];
    memset(degree, 0, sizeof(degree));
    int a, b;
    for (i = 0; i < roadsSize; i++) {
        a = roads[i][0];
        b = roads[i][1];
        connect[a][b] = 1;
        connect[b][a] = 1;
        degree[a]++;
        degree[b]++;
    }

    int rank;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            rank = degree[i] + degree[j] - connect[i][j];
            retVal = fmax(retVal, rank);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int n;
        int roads[MAX_SIZE][2];
        int roadsSize;
        int roadsColSize[MAX_SIZE];
    } testCase[] = {{4, {{0, 1}, {0, 3}, {1, 2}, {1, 3}}, 4, {2, 2, 2, 2}},
                    {5, {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}}, 6, {2, 2, 2, 2, 2, 2, 2}},
                    {8, {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {5, 6}, {5, 7}}, 6, {2, 2, 2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
     *  Output: 4
     *
     *  Input: n = 5, roads = [[0,1],[0,3],[1,2],[1,3],[2,3],[2,4]]
     *  Output: 5
     *
     *  Input: n = 8, roads = [[0,1],[1,2],[2,3],[2,4],[5,6],[5,7]]
     *  Output: 5
     */

    int** pRoads = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, roads = [", testCase[i].n);
        for (j = 0; j < testCase[i].roadsSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].roadsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].roads[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRoads = (int**)malloc(testCase[i].roadsSize * sizeof(int*));
        if (pRoads == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].roadsSize; ++j) {
            pRoads[j] = (int*)malloc(testCase[i].roadsColSize[j] * sizeof(int));
            if (pRoads[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pRoads[k]) {
                        free(pRoads[k]);
                        pRoads[k] = NULL;
                    }
                }
                free(pRoads);
                pRoads = NULL;
                return EXIT_FAILURE;
            }
            memset(pRoads[j], 0, testCase[i].roadsColSize[j] * sizeof(int));
            memcpy(pRoads[j], testCase[i].roads[j], testCase[i].roadsColSize[j] * sizeof(int));
        }
        answer = maximalNetworkRank(testCase[i].n, pRoads, testCase[i].roadsSize, testCase[i].roadsColSize);

        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].roadsSize; ++j) {
            if (pRoads[j]) {
                free(pRoads[j]);
                pRoads[j] = NULL;
            }
        }
        free(pRoads);
        pRoads = NULL;
    }

    return EXIT_SUCCESS;
}
