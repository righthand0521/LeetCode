#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/minimum-time-to-collect-all-apples-in-a-tree/solutions/746413/c-mo-ni-lin-jie-ju-zhen-by-big0range-0t8q/
bool dfs(int n, bool *hasApple, int hasAppleSize, int index, int **adjacent, int *adjacentColSize, int *retVal) {
    if (index >= n) {
        return false;
    }
    int len = adjacentColSize[index];

    adjacentColSize[index] = 0;
    bool flag = false;
    int i;
    for (i = 0; i < len; ++i) {
        if (adjacentColSize[adjacent[index][i]] == 0) {
            continue;
        }

        if (dfs(n, hasApple, hasAppleSize, adjacent[index][i], adjacent, adjacentColSize, retVal) == false) {
            continue;
        }

        (*retVal) += 2;
        flag = true;
    }

    return (hasApple[index] || flag);
}
int minTime(int n, int **edges, int edgesSize, int *edgesColSize, bool *hasApple, int hasAppleSize) {
    int retVal = 0;

    int i, j;

    int *adjacentColSize = (int *)malloc(n * sizeof(int));
    if (adjacentColSize == NULL) {
        perror("malloc");
        return retVal;
    }
    memset(adjacentColSize, 0, (n * sizeof(int)));

#define MAX_ADJACENT_LEN (20)
    int **adjacent = (int **)malloc(n * sizeof(int *));
    if (adjacent == NULL) {
        perror("malloc");
        free(adjacentColSize);
        adjacentColSize = NULL;
        return retVal;
    }
    for (i = 0; i < n; ++i) {
        adjacent[i] = (int *)malloc(MAX_ADJACENT_LEN * sizeof(int));
        if (adjacent[i] == NULL) {
            perror("malloc");
            free(adjacentColSize);
            adjacentColSize = NULL;
            for (j = 0; j < i; ++j) {
                free(adjacent[j]);
                adjacent[j] = NULL;
            }
            free(adjacent);
            adjacent = NULL;
            return retVal;
        }
        memset(adjacent[i], 0, (MAX_ADJACENT_LEN * sizeof(int)));
    }

    for (i = 0; i < edgesSize; ++i) {
        adjacent[edges[i][0]][(adjacentColSize[edges[i][0]])++] = edges[i][1];
        adjacent[edges[i][1]][(adjacentColSize[edges[i][1]])++] = edges[i][0];
    }
#if (DEBUG)
    for (i = 0; i < n; ++i) {
        printf("%d: ", i);
        for (j = 0; j < adjacentColSize[i]; ++j) {
            printf("%d ", adjacent[i][j]);
        }
        printf("\n");
    }
#endif

    dfs(n, hasApple, hasAppleSize, 0, adjacent, adjacentColSize, &retVal);
    free(adjacentColSize);
    adjacentColSize = NULL;
    for (i = 0; i < n; ++i) {
        free(adjacent[i]);
        adjacent[i] = NULL;
    }
    free(adjacent);
    adjacent = NULL;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        bool hasApple[MAX_SIZE];
        int hasAppleSize;
    } testCase[] = {{7,
                     {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}},
                     6,
                     {2, 2, 2, 2, 2, 2},
                     {false, false, true, false, true, true, false},
                     7},
                    {7,
                     {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}},
                     6,
                     {2, 2, 2, 2, 2, 2},
                     {false, false, true, false, false, true, false},
                     7},
                    {7,
                     {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}},
                     6,
                     {2, 2, 2, 2, 2, 2},
                     {false, false, false, false, false, false, false},
                     7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int **pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("], hasApple = [");
        for (j = 0; j < testCase[i].hasAppleSize; ++j) {
            printf("%s%s", (j == 0 ? "" : ","), (testCase[i].hasApple[j] == true ? "true" : "false"));
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
                    if (pEdges[k]) {
                        free(pEdges[k]);
                    }
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, testCase[i].edgesColSize[j] * sizeof(int));
            memcpy(pEdges[j], testCase[i].edges[j], testCase[i].edgesColSize[j] * sizeof(int));
        }

        answer = minTime(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize, testCase[i].hasApple,
                         testCase[i].hasAppleSize);

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
