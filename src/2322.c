#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct ListNode* createList(int val) {
    struct ListNode* pObj = NULL;

    pObj = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->val = val;
    pObj->next = NULL;

    return pObj;
}
void freeList(struct ListNode* list) {
    struct ListNode* pFree;
    while (list) {
        pFree = list;
        list = list->next;
        free(pFree);
    }
    pFree = NULL;
}
int calc(int part1, int part2, int part3) {
    int retVal = fmax(part1, fmax(part2, part3)) - fmin(part1, fmin(part2, part3));

    return retVal;
}
int dfs2(int x, int f, int oth, int anc, int* nums, struct ListNode** adjacent, int sum, int* res) {
    int retVal = nums[x];

    for (struct ListNode* p = adjacent[x]; p != NULL; p = p->next) {
        int y = p->val;
        if (y == f) {
            continue;
        }
        retVal ^= dfs2(y, x, oth, anc, nums, adjacent, sum, res);
    }
    if (f != anc) {
        (*res) = fmin((*res), calc(oth, retVal, sum ^ oth ^ retVal));
    }

    return retVal;
}
int dfs(int x, int f, int* nums, struct ListNode** adjacent, int sum, int* res) {
    int retVal = nums[x];

    for (struct ListNode* p = adjacent[x]; p != NULL; p = p->next) {
        int y = p->val;
        if (y == f) {
            continue;
        }
        retVal ^= dfs(y, x, nums, adjacent, sum, res);
    }

    for (struct ListNode* p = adjacent[x]; p != NULL; p = p->next) {
        int y = p->val;
        if (y == f) {
            dfs2(y, x, retVal, x, nums, adjacent, sum, res);
        }
    }

    return retVal;
}
int minimumScore(int* nums, int numsSize, int** edges, int edgesSize, int* edgesColSize) {
    int retVal = 0;

    struct ListNode* adjacent[numsSize];
    for (int i = 0; i < numsSize; i++) {
        adjacent[i] = NULL;
    }
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        struct ListNode* nodeu = createList(u);
        if (nodeu == NULL) {
            perror("malloc");
            goto exit;
        }
        nodeu->next = adjacent[v];
        adjacent[v] = nodeu;

        struct ListNode* nodev = createList(v);
        if (nodev == NULL) {
            perror("malloc");
            goto exit;
        }
        nodev->next = adjacent[u];
        adjacent[u] = nodev;
    }

    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum ^= nums[i];
    }

    retVal = INT_MAX;
    dfs(0, -1, nums, adjacent, sum, &retVal);

exit:
    for (int i = 0; i < numsSize; i++) {
        freeList(adjacent[i]);
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int nums[MAX_SIZE];
        int numsSize;
        int edges[MAX_SIZE][2];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
    } testCase[] = {{{1, 5, 5, 4, 11}, 5, {{0, 1}, {1, 2}, {1, 3}, {3, 4}}, 4, {2, 2, 2, 2}},
                    {{5, 5, 2, 4, 4, 2}, 6, {{0, 1}, {1, 2}, {5, 2}, {4, 3}, {1, 3}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
     *  Output: 9
     *
     *  Input: nums = [5,5,2,4,4,2], edges = [[0,1],[1,2],[5,2],[4,3],[1,3]]
     *  Output: 0
     */

    int** pEdges = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: nums = [");
        for (j = 0; j < testCase[i].numsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].nums[j]);
        }
        printf("], edges = [");
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].edges[j][k]);
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
                }
                free(pEdges);
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }

        answer = minimumScore(testCase[i].nums, testCase[i].numsSize, pEdges, testCase[i].edgesSize,
                              testCase[i].edgesColSize);
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
