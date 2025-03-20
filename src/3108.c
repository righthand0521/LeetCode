#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/minimum-cost-walk-in-weighted-graph/solutions/2727524/dai-quan-tu-li-lu-tu-de-zui-xiao-dai-jie-6tds/
int findParent(int* parent, int x) {
    int retVal;

    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    retVal = x;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minimumCost(int n, int** edges, int edgesSize, int* edgesColSize, int** query, int querySize, int* queryColSize,
                 int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    const int fullWeight = 0x7FFFFFFF;
    int x = 0;

    int parent[n];
    int weight[n];
    for (x = 0; n > x; x++) {
        parent[x] = x;
        weight[x] = fullWeight;
    }

    int e0 = 0, e1 = 0, p0 = 0, p1 = 0;
    for (x = 0; edgesSize > x; x++) {
        e0 = fmin(edges[x][0], edges[x][1]);
        e1 = fmax(edges[x][0], edges[x][1]);
        p0 = findParent(parent, e0);
        p1 = findParent(parent, e1);
        if (p0 != p1) {
            weight[p1] &= weight[p0];
            parent[p0] = p1;
        }
        weight[p1] &= edges[x][2];
    }

    pRetVal = (int*)calloc(querySize, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        return pRetVal;
    }
    for (x = 0; querySize > x; x++) {
        if (query[x][0] == query[x][1]) {
            pRetVal[x] = 0;
        } else {
            p0 = findParent(parent, query[x][0]);
            p1 = findParent(parent, query[x][1]);
            if (p0 == p1) {
                pRetVal[x] = weight[p0];
            } else {
                pRetVal[x] = -1;
            }
        }
    }
    (*returnSize) = querySize;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][3];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int query[MAX_SIZE][2];
        int querySize;
        int queryColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{5, {{0, 1, 7}, {1, 3, 7}, {1, 2, 1}}, 3, {3, 3, 3}, {{0, 3}, {3, 4}}, 2, {2, 2}},
                    {3, {{0, 2, 7}, {0, 1, 15}, {1, 2, 6}, {1, 2, 1}}, 4, {3, 3, 3, 3}, {{1, 2}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, edges = [[0,1,7],[1,3,7],[1,2,1]], query = [[0,3],[3,4]]
     *  Output: [1,-1]
     *
     *  Input: n = 3, edges = [[0,2,7],[0,1,15],[1,2,6],[1,2,1]], query = [[1,2]]
     *  Output: [0]
     */

    int** pEdges = NULL;
    int** pQuery = NULL;
    int* pAnswer = NULL;
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
        printf("], query = [");
        for (j = 0; j < testCase[i].querySize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].queryColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].query[j][k]);
            }
            printf("]");
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
        pQuery = (int**)malloc(testCase[i].querySize * sizeof(int*));
        if (pQuery == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].querySize; ++j) {
            pQuery[j] = (int*)malloc(testCase[i].queryColSize[j] * sizeof(int));
            if (pQuery[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pQuery[k]);
                    pQuery[k] = NULL;
                }
                free(pQuery);
                pQuery = NULL;
                for (j = 0; j < testCase[i].querySize; ++j) {
                    free(pEdges[j]);
                    pEdges[j] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pQuery[j], 0, (testCase[i].queryColSize[j] * sizeof(int)));
            memcpy(pQuery[j], testCase[i].query[j], (testCase[i].queryColSize[j] * sizeof(int)));
        }

        pAnswer = minimumCost(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize, pQuery,
                              testCase[i].querySize, testCase[i].queryColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].querySize; ++j) {
            free(pQuery[j]);
            pQuery[j] = NULL;
        }
        free(pQuery);
        pQuery = NULL;
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            free(pEdges[j]);
            pEdges[j] = NULL;
        }
        free(pEdges);
        pEdges = NULL;
    }

    return EXIT_SUCCESS;
}
