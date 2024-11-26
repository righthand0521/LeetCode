#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findChampion(int n, int **edges, int edgesSize, int *edgesColSize) {
    int retVal = -1;

    int indegree[n];
    memset(indegree, 0, sizeof(indegree));

    int i;
    for (i = 0; i < edgesSize; ++i) {
        indegree[edges[i][1]] += 1;
    }

    for (i = 0; i < n; ++i) {
        if (indegree[i] != 0) {
            continue;
        }

        if (retVal == -1) {
            retVal = i;
        } else {
            retVal = -1;
            break;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (int)(100 * (100 - 1) / 2)
#define MAX_COL_SIZE (2)
    struct testCaseType {
        int n;
        int edges[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgesSize;
        int edgesColSize[MAX_ROW_SIZE];
    } testCase[] = {{3, {{0, 1}, {1, 2}}, 2, {2, 2}}, {4, {{0, 2}, {1, 3}, {1, 2}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, edges = [[0,1],[1,2]]
     *  Output: 0
     *
     *  Input: n = 4, edges = [[0,2],[1,3],[1,2]]
     *  Output: -1
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
        printf("]\n");

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
        answer = findChampion(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize);
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
