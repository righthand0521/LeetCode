#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/solutions/918443/cyu-yan-lin-jie-ju-zhen-dfs-hashsuo-yin-4sp1p/
#define MAX_NODE (int)(1e5)
#define MAX_LABELS_CHAR (26)
#define TIME_LIMIT_EXCEEDED (0)
#if (TIME_LIMIT_EXCEEDED)
#define MAX_ADJACENT_LEN (100)  // Time Limit Exceeded
#else
#define MAX_ADJACENT_LEN (10)
#endif
void dfs(int node, char* labels, int* visited, int** arr, int** adjacent, int* count, int* pRetVal) {
    int idx = labels[node] - 'a';
    visited[node] = 1;
    arr[node][idx] = 1;

    int child;
    int i, j;
    for (i = 0; i < count[node]; ++i) {
        child = adjacent[node][i];
        if (visited[child]) {
            continue;
        }
        dfs(child, labels, visited, arr, adjacent, count, pRetVal);

        for (j = 0; j < MAX_LABELS_CHAR; ++j) {
            arr[node][j] += arr[child][j];
        }
    }

    pRetVal[node] = arr[node][idx];
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countSubTrees(int n, int** edges, int edgesSize, int* edgesColSize, char* labels, int* returnSize) {
    int* pRetVal = NULL;

    int i, j;

    //
    (*returnSize) = n;
    pRetVal = (int*)malloc((*returnSize) * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, 0, ((*returnSize) * sizeof(int)));

    //
    int count[MAX_NODE];
    memset(count, 0, sizeof(count));

    int** adjacent = (int**)malloc(sizeof(int*) * MAX_NODE);
    if (adjacent == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < MAX_NODE; ++i) {
        adjacent[i] = (int*)malloc(sizeof(int) * MAX_ADJACENT_LEN);
        if (adjacent[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(adjacent[j]);
                adjacent[j] = NULL;
            }
            free(adjacent);
            adjacent = NULL;
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(adjacent[i], 0, sizeof(int) * MAX_ADJACENT_LEN);
    }

    int node1;
    int node2;
    for (i = 0; i < edgesSize; ++i) {
        node1 = edges[i][0];
        node2 = edges[i][1];
        adjacent[node1][count[node1]++] = node2;
        adjacent[node2][count[node2]++] = node1;
    }

    //
    int visited[MAX_NODE];
    memset(visited, 0, sizeof(visited));

    int** arr = (int**)malloc(n * sizeof(int*));
    if (arr == NULL) {
        perror("malloc");
        for (j = 0; j < MAX_NODE; ++j) {
            free(adjacent[j]);
            adjacent[j] = NULL;
        }
        free(adjacent);
        adjacent = NULL;
        free(pRetVal);
        pRetVal = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < n; ++i) {
        arr[i] = (int*)malloc(MAX_LABELS_CHAR * sizeof(int));
        if (arr[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(arr[j]);
                arr[j] = NULL;
            }
            free(arr);
            arr = NULL;
            for (j = 0; j < MAX_NODE; ++j) {
                free(adjacent[j]);
                adjacent[j] = NULL;
            }
            free(adjacent);
            adjacent = NULL;
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        memset(arr[i], 0, (MAX_LABELS_CHAR * sizeof(int)));
    }

    dfs(0, labels, visited, arr, adjacent, count, pRetVal);

    for (j = 0; j < n; ++j) {
        free(arr[j]);
        arr[j] = NULL;
    }
    free(arr);
    arr = NULL;
    for (j = 0; j < MAX_NODE; ++j) {
        free(adjacent[j]);
        adjacent[j] = NULL;
    }
    free(adjacent);
    adjacent = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        char labels[MAX_SIZE];
        int returnSize;
    } testCase[] = {{7, {{0, 1}, {0, 2}, {1, 4}, {1, 5}, {2, 3}, {2, 6}}, 6, {2, 2, 2, 2, 2, 2}, "abaedcd", 0},
                    {4, {{0, 1}, {1, 2}, {0, 3}}, 3, {2, 2, 2}, "bbbb", 0},
                    {5, {{0, 1}, {0, 2}, {1, 3}, {0, 4}}, 4, {2, 2, 2, 2}, "aabab", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pEdges = NULL;
    int* pAnswer = NULL;
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
        printf("], labels = \"%s\"\n", testCase[i].labels);

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
                    }
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, testCase[i].edgesColSize[j] * sizeof(int));
            memcpy(pEdges[j], testCase[i].edges[j], testCase[i].edgesColSize[j] * sizeof(int));
        }

        pAnswer = countSubTrees(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                testCase[i].labels, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
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
