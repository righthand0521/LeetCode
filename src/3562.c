#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct {
    int* dp0;
    int* dp1;
    int size;
} Result;
struct ListNode* creatListNode(int val) {
    struct ListNode* pRetVal = NULL;

    pRetVal = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    pRetVal->val = val;
    pRetVal->next = NULL;

    return pRetVal;
}
void freeList(struct ListNode* list) {
    struct ListNode* p = NULL;
    while (list) {
        p = list;
        list = list->next;
        free(p);
    }
}
void dfs(int u, int n, int* present, int* future, struct ListNode** g, int budget, Result* result, int* visited) {
    if (visited[u]) {
        return;
    }
    visited[u] = 1;

    int cost = present[u];
    int dCost = present[u] / 2;

    // dp[u][state][budget]
    // state = 0: Do not purchase parent node, state = 1: Must purchase parent node
    int* dp0 = (int*)calloc(budget + 1, sizeof(int));
    int* dp1 = (int*)calloc(budget + 1, sizeof(int));

    // subProfit[state][budget]
    // state = 0: discount not available, state = 1: discount available
    int* subProfit0 = (int*)calloc(budget + 1, sizeof(int));
    int* subProfit1 = (int*)calloc(budget + 1, sizeof(int));

    int uSize = cost;

    for (struct ListNode* p = g[u]; p; p = p->next) {
        int v = p->val;
        Result childResult;
        childResult.dp0 = NULL;
        childResult.dp1 = NULL;
        childResult.size = 0;
        dfs(v, n, present, future, g, budget, &childResult, visited);

        uSize += childResult.size;
        for (int j = budget; j >= 0; j--) {
            for (int sub = 0; sub <= fmin(childResult.size, j); sub++) {
                if (j - sub >= 0) {
                    subProfit0[j] = fmax(subProfit0[j], subProfit0[j - sub] + childResult.dp0[sub]);
                    subProfit1[j] = fmax(subProfit1[j], subProfit1[j - sub] + childResult.dp1[sub]);
                }
            }
        }

        free(childResult.dp0);
        free(childResult.dp1);
    }

    for (int i = 0; i <= budget; i++) {
        dp0[i] = subProfit0[i];
        dp1[i] = subProfit0[i];
        if (i >= dCost) {
            dp1[i] = fmax(subProfit0[i], subProfit1[i - dCost] + future[u] - dCost);
        }
        if (i >= cost) {
            dp0[i] = fmax(subProfit0[i], subProfit1[i - cost] + future[u] - cost);
        }
    }

    result->dp0 = dp0;
    result->dp1 = dp1;
    result->size = uSize;

    free(subProfit0);
    free(subProfit1);
}
int maxProfit(int n, int* present, int presentSize, int* future, int futureSize, int** hierarchy, int hierarchySize,
              int* hierarchyColSize, int budget) {
    int retVal = 0;

    struct ListNode** g = (struct ListNode**)malloc(n * sizeof(struct ListNode*));
    if (g == NULL) {
        perror("malloc");
        return retVal;
    }
    for (int i = 0; i < n; i++) {
        g[i] = NULL;
    }
    struct ListNode* p;
    int u, v;
    for (int i = 0; i < hierarchySize; i++) {
        u = hierarchy[i][0] - 1;
        v = hierarchy[i][1] - 1;
        p = creatListNode(v);
        if (p == NULL) {
            for (int j = 0; j < n; j++) {
                freeList(g[j]);
            }
            free(g);
            return retVal;
        }
        p->next = g[u];
        g[u] = p;
    }

    int* visited = (int*)calloc(n, sizeof(int));
    if (visited == NULL) {
        perror("malloc");
        for (int j = 0; j < n; j++) {
            freeList(g[j]);
        }
        free(g);
        return retVal;
    }

    Result result;
    result.dp0 = NULL;
    result.dp1 = NULL;
    result.size = 0;

    dfs(0, n, present, future, g, budget, &result, visited);
    retVal = result.dp0[budget];

    //
    free(result.dp0);
    free(result.dp1);
    free(visited);
    for (int i = 0; i < n; i++) {
        freeList(g[i]);
    }
    free(g);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (160)
    struct testCaseType {
        int n;
        int present[MAX_SIZE];
        int presentSize;
        int future[MAX_SIZE];
        int futureSize;
        int hierarchy[MAX_SIZE][MAX_SIZE];
        int hierarchySize;
        int hierarchyColSize[MAX_SIZE];
        int budget;
    } testCase[] = {{2, {1, 2}, 2, {4, 3}, 2, {{1, 2}}, 1, {2}, 3},
                    {2, {3, 4}, 2, {5, 8}, 2, {{1, 2}}, 1, {2}, 4},
                    {3, {4, 6, 8}, 3, {7, 9, 11}, 3, {{1, 2}, {1, 3}}, 2, {2, 2}, 10},
                    {3, {5, 2, 3}, 3, {8, 5, 6}, 3, {{1, 2}, {2, 3}}, 2, {2, 2}, 7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
     *  Output: 5
     *
     *  Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget = 4
     *  Output: 4
     *
     *  Input: n = 3, present = [4,6,8], future = [7,9,11], hierarchy = [[1,2],[1,3]], budget = 10
     *  Output: 10
     *
     *  Input: n = 3, present = [5,2,3], future = [8,5,6], hierarchy = [[1,2],[2,3]], budget = 7
     *  Output: 12
     */

    int** pHierarchy = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, present =  [", testCase[i].n);
        for (j = 0; j < testCase[i].presentSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].present[j]);
        }
        printf("], future =  [");
        for (j = 0; j < testCase[i].futureSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].future[j]);
        }
        printf("], hierarchy =  [");
        for (j = 0; j < testCase[i].hierarchySize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].hierarchyColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].hierarchy[j][k]);
            }
            printf("]");
        }
        printf("], budget = %d\n", testCase[i].budget);

        pHierarchy = (int**)malloc(testCase[i].hierarchySize * sizeof(int*));
        if (pHierarchy == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].hierarchySize; ++j) {
            pHierarchy[j] = (int*)malloc(testCase[i].hierarchyColSize[j] * sizeof(int));
            if (pHierarchy[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pHierarchy[k]) {
                        free(pHierarchy[k]);
                        pHierarchy[k] = NULL;
                    }
                }
                free(pHierarchy);
                pHierarchy = NULL;
                return EXIT_FAILURE;
            }
            memset(pHierarchy[j], 0, testCase[i].hierarchyColSize[j] * sizeof(int));
            memcpy(pHierarchy[j], testCase[i].hierarchy[j], testCase[i].hierarchyColSize[j] * sizeof(int));
        }

        answer = maxProfit(testCase[i].n, testCase[i].present, testCase[i].presentSize, testCase[i].future,
                           testCase[i].futureSize, pHierarchy, testCase[i].hierarchySize, testCase[i].hierarchyColSize,
                           testCase[i].budget);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].hierarchySize; ++j) {
            if (pHierarchy[j]) {
                free(pHierarchy[j]);
                pHierarchy[j] = NULL;
            }
        }
        free(pHierarchy);
        pHierarchy = NULL;
    }

    return EXIT_SUCCESS;
}
