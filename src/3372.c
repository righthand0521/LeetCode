#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dfs(int node, int parent, int** children, int* childrenColSize, int k) {
    int retVal = 0;

    if (k < 0) {
        return retVal;
    }

    retVal = 1;
    for (int i = 0; i < childrenColSize[node]; i++) {
        int child = children[node][i];
        if (child == parent) {
            continue;
        }
        retVal += dfs(child, node, children, childrenColSize, k - 1);
    }

    return retVal;
}
int* build(int** edges, int edgesSize, int k) {
    int* pRetVal = NULL;

    int n = edgesSize + 1;

    int* childrenColSize = (int*)malloc(n * sizeof(int));
    if (childrenColSize == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(childrenColSize, 0, n * sizeof(int));
    for (int i = 0; i < edgesSize; i++) {
        childrenColSize[edges[i][0]]++;
        childrenColSize[edges[i][1]]++;
    }

    int** children = (int**)malloc(n * sizeof(int*));
    if (children == NULL) {
        perror("malloc");
        free(childrenColSize);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        children[i] = (int*)malloc(childrenColSize[i] * sizeof(int));
        childrenColSize[i] = 0;
    }
    for (int i = 0; i < edgesSize; i++) {
        children[edges[i][0]][childrenColSize[edges[i][0]]++] = edges[i][1];
        children[edges[i][1]][childrenColSize[edges[i][1]]++] = edges[i][0];
    }

    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        for (int i = 0; i < n; i++) {
            free(children[i]);
        }
        free(children);
        free(childrenColSize);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        pRetVal[i] = dfs(i, -1, children, childrenColSize, k);
    }

    //
    for (int i = 0; i < n; i++) {
        free(children[i]);
    }
    free(children);
    free(childrenColSize);

    return pRetVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxTargetNodes(int** edges1, int edges1Size, int* edges1ColSize, int** edges2, int edges2Size, int* edges2ColSize,
                    int k, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int* count1 = build(edges1, edges1Size, k);
    if (count1 == NULL) {
        perror("build");
        return pRetVal;
    }
    int* count2 = build(edges2, edges2Size, k - 1);
    if (count2 == NULL) {
        perror("build");
        return pRetVal;
    }

    int maxCount = 0;
    for (int i = 0; i < edges2Size + 1; i++) {
        if (count2[i] > maxCount) {
            maxCount = count2[i];
        }
    }

    int n = edges1Size + 1;
    pRetVal = (int*)malloc(n * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        free(count1);
        free(count2);
        return pRetVal;
    }
    for (int i = 0; i < n; i++) {
        pRetVal[i] = count1[i] + maxCount;
    }
    (*returnSize) = n;

    //
    free(count1);
    free(count2);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int edges1[MAX_SIZE][2];
        int edges1Size;
        int edges1ColSize[MAX_SIZE];
        int edges2[MAX_SIZE][2];
        int edges2Size;
        int edges2ColSize[MAX_SIZE];
        int k;
        int returnSize;
    } testCase[] = {{{{0, 1}, {0, 2}, {2, 3}, {2, 4}},
                     4,
                     {2, 2, 2, 2},
                     {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}},
                     7,
                     {2, 2, 2, 2, 2, 2, 2},
                     2},
                    {{{0, 1}, {0, 2}, {0, 3}, {0, 4}}, 4, {2, 2, 2, 2}, {{0, 1}, {1, 2}, {2, 3}}, 3, {2, 2, 2}, 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2
     *  Output: [9,7,9,8,8]
     *
     *  Input: edges1 = [[0,1],[0,2],[0,3],[0,4]], edges2 = [[0,1],[1,2],[2,3]], k = 1
     *  Output: [6,3,3,3,3]
     */

    int** pEdges1 = NULL;
    int** pEdges2 = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: edges1 = [");
        for (j = 0; j < testCase[i].edges1Size; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edges1ColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges1[j][k]);
            }
            printf("]");
        }
        printf("], edges2 = [");
        for (j = 0; j < testCase[i].edges2Size; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edges2ColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges2[j][k]);
            }
            printf("]");
        }
        printf("], k = %d\n", testCase[i].k);

        pEdges1 = (int**)malloc(testCase[i].edges1Size * sizeof(int*));
        if (pEdges1 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edges1Size; ++j) {
            pEdges1[j] = (int*)malloc(testCase[i].edges1ColSize[j] * sizeof(int));
            if (pEdges1[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges1[k]);
                    pEdges1[k] = NULL;
                }
                free(pEdges1);
                pEdges1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges1[j], 0, (testCase[i].edges1ColSize[j] * sizeof(int)));
            memcpy(pEdges1[j], testCase[i].edges1[j], (testCase[i].edges1ColSize[j] * sizeof(int)));
        }
        pEdges2 = (int**)malloc(testCase[i].edges2Size * sizeof(int*));
        if (pEdges2 == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edges2Size; ++j) {
            pEdges2[j] = (int*)malloc(testCase[i].edges2ColSize[j] * sizeof(int));
            if (pEdges2[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges2[k]);
                    pEdges2[k] = NULL;
                }
                free(pEdges2);
                pEdges2 = NULL;
                for (j = 0; j < testCase[i].edges2Size; ++j) {
                    free(pEdges1[j]);
                    pEdges1[j] = NULL;
                }
                free(pEdges1);
                pEdges1 = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges2[j], 0, (testCase[i].edges2ColSize[j] * sizeof(int)));
            memcpy(pEdges2[j], testCase[i].edges2[j], (testCase[i].edges2ColSize[j] * sizeof(int)));
        }

        pAnswer =
            maxTargetNodes(pEdges1, testCase[i].edges1Size, testCase[i].edges1ColSize, pEdges2, testCase[i].edges2Size,
                           testCase[i].edges2ColSize, testCase[i].k, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].edges2Size; ++j) {
            free(pEdges2[j]);
            pEdges2[j] = NULL;
        }
        free(pEdges2);
        pEdges2 = NULL;
        for (j = 0; j < testCase[i].edges1Size; ++j) {
            free(pEdges1[j]);
            pEdges1[j] = NULL;
        }
        free(pEdges1);
        pEdges1 = NULL;
    }

    return EXIT_SUCCESS;
}
