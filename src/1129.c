#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define BREADTH_FIRST_SEARCH (1)
struct ListNode* createAdjacentNode(int val) {
    struct ListNode* pNew = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (pNew == NULL) {
        perror("malloc");
        return pNew;
    }
    pNew->val = val;
    pNew->next = NULL;

    return pNew;
}
void freeAdjacentList(struct ListNode* pHead) {
    struct ListNode* pFree = NULL;
    while (pHead != NULL) {
        pFree = pHead;
        pHead = pHead->next;
        free(pFree);
        pFree = NULL;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* shortestAlternatingPaths(int n, int** redEdges, int redEdgesSize, int* redEdgesColSize, int** blueEdges,
                              int blueEdgesSize, int* blueEdgesColSize, int* returnSize) {
    int* pRetVal = NULL;

    int i;

    // malloc return answer
    (*returnSize) = n;
    pRetVal = (int*)calloc(n, sizeof(int));
    if (pRetVal == NULL) {
        perror("calloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        // -1 if such a path does not exist.
        pRetVal[i] = -1;
    }

    // malloc adjacent matrix
    struct ListNode* adjacent[2][n];
    for (i = 0; i < n; ++i) {
        // redEdges: 0, blueEdges: 1.
        adjacent[0][i] = NULL;
        adjacent[1][i] = NULL;
    }
    struct ListNode* pNew = NULL;
    for (i = 0; i < redEdgesSize; ++i) {
        pNew = createAdjacentNode(redEdges[i][1]);
        if (pNew == NULL) {
            perror("malloc");
            for (i = 0; i < n; i++) {
                freeAdjacentList(adjacent[0][i]);
                freeAdjacentList(adjacent[1][i]);
            }
            return pRetVal;
        }
        pNew->next = adjacent[0][redEdges[i][0]];
        adjacent[0][redEdges[i][0]] = pNew;
    }
    for (i = 0; i < blueEdgesSize; ++i) {
        pNew = createAdjacentNode(blueEdges[i][1]);
        if (pNew == NULL) {
            perror("malloc");
            for (i = 0; i < n; i++) {
                freeAdjacentList(adjacent[0][i]);
                freeAdjacentList(adjacent[1][i]);
            }
            return pRetVal;
        }
        pNew->next = adjacent[1][blueEdges[i][0]];
        adjacent[1][blueEdges[i][0]] = pNew;
    }
    // redEdges: 0, blueEdges: 1.
    int distance[2][n];
    for (i = 0; i < n; ++i) {
        distance[0][i] = INT_MAX;
        distance[1][i] = INT_MAX;
    }
    distance[0][0] = 0;
    distance[1][0] = 0;

    // BFS Queue
    int head = 0;
    int tail = 2;
    int bfs[n * 2][2];
    memset(bfs, 0, sizeof(bfs));
    bfs[1][1] = 1;
    // BFS
    int red;
    int blue;
    struct ListNode* pCurrent = NULL;
    int dstNode;
    while (head != tail) {
        red = bfs[head][0];
        blue = bfs[head][1];
        ++head;

        for (pCurrent = adjacent[1 - blue][red]; pCurrent != NULL; pCurrent = pCurrent->next) {
            dstNode = pCurrent->val;
            if (distance[1 - blue][dstNode] != INT_MAX) {
                continue;
            }
            distance[1 - blue][dstNode] = distance[blue][red] + 1;
            bfs[tail][0] = dstNode;
            bfs[tail++][1] = 1 - blue;
        }
    }
    // update return answer
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = fmin(distance[0][i], distance[1][i]);
        if (pRetVal[i] == INT_MAX) {
            pRetVal[i] = -1;
        }
    }

    // free adjacent matrix
    for (i = 0; i < n; i++) {
        freeAdjacentList(adjacent[0][i]);
        freeAdjacentList(adjacent[1][i]);
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (400)
    struct testCaseType {
        int n;
        int redEdges[MAX_SIZE][2];
        int redEdgesSize;
        int redEdgesColSize[MAX_SIZE];
        int blueEdges[MAX_SIZE][2];
        int blueEdgesSize;
        int blueEdgesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{3, {{0, 1}, {1, 2}}, 2, {2, 2}, {}, 0, {}, 0},
                    {3, {{0, 1}}, 1, {2}, {{2, 1}}, 1, {2}, 0},
                    {3, {{1, 0}}, 1, {2}, {{2, 1}}, 1, {2}, 0},
                    {3, {{0, 1}}, 1, {2}, {{1, 2}}, 1, {2}, 0},
                    {3, {{0, 1}, {0, 2}}, 2, {2, 2}, {{1, 0}}, 1, {2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
     *  Output: [0,1,-1]
     *
     *  Input: n = 3, redEdges = [[0,1]],make blueEdges = [[2,1]]
     *  Output: [0,1,-1]
     *
     *  n = 3, red_edges = [[1,0]], blue_edges = [[2,1]]
     *  [0,-1,-1]
     *
     *  n = 3, red_edges = [[0,1]], blue_edges = [[1,2]]
     *  [0,1,2]
     *
     *  n = 3, red_edges = [[0,1],[0,2]], blue_edges = [[1,0]]
     *  [0,1,1]
     */

    int** pRedEdges = NULL;
    int** pBedEdges = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, redEdges = [", testCase[i].n);
        for (j = 0; j < testCase[i].redEdgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].redEdgesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].redEdges[j][k]);
            }
            printf("]");
        }
        printf("], blueEdges = [");
        for (j = 0; j < testCase[i].blueEdgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].blueEdgesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].blueEdges[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pRedEdges = (int**)malloc(testCase[i].redEdgesSize * sizeof(int*));
        if (pRedEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].redEdgesSize; ++j) {
            pRedEdges[j] = (int*)malloc(testCase[i].redEdgesColSize[j] * sizeof(int));
            if (pRedEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pRedEdges[k]) {
                        free(pRedEdges[k]);
                    }
                }
                free(pRedEdges);
                pRedEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pRedEdges[j], 0, testCase[i].redEdgesColSize[j] * sizeof(int));
            memcpy(pRedEdges[j], testCase[i].redEdges[j], testCase[i].redEdgesColSize[j] * sizeof(int));
        }
        pBedEdges = (int**)malloc(testCase[i].blueEdgesSize * sizeof(int*));
        if (pBedEdges == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].redEdgesSize; ++j) {
                if (pRedEdges[j]) {
                    free(pRedEdges[j]);
                    pRedEdges[j] = NULL;
                }
            }
            free(pRedEdges);
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].blueEdgesSize; ++j) {
            pBedEdges[j] = (int*)malloc(testCase[i].blueEdgesColSize[j] * sizeof(int));
            if (pBedEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pBedEdges[k]) {
                        free(pBedEdges[k]);
                    }
                }
                free(pBedEdges);
                pBedEdges = NULL;
                for (j = 0; j < testCase[i].redEdgesSize; ++j) {
                    if (pRedEdges[j]) {
                        free(pRedEdges[j]);
                        pRedEdges[j] = NULL;
                    }
                }
                free(pRedEdges);
                return EXIT_FAILURE;
            }
            memset(pBedEdges[j], 0, testCase[i].blueEdgesColSize[j] * sizeof(int));
            memcpy(pBedEdges[j], testCase[i].blueEdges[j], testCase[i].blueEdgesColSize[j] * sizeof(int));
        }

        pAnswer = shortestAlternatingPaths(testCase[i].n, pRedEdges, testCase[i].redEdgesSize,
                                           testCase[i].redEdgesColSize, pBedEdges, testCase[i].blueEdgesSize,
                                           testCase[i].blueEdgesColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0 ? "" : ","), pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].redEdgesSize; ++j) {
            if (pRedEdges[j]) {
                free(pRedEdges[j]);
                pRedEdges[j] = NULL;
            }
        }
        free(pRedEdges);
        pRedEdges = NULL;
        for (j = 0; j < testCase[i].blueEdgesSize; ++j) {
            if (pBedEdges[j]) {
                free(pBedEdges[j]);
                pBedEdges[j] = NULL;
            }
        }
        free(pBedEdges);
        pBedEdges = NULL;
    }

    return EXIT_SUCCESS;
}
