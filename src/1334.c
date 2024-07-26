#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findTheCity(int n, int **edges, int edgesSize, int *edgesColSize, int distanceThreshold) {
    int retVal = 0;

    int answer[2];
    answer[0] = INT_MAX / 2;
    answer[1] = -1;

    int i, j, k;

    int distance[n][n];
    int adjacencyList[n][n];
    bool visit[n][n];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            distance[i][j] = INT_MAX / 2;
            adjacencyList[i][j] = INT_MAX / 2;
            visit[i][j] = false;
        }
    }

    int start, end, weight;
    for (i = 0; i < edgesSize; i++) {
        start = edges[i][0];
        end = edges[i][1];
        weight = edges[i][2];
        adjacencyList[start][end] = weight;
        adjacencyList[end][start] = weight;
    }

    int target;
    for (i = 0; i < n; ++i) {
        distance[i][i] = 0;
        for (j = 0; j < n; ++j) {
            target = -1;
            for (k = 0; k < n; ++k) {
                if ((visit[i][k] == false) && (target == -1 || distance[i][k] < distance[i][target])) {
                    target = k;
                }
            }

            for (k = 0; k < n; ++k) {
                distance[i][k] = fmin(distance[i][k], distance[i][target] + adjacencyList[target][k]);
            }
            visit[i][target] = true;
        }
    }

    int count;
    for (i = 0; i < n; ++i) {
        count = 0;
        for (j = 0; j < n; ++j) {
            if (distance[i][j] <= distanceThreshold) {
                count++;
            }
        }
        if (count <= answer[0]) {
            answer[0] = count;
            answer[1] = i;
        }
    }
    retVal = answer[1];

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (int)(100 * (100 - 1) / 2)
#define MAX_COL_SIZE (3)
    struct testCaseType {
        int n;
        int edges[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgesSize;
        int edgesColSize[MAX_ROW_SIZE];
        int distanceThreshold;
    } testCase[] = {{4, {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}}, 4, {3, 3, 3, 3}, 4},
                    {5, {{0, 1, 2}, {0, 4, 8}, {1, 2, 3}, {1, 4, 2}, {2, 3, 1}, {3, 4, 1}}, 6, {3, 3, 3, 3, 3, 3}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
     *  Output: 3
     *
     *  Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
     *  Output: 0
     */

    int **pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("], distanceThreshold = %d\n", testCase[i].distanceThreshold);

        pEdges = (int **)malloc(testCase[i].edgesSize * sizeof(int *));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int *)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges[k]);
                    pEdges[k] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }
        answer = findTheCity(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                             testCase[i].distanceThreshold);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            free(pEdges[j]);
            pEdges[j] = NULL;
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
