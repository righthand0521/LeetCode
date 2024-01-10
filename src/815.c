#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vector {
    int* arr;
    int capacity;
    int size;
};
void init(struct Vector* vec) {
    vec->arr = (int*)malloc(sizeof(int));
    vec->capacity = 1;
    vec->size = 0;
}
void push_back(struct Vector* vec, int val) {
    if (vec->size == vec->capacity) {
        vec->capacity <<= 1;
        vec->arr = realloc(vec->arr, sizeof(int) * vec->capacity);
    }
    vec->arr[vec->size++] = val;
}
int numBusesToDestination(int** routes, int routesSize, int* routesColSize, int source, int target) {
    int retVal = 0;

    //
    if (source == target) {
        return retVal;
    }

    //
    int i, j, k;

    //
    struct Vector rec[100001];
    for (i = 0; i < 100001; i++) {
        init(&rec[i]);
    }

    int edge[routesSize][routesSize];
    memset(edge, 0, sizeof(edge));
    int site;
    for (i = 0; i < routesSize; i++) {
        for (j = 0; j < routesColSize[i]; j++) {
            site = routes[i][j];
            for (k = 0; k < rec[site].size; k++) {
                edge[i][rec[site].arr[k]] = true;
                edge[rec[site].arr[k]][i] = true;
            }
            push_back(&rec[site], i);
        }
    }

    //
    int dis[routesSize];
    memset(dis, -1, sizeof(dis));

    int que[routesSize];
    memset(que, 0, sizeof(que));
    int left = 0;
    int right = 0;
    for (i = 0; i < rec[source].size; i++) {
        dis[rec[source].arr[i]] = 1;
        que[right++] = rec[source].arr[i];
    }

    int x, y;
    while (left < right) {
        x = que[left++];
        for (y = 0; y < routesSize; y++) {
            if (edge[x][y] && dis[y] == -1) {
                dis[y] = dis[x] + 1;
                que[right++] = y;
            }
        }
    }

    //
    retVal = INT_MAX;
    for (i = 0; i < rec[target].size; i++) {
        if (dis[rec[target].arr[i]] != -1) {
            retVal = fmin(retVal, dis[rec[target].arr[i]]);
        }
    }
    if (retVal == INT_MAX) {
        retVal = -1;
    }

    //
    for (i = 0; i < 100001; i++) {
        free(rec[i].arr);
        rec[i].arr = NULL;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_ROW_SIZE (500)
#define MAX_COL_SIZE (int)(1e3)  //  1 <= routes[i].length <= 10^5
    struct testCaseType {
        int routes[MAX_ROW_SIZE][MAX_COL_SIZE];
        int routesSize;
        int routesColSize[MAX_ROW_SIZE];
        int source;
        int target;
    } testCase[] = {{{{1, 2, 7}, {3, 6, 7}}, 2, {3, 3}, 1, 6},
                    {{{7, 12}, {4, 5, 15}, {6}, {15, 19}, {9, 12, 13}}, 5, {2, 3, 1, 2, 3}, 15, 12}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
     *  Output: 2
     *
     *  Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
     *  Output: -1
     */

    int** pRoutes = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("routes = [");
        for (j = 0; j < testCase[i].routesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].routesColSize[j]; ++k) {
                printf("%s%d", (k == 0 ? "" : ","), testCase[i].routes[j][k]);
            }
            printf("]");
        }
        printf("], source = %d, target = %d\n", testCase[i].source, testCase[i].target);

        pRoutes = (int**)malloc(testCase[i].routesSize * sizeof(int*));
        if (pRoutes == NULL) {
            perror("calloc");
            return EXIT_FAILURE;
        }
        memset(pRoutes, 0, testCase[i].routesSize * sizeof(int*));
        for (j = 0; j < testCase[i].routesSize; ++j) {
            pRoutes[j] = (int*)malloc(testCase[i].routesColSize[j] * sizeof(int));
            if (pRoutes[j] == NULL) {
                perror("calloc");
                for (k = 0; k < j; ++k) {
                    free(pRoutes[k]);
                    pRoutes[k] = NULL;
                }
                free(pRoutes);
                pRoutes = NULL;
            }
            memset(pRoutes[j], 0, (testCase[i].routesColSize[j] * sizeof(int)));
            memcpy(pRoutes[j], testCase[i].routes[j], (testCase[i].routesColSize[j] * sizeof(int)));
        }
        answer = numBusesToDestination(pRoutes, testCase[i].routesSize, testCase[i].routesColSize, testCase[i].source,
                                       testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].routesSize; ++j) {
            free(pRoutes[j]);
            pRoutes[j] = NULL;
        }
        free(pRoutes);
        pRoutes = NULL;
    }

    return EXIT_SUCCESS;
}
