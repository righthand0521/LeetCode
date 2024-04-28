#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dfs(int u, int f, int* sz, int* dp, int* hd, int* nx, int* e) {
    sz[u] = 1;
    dp[u] = 0;

    int v;
    int i;
    for (i = hd[u]; i; i = nx[i]) {
        v = e[i];
        if (v == f) {
            continue;
        }

        dfs(v, u, sz, dp, hd, nx, e);

        dp[u] += (dp[v] + sz[v]);
        sz[u] += sz[v];
    }
}
void dfs2(int u, int f, int* sz, int* dp, int* hd, int* nx, int* e, int* pRetVal) {
    pRetVal[u] = dp[u];

    int v, pu, pv, su, sv;
    int i;
    for (i = hd[u]; i; i = nx[i]) {
        v = e[i];
        if (v == f) {
            continue;
        }

        pu = dp[u];
        pv = dp[v];
        su = sz[u];
        sv = sz[v];

        dp[u] -= dp[v] + sz[v];
        sz[u] -= sz[v];
        dp[v] += dp[u] + sz[u];
        sz[v] += sz[u];

        dfs2(v, u, sz, dp, hd, nx, e, pRetVal);

        dp[u] = pu;
        dp[v] = pv;
        sz[u] = su;
        sz[v] = sv;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sumOfDistancesInTree(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    int* pRetVal = NULL;

    //
    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (n * sizeof(int)));
    (*returnSize) = n;

    //
    int* sz = malloc(n * sizeof(int));
    if (sz == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(sz, 0, (n * sizeof(int)));
    //
    int* dp = malloc(n * sizeof(int));
    if (dp == NULL) {
        perror("malloc");
        goto szExit;
        return pRetVal;
    }
    memset(dp, 0, (n * sizeof(int)));
    //
    int* hd = malloc(n * sizeof(int));
    if (hd == NULL) {
        perror("malloc");
        goto dpExit;
        return pRetVal;
    }
    memset(hd, 0, (n * sizeof(int)));
    //
    int adjacencySize = edgesSize * 2 + 1;
    int* nx = malloc(adjacencySize * sizeof(int));
    if (nx == NULL) {
        perror("malloc");
        goto hdExit;
        return pRetVal;
    }
    memset(nx, 0, (adjacencySize * sizeof(int)));
    //
    int* e = malloc(adjacencySize * sizeof(int));
    if (e == NULL) {
        perror("malloc");
        goto nxExit;
        return pRetVal;
    }
    memset(e, 0, (adjacencySize * sizeof(int)));
    int src, dst;
    int i, num;
    for (i = 0, num = 0; i < edgesSize; i++) {
        src = edges[i][0];
        dst = edges[i][1];

        nx[++num] = hd[src];
        hd[src] = num;
        e[num] = dst;

        nx[++num] = hd[dst];
        hd[dst] = num;
        e[num] = src;
    }

    //
    dfs(0, -1, sz, dp, hd, nx, e);
    dfs2(0, -1, sz, dp, hd, nx, e, pRetVal);

    //
    free(e);
    e = NULL;
nxExit:
    free(nx);
    nx = NULL;
hdExit:
    free(hd);
    hd = NULL;
dpExit:
    free(dp);
    dp = NULL;
szExit:
    free(sz);
    sz = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{6, {{0, 1}, {0, 2}, {2, 3}, {2, 4}, {2, 5}}, 5, {2, 2, 2, 2, 2}, 0},
                    {1, {{}}, 0, {}, 0},
                    {2, {{1, 0}}, 1, {2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
     *  Output: [8,12,6,10,10,10]
     *
     *  Input: n = 1, edges = []
     *  Output: [0]
     *
     *  Input: n = 2, edges = [[1,0]]
     *  Output: [1,1]
     */

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
