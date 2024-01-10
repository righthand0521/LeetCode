#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *ans, *sz, *dp;
int *hd, *nx, *e;
void dfs(int u, int f) {
    sz[u] = 1;
    dp[u] = 0;
    for (int i = hd[u]; i; i = nx[i]) {
        int v = e[i];
        if (v == f) {
            continue;
        }
        dfs(v, u);
        dp[u] += dp[v] + sz[v];
        sz[u] += sz[v];
    }
}
void dfs2(int u, int f) {
    ans[u] = dp[u];
    for (int i = hd[u]; i; i = nx[i]) {
        int v = e[i];
        if (v == f) {
            continue;
        }
        int pu = dp[u], pv = dp[v];
        int su = sz[u], sv = sz[v];

        dp[u] -= dp[v] + sz[v];
        sz[u] -= sz[v];
        dp[v] += dp[u] + sz[u];
        sz[v] += sz[u];

        dfs2(v, u);

        dp[u] = pu, dp[v] = pv;
        sz[u] = su, sz[v] = sv;
    }
}
int* sumOfDistancesInTree(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    ans = malloc(sizeof(int) * n);
    sz = malloc(sizeof(int) * n);
    dp = malloc(sizeof(int) * n);
    hd = malloc(sizeof(int) * n);
    nx = malloc(sizeof(int) * (edgesSize * 2 + 1));
    e = malloc(sizeof(int) * (edgesSize * 2 + 1));
    for (int i = 0; i < n; i++) {
        ans[i] = sz[i] = dp[i] = hd[i] = 0;
    }
    for (int i = 0, num = 0; i < edgesSize; i++) {
        int u = edges[i][0], v = edges[i][1];
        nx[++num] = hd[u], hd[u] = num, e[num] = v;
        nx[++num] = hd[v], hd[v] = num, e[num] = u;
    }
    dfs(0, -1);
    dfs2(0, -1);
    *returnSize = n;

    free(sz);
    free(dp);
    free(hd);
    free(nx);
    free(e);

    return ans;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 100)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][MAX_SIZE];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{6, {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}}, 5, {2, 2, 2, 2, 2}, 0},
                    {1, {{}}, 0, {}, 0},
                    {2, {{1, 0}}, 1, {2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pEdges = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges =  [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEdges = (int**)malloc(testCase[i].edgesSize * sizeof(int*));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (k = 0; k < testCase[i].edgesSize; ++k) {
            pEdges[k] = (int*)malloc(testCase[i].edgesColSize[k] * sizeof(int));
            if (pEdges[k] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].edgesSize; ++k) {
                    if (pEdges[k]) {
                        free(pEdges[k]);
                    }
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[k], 0, testCase[i].edgesColSize[k] * sizeof(int));
            memcpy(pEdges[k], testCase[i].edges[k], testCase[i].edgesColSize[k] * sizeof(int));
        }
        pAnswer = sumOfDistancesInTree(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                       &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].edgesSize; ++j) {
            free(pEdges[j]);
            pEdges[j] = NULL;
        }
        free(pEdges);
        pEdges = NULL;

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}