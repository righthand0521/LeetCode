#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/most-profitable-path-in-a-tree/solutions/1990965/chun-c-by-mogaitesheng-f0mh/
#define N (100005)
struct Edges {
    int end;
    int next;
} edge[N * 2];
int indx, res;
int h[N], v[N], q[N];
void add(int s, int e) {
    edge[indx].end = e;
    edge[indx].next = h[s];
    h[s] = indx++;
}
bool dfsBob(int head, int idx) {
    bool retVal = true;

    v[head] = idx;
    if (head == 0) {
        return retVal;
    }

    for (int i = h[head]; i != -1; i = edge[i].next) {
        if (v[edge[i].end] != -1) {
            continue;
        }

        if (dfsBob(edge[i].end, idx + 1)) {
            return retVal;
        }
    }
    v[head] = -1;
    retVal = false;

    return retVal;
}
void dfsAlice(int head, int score, int time, int* amount) {
    q[head] = 1;

    if (v[head] == time) {
        score += amount[head] / 2;
    } else if (v[head] == -1 || v[head] > time) {
        score += amount[head];
    }

    int ischild = 0;
    for (int i = h[head]; i != -1; i = edge[i].next) {
        if (q[edge[i].end] != -1) {
            continue;
        }
        dfsAlice(edge[i].end, score, time + 1, amount);
        ischild = 1;
    }

    if (ischild == false) {
        res = fmax(res, score);
    }

    q[head] = -1;
}
int mostProfitablePath(int** edges, int edgesSize, int* edgesColSize, int bob, int* amount, int amountSize) {
    int retVal = 0;

    indx = 0;
    res = INT_MIN;
    memset(h, -1, sizeof(h));
    memset(v, -1, sizeof(v));
    memset(q, -1, sizeof(q));
    for (int i = 0; i < edgesSize; i++) {
        add(edges[i][0], edges[i][1]);
        add(edges[i][1], edges[i][0]);
    }

    dfsBob(bob, 0);
    dfsAlice(0, 0, 0, amount);

    retVal = res;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int bob;
        int amount[MAX_SIZE];
        int amountSize;
    } testCase[] = {{{{0, 1}, {1, 2}, {1, 3}, {3, 4}}, 4, {2, 2, 2, 2}, 3, {-2, 4, 2, -4, 6}, 5},
                    {{{0, 1}}, 1, {2}, 1, {-7280, 2350}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
     *  Output: 6
     *
     *  Input: edges = [[0,1]], bob = 1, amount = [-7280,2350]
     *  Output: -7280
     */

    int** pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: edges = [");
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
            }
            printf("]");
        }
        printf("], bob = %d, amount = [", testCase[i].bob);
        for (j = 0; j < testCase[i].amountSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].amount[j]);
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
        answer = mostProfitablePath(pEdges, testCase[i].edgesSize, testCase[i].edgesColSize, testCase[i].bob,
                                    testCase[i].amount, testCase[i].amountSize);

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
