#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNION_FIND (1)
#if (UNION_FIND)
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
int initDisjointSet(struct DisjointSetUnion* obj, int n) {
    obj->f = (int*)malloc(n * sizeof(int));
    if (obj->f == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    obj->size = (int*)malloc(n * sizeof(int));
    if (obj->size == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    obj->n = n;
    obj->setCount = n;

    int i;
    for (i = 0; i < n; ++i) {
        obj->f[i] = i;
        obj->size[i] = 1;
    }

    return EXIT_SUCCESS;
}
void freeDisjointSet(struct DisjointSetUnion* obj) {
    if (obj->f) {
        free(obj->f);
        obj->f = NULL;
    }

    if (obj->size) {
        free(obj->size);
        obj->size = NULL;
    }
}
int find(struct DisjointSetUnion* obj, int x) {
    int retVal = x;

    if (obj->f[x] != x) {
        obj->f[x] = find(obj, obj->f[x]);
        retVal = obj->f[x];
    }

    return retVal;
}
bool unionSet(struct DisjointSetUnion* obj, int x, int y) {
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
#endif
int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize) {
    int retVal = -1;

    if (connectionsSize < n - 1) {
        return retVal;
    }

    struct DisjointSetUnion* pUnionFind = (struct DisjointSetUnion*)malloc(sizeof(struct DisjointSetUnion));
    if (pUnionFind == NULL) {
        perror("malloc");
        return retVal;
    }
    if (initDisjointSet(pUnionFind, n) == EXIT_FAILURE) {
        freeDisjointSet(pUnionFind);
        free(pUnionFind);
        pUnionFind = NULL;
        return retVal;
    }

    int i;
    for (i = 0; i < connectionsSize; ++i) {
        unionSet(pUnionFind, connections[i][0], connections[i][1]);
    }
    retVal = pUnionFind->setCount - 1;

    freeDisjointSet(pUnionFind);
    free(pUnionFind);
    pUnionFind = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int n;
        int connections[MAX_SIZE][2];
        int connectionsSize;
        int connectionsColSize[MAX_SIZE];
    } testCase[] = {{4, {{0, 1}, {0, 2}, {1, 2}}, 3, {2, 2, 2}},
                    {6, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}}, 5, {2, 2, 2, 2, 2}},
                    {6, {{0, 1}, {0, 2}, {0, 3}, {1, 2}}, 4, {2, 2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 4, connections = [[0,1],[0,2],[1,2]]
     *  Output: 1
     *
     *  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
     *  Output: 2
     *
     *  Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
     *  Output: -1
     */

    int** pConnections = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, connections = [", testCase[i].n);
        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].connectionsColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].connections[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pConnections = (int**)malloc(testCase[i].connectionsSize * sizeof(int*));
        if (pConnections == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            pConnections[j] = (int*)malloc(testCase[i].connectionsColSize[j] * sizeof(int));
            if (pConnections[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pConnections[k]);
                }
                free(pConnections);
                return EXIT_FAILURE;
            }
            memset(pConnections[j], 0, (testCase[i].connectionsColSize[j] * sizeof(int)));
            memcpy(pConnections[j], testCase[i].connections[j], (testCase[i].connectionsColSize[j] * sizeof(int)));
        }

        answer =
            makeConnected(testCase[i].n, pConnections, testCase[i].connectionsSize, testCase[i].connectionsColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            free(pConnections[j]);
            pConnections[j] = NULL;
        }
        free(pConnections);
        pConnections = NULL;
    }

    return EXIT_SUCCESS;
}
