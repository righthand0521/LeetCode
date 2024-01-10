#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Convex_hull
#define Jarvis_Algorithm (1)  // Time Complexity: O(n^2), Space Complexity: O(n).
#define Graham_Scan (1)       // Time Complexity: O(nlogn), Space Complexity: O(n).
#define Monotone_Chain (1)    // Time Complexity: O(nlogn), Space Complexity: O(n).
int crossProduct(const int* p, const int* q, const int* r) {
    // https://en.wikipedia.org/wiki/Cross_product
    return (((q[0] - p[0]) * (r[1] - q[1])) - ((q[1] - p[1]) * (r[0] - q[0])));
}
#if (Jarvis_Algorithm)

#elif (Graham_Scan)
int distance(const int* p, const int* q) { return (((p[0] - q[0]) * (p[0] - q[0])) + ((p[1] - q[1]) * (p[1] - q[1]))); }
int* p = NULL;
int cmp(const void* pa, const void* pb) {
    int* a = *((int**)pa);
    int* b = *((int**)pb);

    int diff = crossProduct(p, a, b);
    if (diff == 0) {
        return (distance(p, a) - distance(p, b));
    } else {
        return -diff;
    }
}
void swap(int* pa, int* pb) {
    int c = pa[0];

    pa[0] = pb[0];
    pb[0] = c;
    c = pa[1];
    pa[1] = pb[1];
    pb[1] = c;
}
#elif (Monotone_Chain)
int cmp(const void* pa, const void* pb) {
    int* a = *((int**)pa);
    int* b = *((int**)pb);

    if (a[0] == b[0]) {
        return (a[1] - b[1]);
    }
    return a[0] - b[0];
}
#endif
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** outerTrees(int** trees, int treesSize, int* treesColSize, int* returnSize, int** returnColumnSizes) {
    int** retVal = NULL;
    (*returnSize) = 0;

    int pos = 0;
    int i, j;

    retVal = (int**)malloc(treesSize * sizeof(int*));
    if (retVal == NULL) {
        perror("malloc");
        return retVal;
    }

    if (treesSize < 4) {
        (*returnColumnSizes) = (int*)malloc(treesSize * sizeof(int));
        if ((*returnColumnSizes) == NULL) {
            perror("malloc");
            free(retVal);
            retVal = NULL;
            return retVal;
        }
        for (i = 0; i < treesSize; ++i) {
            retVal[i] = (int*)malloc(2 * sizeof(int));
            if (retVal[i] == NULL) {
                perror("malloc");
                for (j = 0; j < i; ++j) {
                    free(retVal[j]);
                    retVal[j] = NULL;
                }
                free((*returnColumnSizes));
                (*returnColumnSizes) = NULL;
                free(retVal);
                retVal = NULL;
                return retVal;
            }
            retVal[i][0] = trees[i][0];
            retVal[i][1] = trees[i][1];
            (*returnColumnSizes)[i] = 2;
        }
        (*returnSize) = treesSize;

        return retVal;
    }

#if (Jarvis_Algorithm)
    printf("Jarvis Algorithm: Time Complexity: O(n^2), Space Complexity: O(n).\n");

    int leftMost = 0;
    for (i = 0; i < treesSize; ++i) {
        if ((trees[i][0] < trees[leftMost][0]) ||
            ((trees[i][0] == trees[leftMost][0]) && (trees[i][1] < trees[leftMost][1]))) {
            leftMost = i;
        }
    }

    bool* visit = (bool*)malloc(treesSize * sizeof(bool));
    if (visit == NULL) {
        perror("malloc");
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    memset(visit, 0, (treesSize * sizeof(bool)));

    int p = leftMost;
    int q;
    int r;
    do {
        q = (p + 1) % treesSize;
        for (r = 0; r < treesSize; ++r) {
            // 如果 r 在 pq 的右側，則 q = r.
            if (crossProduct(trees[p], trees[q], trees[r]) < 0) {
                q = r;
            }
        }

        // 是否存在點 i, 使得 p 、q 、i 在同一條直線上
        for (i = 0; i < treesSize; ++i) {
            if ((visit[i]) || (i == p) || (i == q)) {
                continue;
            }

            if (crossProduct(trees[p], trees[q], trees[i]) == 0) {
                retVal[pos] = (int*)malloc(2 * sizeof(int));
                if (retVal[pos] == NULL) {
                    perror("malloc");
                    for (j = 0; j < pos; ++j) {
                        if (retVal[j]) {
                            free(retVal[j]);
                            retVal[j] = NULL;
                        }
                    }
                    free(visit);
                    visit = NULL;
                    free(retVal);
                    retVal = NULL;
                    return retVal;
                }

                retVal[pos][0] = trees[i][0];
                retVal[pos][1] = trees[i][1];
                pos++;
                visit[i] = true;
            }
        }

        if (!visit[q]) {
            visit[q] = true;
            retVal[pos] = (int*)malloc(2 * sizeof(int));
            if (retVal[pos] == NULL) {
                perror("malloc");
                for (j = 0; j < pos; ++j) {
                    if (retVal[j]) {
                        free(retVal[j]);
                        retVal[j] = NULL;
                    }
                }
                free(visit);
                visit = NULL;
                free(retVal);
                retVal = NULL;
                return retVal;
            }
            retVal[pos][0] = trees[q][0];
            retVal[pos][1] = trees[q][1];
            pos++;
        }

        p = q;
    } while (p != leftMost);
    free(visit);
    visit = NULL;
#elif (Graham_Scan)
    printf("Graham Scan: Time Complexity: O(nlogn), Space Complexity: O(n).\n");

    // 找到 y 最小的點 bottom
    int bottom = 0;
    for (i = 0; i < treesSize; ++i) {
        if ((trees[i][1] < trees[bottom][1]) ||
            ((trees[i][1] == trees[bottom][1]) && (trees[i][0] < trees[bottom][0]))) {
            bottom = i;
        }
    }
    swap(trees[bottom], trees[0]);
    p = trees[0];

    // 以 bottom 原點，按照極坐標的角度大小進行排序
    qsort(trees + 1, treesSize - 1, sizeof(int*), cmp);

    // 對於凸包最後且在同一條直線的元素按照距離從大到小進行排序
    int r = treesSize - 1;
    while ((r >= 0) && (crossProduct(trees[0], trees[treesSize - 1], trees[r]) == 0)) {
        r--;
    }

    int l, h;
    for (l = r + 1, h = treesSize - 1; l < h; l++, h--) {
        swap(trees[l], trees[h]);
    }

    int* stack = (int*)malloc(treesSize * sizeof(int));
    if (stack == NULL) {
        perror("malloc");
        free(retVal);
        retVal = NULL;
        return retVal;
    }

    int top = 0;
    stack[top++] = 0;
    stack[top++] = 1;
    for (i = 2; i < treesSize; ++i) {
        // 如果當前元素與棧頂的兩個元素構成的向量順時針旋轉，則彈出棧頂元素
        while ((top > 1) && (crossProduct(trees[stack[top - 2]], trees[stack[top - 1]], trees[i]) < 0)) {
            top--;
        }
        stack[top++] = i;
    }

    while (top > 0) {
        retVal[pos] = (int*)malloc(2 * sizeof(int));
        if (retVal[pos] == NULL) {
            perror("malloc");
            for (j = 0; j < pos; ++j) {
                if (retVal[j]) {
                    free(retVal[j]);
                    retVal[j] = NULL;
                }
            }
            free(stack);
            stack = NULL;
            free(retVal);
            retVal = NULL;
            return retVal;
        }
        memcpy(retVal[pos], trees[stack[top - 1]], (2 * sizeof(int)));

        pos++;
        top--;
    }

    free(stack);
    stack = NULL;
#elif (Monotone_Chain)
    printf("Monotone Chain: Time Complexity: O(nlogn), Space Complexity: O(n).\n");

    qsort(trees, treesSize, sizeof(int*), cmp);

    int* hull = (int*)malloc(sizeof(int) * (treesSize + 1));
    if (hull == NULL) {
        perror("malloc");
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    int* used = (int*)malloc(sizeof(int) * treesSize);
    if (used == NULL) {
        perror("malloc");
        free(hull);
        hull = NULL;
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    memset(used, 0, (treesSize * sizeof(int)));
    // hull[0] 需要入棧兩次，不進行標記
    hull[pos++] = 0;

    // 求出凸包的下半部分
    for (i = 1; i < treesSize; ++i) {
        while ((pos > 1) && (crossProduct(trees[hull[pos - 2]], trees[hull[pos - 1]], trees[i]) < 0)) {
            used[hull[pos - 1]] = false;
            pos--;
        }
        used[i] = true;
        hull[pos++] = i;
    }
    int m = pos;

    // 求出凸包的上半部分
    for (i = treesSize - 2; i >= 0; --i) {
        if (!used[i]) {
            while ((pos > m) && (crossProduct(trees[hull[pos - 2]], trees[hull[pos - 1]], trees[i]) < 0)) {
                used[hull[pos - 1]] = false;
                pos--;
            }
            used[i] = true;
            hull[pos++] = i;
        }
    }

    // hull[0] 同時參與凸包的上半部分檢測，因此需去掉重複的 hull[0]
    pos--;

    for (i = 0; i < pos; ++i) {
        retVal[i] = (int*)malloc(sizeof(int) * 2);
        if (retVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                if (retVal[j]) {
                    free(retVal[j]);
                    retVal[j] = NULL;
                }
            }
            free(used);
            used = NULL;
            free(hull);
            hull = NULL;
            free(retVal);
            retVal = NULL;
            return retVal;
        }
        memcpy(retVal[i], trees[hull[i]], (2 * sizeof(int)));
    }

    free(used);
    used = NULL;
    free(hull);
    hull = NULL;
#endif

    (*returnSize) = pos;
    (*returnColumnSizes) = (int*)malloc(pos * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j = 0; j < pos; ++j) {
            if (retVal[j]) {
                free(retVal[j]);
                retVal[j] = NULL;
            }
        }
        free(retVal);
        retVal = NULL;
        return retVal;
    }
    for (i = 0; i < pos; ++i) {
        (*returnColumnSizes)[i] = 2;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3000)
    struct testCaseType {
        int trees[MAX_SIZE][2];
        int treesSize;
        int treesColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{{1, 1}, {2, 2}, {2, 0}, {2, 4}, {3, 3}, {4, 2}}, 6, {2, 2, 2, 2, 2, 2}, 0, NULL},
                    {{{1, 2}, {2, 2}, {4, 2}}, 3, {2, 2, 2}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pTrees = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: points =  [");
        for (j = 0; j < testCase[i].treesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].treesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].trees[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pTrees = (int**)malloc(testCase[i].treesSize * sizeof(int*));
        if (pTrees == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].treesSize; ++j) {
            pTrees[j] = (int*)malloc(testCase[i].treesColSize[j] * sizeof(int));
            if (pTrees[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pTrees[k]) {
                        free(pTrees[k]);
                        pTrees[k] = NULL;
                    }
                }
                free(pTrees);
                pTrees = NULL;
                return EXIT_FAILURE;
            }
            memset(pTrees[j], 0, testCase[i].treesColSize[j] * sizeof(int));
            memcpy(pTrees[j], testCase[i].trees[j], testCase[i].treesColSize[j] * sizeof(int));
        }
        pAnswer = outerTrees(pTrees, testCase[i].treesSize, testCase[i].treesColSize, &testCase[i].returnSize,
                             &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;

        for (j = 0; j < testCase[i].treesSize; ++j) {
            if (pTrees[j]) {
                free(pTrees[j]);
                pTrees[j] = NULL;
            }
        }
        free(pTrees);
        pTrees = NULL;
    }

    return EXIT_SUCCESS;
}
