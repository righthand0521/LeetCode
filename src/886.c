#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
#ifndef UNION_FIND
#define UNION_FIND (1)

int findFa(int x, int *fa) {
    if (fa[x] < 0) {
        return x;
    }

    return (fa[x] = findFa(fa[x], fa));
}
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void unit(int x, int y, int *fa) {
    x = findFa(x, fa);
    y = findFa(y, fa);
    if (x == y) {
        return;
    }

    if (fa[x] < fa[y]) {
        swap(&x, &y);
    }
    fa[x] += fa[y];
    fa[y] = x;
}
bool isconnect(int x, int y, int *fa) {
    x = findFa(x, fa);
    y = findFa(y, fa);

    return (x == y);
}
#endif
bool possibleBipartition(int n, int **dislikes, int dislikesSize, int *dislikesColSize) {
    bool retVal = false;

    int i, j;
    struct ListNode *pNode;

    int color[n + 1];
    memset(color, 0, sizeof(color));
    int fa[n + 1];
    memset(fa, -1, sizeof(fa));
    struct ListNode *g[n + 1];
    for (i = 0; i <= n; ++i) {
        g[i] = NULL;
    }

    int a, b;
    for (i = 0; i < dislikesSize; ++i) {
        a = dislikes[i][0];
        b = dislikes[i][1];

        pNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (pNode == NULL) {
            perror("malloc");
            for (i = 0; i <= n; ++i) {
                if (g[i]) {
                    free(g[i]);
                    g[i] = NULL;
                }
            }
            return retVal;
        }
        pNode->val = a;
        pNode->next = g[b];
        g[b] = pNode;

        pNode = (struct ListNode *)malloc(sizeof(struct ListNode));
        if (pNode == NULL) {
            perror("malloc");
            for (i = 0; i <= n; ++i) {
                if (g[i]) {
                    free(g[i]);
                    g[i] = NULL;
                }
            }
            return retVal;
        }
        pNode->val = b;
        pNode->next = g[a];
        g[a] = pNode;
    }

    struct ListNode *curr;
    struct ListNode *prev;
    for (i = 1; i <= n; ++i) {
        for (pNode = g[i]; pNode; pNode = pNode->next) {
            unit(g[i]->val, pNode->val, fa);

            if (isconnect(i, pNode->val, fa) == false) {
                continue;
            }

            for (j = 0; j <= n; ++j) {
                curr = g[j];
                while (curr) {
                    prev = curr;
                    curr = curr->next;
                    free(prev);
                }
            }

            return retVal;
        }
    }
    for (j = 0; j <= n; j++) {
        curr = g[j];
        while (curr) {
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        int n;
        int dislikes[MAX_SIZE][2];
        int dislikesSize;
        int dislikesColSize[MAX_SIZE];
    } testCase[] = {{4, {{1, 2}, {1, 3}, {2, 4}}, 3, {2, 2, 2}},
                    {3, {{1, 2}, {1, 3}, {2, 3}}, 3, {2, 2, 2}},
                    {5, {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {1, 5}}, 5, {2, 2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int **pDislikes = NULL;
    bool answer = false;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, dislikes = [", testCase[i].n);
        for (j = 0; j < testCase[i].dislikesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].dislikesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].dislikes[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pDislikes = (int **)malloc(testCase[i].dislikesSize * sizeof(int *));
        if (pDislikes == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].dislikesSize; ++j) {
            pDislikes[j] = (int *)malloc(testCase[i].dislikesColSize[j] * sizeof(int));
            if (pDislikes[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pDislikes[k]) {
                        free(pDislikes[k]);
                    }
                }
                free(pDislikes);
                pDislikes = NULL;
                return EXIT_FAILURE;
            }
            memset(pDislikes[j], 0, testCase[i].dislikesColSize[j] * sizeof(int));
            memcpy(pDislikes[j], testCase[i].dislikes[j], testCase[i].dislikesColSize[j] * sizeof(int));
        }
        answer = possibleBipartition(testCase[i].n, pDislikes, testCase[i].dislikesSize, testCase[i].dislikesColSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");

        for (j = 0; j < testCase[i].dislikesSize; ++j) {
            if (pDislikes[j]) {
                free(pDislikes[j]);
                pDislikes[j] = NULL;
            }
        }
        free(pDislikes);
        pDislikes = NULL;
    }

    return EXIT_SUCCESS;
}
