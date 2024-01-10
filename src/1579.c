#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b) {
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}
struct DisjointSetUnion {
    int *f;
    int *size;
    int n;
    int setCount;
};
void initDSU(struct DisjointSetUnion *obj, int n) {
    obj->f = (int *)malloc(n * sizeof(int));
    if (obj->f == NULL) {
        perror("malloc");
        return;
    }
    obj->size = (int *)malloc(n * sizeof(int));
    if (obj->size == NULL) {
        perror("malloc");
        free(obj->f);
        obj->f = NULL;
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
void freeDSU(struct DisjointSetUnion *obj) {
    free(obj->f);
    obj->f = NULL;
    free(obj->size);
    obj->size = NULL;
    free(obj);
    obj = NULL;
}
int find(struct DisjointSetUnion *obj, int x) {
    int retVal = 0;

    if (obj->f[x] != x) {
        obj->f[x] = find(obj, obj->f[x]);
    }
    retVal = obj->f[x];

    return retVal;
}
int unionSet(struct DisjointSetUnion *obj, int x, int y) {
    int retVal = false;

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
int maxNumEdgesToRemove(int n, int **edges, int edgesSize, int *edgesColSize) {
    int retVal = 0;

    struct DisjointSetUnion *ufa = (struct DisjointSetUnion *)malloc(sizeof(struct DisjointSetUnion));
    if (ufa == NULL) {
        perror("malloc");
        return retVal;
    }
    initDSU(ufa, n);

    struct DisjointSetUnion *ufb = (struct DisjointSetUnion *)malloc(sizeof(struct DisjointSetUnion));
    if (ufb == NULL) {
        perror("malloc");
        freeDSU(ufa);
        return retVal;
    }
    initDSU(ufb, n);

    int i;

    for (i = 0; i < edgesSize; i++) {
        edges[i][1]--;
        edges[i][2]--;
    }

    for (i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 3) {
            if (unionSet(ufa, edges[i][1], edges[i][2]) == false) {
                ++retVal;
            } else {
                unionSet(ufb, edges[i][1], edges[i][2]);
            }
        }
    }

    for (i = 0; i < edgesSize; i++) {
        if (edges[i][0] == 1) {
            if (unionSet(ufa, edges[i][1], edges[i][2]) == false) {
                ++retVal;
            }
        } else if (edges[i][0] == 2) {
            if (unionSet(ufb, edges[i][1], edges[i][2]) == false) {
                ++retVal;
            }
        }
    }

    if ((ufa->setCount != 1) || (ufb->setCount != 1)) {
        retVal = -1;
    }

    freeDSU(ufa);
    freeDSU(ufb);

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (int)(1e5)
#define MAX_COL_SIZE (3)
    struct testCaseType {
        int n;
        int edges[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgesSize;
        int edgesColSize[MAX_ROW_SIZE];
    } testCase[] = {{4, {{3, 1, 2}, {3, 2, 3}, {1, 1, 3}, {1, 2, 4}, {1, 1, 2}, {2, 3, 4}}, 6, {3, 3, 3, 3, 3, 3}},
                    {4, {{3, 1, 2}, {3, 2, 3}, {1, 1, 4}, {2, 1, 4}}, 4, {3, 3, 3, 3}},
                    {4, {{3, 2, 3}, {1, 1, 2}, {2, 3, 4}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
     *  Output: 2
     *
     *  Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
     *  Output: 0
     *
     *  Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
     *  Output: -1
     */

    int **pEdges = NULL;
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
        printf("]\n");

        pEdges = (int **)malloc(testCase[i].edgesSize * sizeof(int *));
        if (pEdges == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgesSize; ++j) {
            pEdges[j] = (int *)malloc(testCase[i].edgesColSize[j] * sizeof(int));
            if (pEdges[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdges[k]);
                    pEdges[k] = NULL;
                }
                free(pEdges);
                pEdges = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdges[j], 0, (testCase[i].edgesColSize[j] * sizeof(int)));
            memcpy(pEdges[j], testCase[i].edges[j], (testCase[i].edgesColSize[j] * sizeof(int)));
        }
        answer = maxNumEdgesToRemove(testCase[i].n, pEdges, testCase[i].edgesSize, testCase[i].edgesColSize);
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
