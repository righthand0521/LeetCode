#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
struct Edge {
    int x;
    int y;
    int w;
    int id;
};
int compareStruct(const void* a, const void* b) {
    int pa = ((struct Edge*)a)->w;
    int pb = ((struct Edge*)b)->w;

    return (pa > pb);
}
struct DisjointSetUnion {
    int* f;
    int* size;
    int n;
    int setCount;
};
void initDSU(struct DisjointSetUnion* obj, int n) {
    obj->f = (int*)malloc(n * sizeof(int));
    if (obj->f == NULL) {
        perror("malloc");
        return;
    }
    obj->size = (int*)malloc(n * sizeof(int));
    if (obj->size == NULL) {
        perror("malloc");
        return;
    }
    obj->n = n;
    obj->setCount = n;

    int i;
    for (i = 0; i < n; i++) {
        obj->f[i] = i;
        obj->size[i] = 1;
    }
}
void freeDSU(struct DisjointSetUnion* obj) {
    free(obj->f);
    free(obj->size);
    free(obj);
    obj = NULL;
}
int find(struct DisjointSetUnion* obj, int x) {
    int retVal = x;
    if (obj->f[x] == x) {
        return retVal;
    }
    obj->f[x] = find(obj, obj->f[x]);
    retVal = obj->f[x];

    return retVal;
}
bool unionSet(struct DisjointSetUnion* obj, int x, int y) {
    bool retVal = false;

    int fx = find(obj, x);
    int fy = find(obj, y);
    if (fx == fy) {
        return retVal;
    }

    if (obj->size[fx] < obj->size[fy]) {
        swap(&fx, &fy);
    }
    obj->size[fx] += obj->size[fy];
    obj->f[fy] = fx;
    obj->setCount--;
    retVal = true;

    return retVal;
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findCriticalAndPseudoCriticalEdges(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize,
                                         int** returnColumnSizes) {
    int** pRetVal = NULL;

    //
    (*returnSize) = 0;
    int i, j;

    //
    struct Edge edgesTmp[edgesSize];
    for (i = 0; i < edgesSize; i++) {
        edgesTmp[i].x = edges[i][0];
        edgesTmp[i].y = edges[i][1];
        edgesTmp[i].w = edges[i][2];
        edgesTmp[i].id = i;
    }
    qsort(edgesTmp, edgesSize, sizeof(struct Edge), compareStruct);

    struct DisjointSetUnion* ufStd = (struct DisjointSetUnion*)malloc(sizeof(struct DisjointSetUnion));
    if (ufStd == NULL) {
        perror("malloc");
        return pRetVal;
    }
    initDSU(ufStd, n);
    int value = 0;
    for (i = 0; i < edgesSize; ++i) {
        if (unionSet(ufStd, edgesTmp[i].x, edgesTmp[i].y)) {
            value += edgesTmp[i].w;
        }
    }
    freeDSU(ufStd);
    ufStd = NULL;

    //
    (*returnSize) = 2;
    pRetVal = (int**)malloc((*returnSize) * sizeof(int*));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); i++) {
        pRetVal[i] = (int*)malloc(edgesSize * sizeof(int));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
    }
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        for (j = 0; j < i; ++j) {
            free(pRetVal[j]);
            pRetVal[j] = NULL;
        }
        free(pRetVal);
        pRetVal = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    memset((*returnColumnSizes), 0, ((*returnSize) * sizeof(int)));

    //
    struct DisjointSetUnion* uf1 = NULL;
    struct DisjointSetUnion* uf2 = NULL;
    int v;
    for (i = 0; i < edgesSize; ++i) {
        uf1 = (struct DisjointSetUnion*)malloc(sizeof(struct DisjointSetUnion));
        if (uf1 == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        initDSU(uf1, n);
        v = 0;
        for (j = 0; j < edgesSize; ++j) {
            if ((i != j) && (unionSet(uf1, edgesTmp[j].x, edgesTmp[j].y) == true)) {
                v += edgesTmp[j].w;
            }
        }
        if (uf1->setCount != 1 || (uf1->setCount == 1 && v > value)) {
            pRetVal[0][(*returnColumnSizes)[0]++] = edgesTmp[i].id;
            freeDSU(uf1);
            uf1 = NULL;
            continue;
        }
        freeDSU(uf1);
        uf1 = NULL;

        uf2 = (struct DisjointSetUnion*)malloc(sizeof(struct DisjointSetUnion));
        if (uf2 == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free(pRetVal);
            pRetVal = NULL;
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        initDSU(uf2, n);
        unionSet(uf2, edgesTmp[i].x, edgesTmp[i].y);
        v = edgesTmp[i].w;
        for (j = 0; j < edgesSize; ++j) {
            if ((i != j) && (unionSet(uf2, edgesTmp[j].x, edgesTmp[j].y)) == true) {
                v += edgesTmp[j].w;
            }
        }
        if (v == value) {
            pRetVal[1][(*returnColumnSizes)[1]++] = edgesTmp[i].id;
        }
        freeDSU(uf2);
        uf2 = NULL;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (200)
    struct testCaseType {
        int n;
        int edges[MAX_SIZE][3];
        int edgesSize;
        int edgesColSize[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{5,
                     {{0, 1, 1}, {1, 2, 1}, {2, 3, 2}, {0, 3, 2}, {0, 4, 3}, {3, 4, 3}, {1, 4, 6}},
                     7,
                     {3, 3, 3, 3, 3, 3, 3},
                     0,
                     NULL},
                    {4, {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}, {0, 3, 1}}, 4, {3, 3, 3, 3}, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
     *  Output: [[0,1],[2,3,4,5]]
     *
     *  Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
     *  Output: [[],[0,1,2,3]]
     */

    int** pEdges = NULL;
    int** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edges =  [", testCase[i].n);
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].edgesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edges[j][k]);
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
        pAnswer =
            findCriticalAndPseudoCriticalEdges(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize,
                                               &testCase[i].returnSize, &testCase[i].returnColumnSizes);
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
