#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UNIONFIND_H
#define UNIONFIND_H
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
struct DisjointSetUnion {
    int* f;
    int* size;
    int n;
    int setCount;
};
void initDSU(struct DisjointSetUnion* obj, int n) {
    obj->f = malloc(sizeof(int) * n);
    obj->size = malloc(sizeof(int) * n);
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
    obj->f = NULL;
    free(obj->size);
    obj->size = NULL;
    free(obj);
    obj = NULL;
}
int find(struct DisjointSetUnion* obj, int x) {
    //
    return obj->f[x] == x ? x : (obj->f[x] = find(obj, obj->f[x]));
}
int unionSet(struct DisjointSetUnion* obj, int x, int y) {
    int fx = find(obj, x), fy = find(obj, y);
    if (fx == fy) {
        return false;
    }

    if (obj->size[fx] < obj->size[fy]) {
        swap(&fx, &fy);
    }
    obj->size[fx] += obj->size[fy];
    obj->f[fy] = fx;
    obj->setCount--;
    return true;
}
int connected(struct DisjointSetUnion* obj, int x, int y) {
    //
    return find(obj, x) == find(obj, y);
}
#endif  // UNIONFIND_H
struct Tuple {
    int x;
    int y;
    int z;
};
int compareStruct(const void* a1, const void* a2) {
    struct Tuple* p1 = (struct Tuple*)a1;
    struct Tuple* p2 = (struct Tuple*)a2;

    // ascending order
    return (p1->z > p2->z);
}
int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize) {
    int retVal = 0;

    int rows = heightsSize;
    int columns = heightsColSize[0];  // 1 <= rows, columns <= 100
    int i, j;

    struct Tuple edges[columns * rows * 2];
    int id;
    int edgesSize = 0;
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < columns; ++j) {
            id = i * columns + j;
            if (i > 0) {
                edges[edgesSize].x = id - columns;
                edges[edgesSize].y = id;
                edges[edgesSize++].z = fabs(heights[i][j] - heights[i - 1][j]);
            }
            if (j > 0) {
                edges[edgesSize].x = id - 1;
                edges[edgesSize].y = id;
                edges[edgesSize++].z = fabs(heights[i][j] - heights[i][j - 1]);
            }
        }
    }
    qsort(edges, edgesSize, sizeof(struct Tuple), compareStruct);

    struct DisjointSetUnion* uf = malloc(sizeof(struct DisjointSetUnion));
    initDSU(uf, rows * columns);
    for (i = 0; i < edgesSize; i++) {
        unionSet(uf, edges[i].x, edges[i].y);
        if (connected(uf, 0, rows * columns - 1)) {
            retVal = edges[i].z;
            break;
        }
    }
    freeDSU(uf);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        int heights[MAX_SIZE][MAX_SIZE];
        int heightsSize;
        int heightsColSize[MAX_SIZE];
    } testCase[] = {
        {{{1, 2, 2}, {3, 8, 2}, {5, 3, 5}}, 3, {3, 3, 3}},
        {{{1, 2, 3}, {3, 8, 4}, {5, 3, 5}}, 3, {3, 3, 3}},
        {{{1, 2, 1, 1, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 2, 1, 2, 1}, {1, 1, 1, 2, 1}}, 5, {5, 5, 5, 5, 5}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
     *  Output: 2
     *
     *  Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
     *  Output: 1
     *
     *  Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
     *  Output: 0
     */

    int** pHeights = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: heights = [");
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].heightsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].heights[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pHeights = (int**)malloc(testCase[i].heightsSize * sizeof(int*));
        if (pHeights == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].heightsSize; ++j) {
            pHeights[j] = (int*)malloc(testCase[i].heightsColSize[j] * sizeof(int));
            if (pHeights[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pHeights[k]);
                    pHeights[k] = NULL;
                }
                free(pHeights);
                pHeights = NULL;
                return EXIT_FAILURE;
            }
            memset(pHeights[j], 0, testCase[i].heightsColSize[j] * sizeof(int));
            memcpy(pHeights[j], testCase[i].heights[j], testCase[i].heightsColSize[j] * sizeof(int));
        }
        answer = minimumEffortPath(pHeights, testCase[i].heightsSize, testCase[i].heightsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].heightsSize; ++j) {
            free(pHeights[j]);
        }
        free(pHeights);
        pHeights = NULL;
    }

    return EXIT_SUCCESS;
}
