#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/maximum-number-of-k-divisible-components/solutions/2464541/ke-yi-bei-k-zheng-chu-lian-tong-kuai-de-o8jw6/
struct ChildNode {
    int child;
    struct ChildNode* next;
};
long long dfs(struct ChildNode** head, int* values, int root, int father, int k, int* result) {
    long long retVal = values[root];

    long long subSum = 0;
    struct ChildNode* node = NULL;
    for (node = head[root]; NULL != node; node = node->next) {
        if (father != node->child) {
            subSum = dfs(head, values, node->child, root, k, result);
            retVal += subSum;
        }
    }
    if (0 == retVal % k) {
        (*result)++;
    }

    return retVal;
}
int maxKDivisibleComponents(int n, int** edges, int edgesSize, int* edgesColSize, int* values, int valuesSize, int k) {
    int retVal = 0;

    int buffSize = n << 1;
    struct ChildNode buff[buffSize];
    memset(buff, 0, sizeof(buff));

    struct ChildNode* head[n];
    memset(head, 0, sizeof(head));

    int x = 0, y = 0;
    for (x = 0; edgesSize > x; x++) {
        buff[y].child = edges[x][1];
        buff[y].next = head[edges[x][0]];
        head[edges[x][0]] = &buff[y];
        y++;

        buff[y].child = edges[x][0];
        buff[y].next = head[edges[x][1]];
        head[edges[x][1]] = &buff[y];
        y++;
    }

    int root = 0;
    dfs(head, values, root, -1, k, &retVal);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(3 * 10000)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int values[MAX_SIZE];
        int valuesSize;
        int k;
    } testCase[] = {
        {5, {{0, 2}, {1, 2}, {1, 3}, {2, 4}}, 4, {2, 2, 2, 2}, {1, 8, 1, 4, 4}, 4, 6},
        {7, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}}, 6, {2, 2, 2, 2, 2, 2}, {3, 0, 6, 1, 5, 2, 1}, 6, 3}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
     *  Output: 2
     *
     *  Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [3,0,6,1,5,2,1], k = 3
     *  Output: 3
     */

    int** pEdges = NULL;
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
        printf("], values = [");
        for (j = 0; j < testCase[i].valuesSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].values[j]);
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
        answer = maxKDivisibleComponents(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                         testCase[i].values, testCase[i].valuesSize, testCase[i].k);

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
