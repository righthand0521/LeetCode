#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareIntArray1D(const void *a1, const void *a2) {
    int *p1 = (int *)a1;
    int *p2 = (int *)a2;

    // ascending order
    return (p1[1] > p2[1]);
}
int compareIntArray2D(const void *a1, const void *a2) {
    int *p1 = *(int **)a1;
    int *p2 = *(int **)a2;

    return (p1[2] > p2[2]);
}
int find(int *uf, int x) {
    int retVal = 0;

    if (uf[x] != x) {
        uf[x] = find(uf, uf[x]);
    }
    retVal = uf[x];

    return retVal;
}
void merge(int *uf, int x, int y) {
    x = find(uf, x);
    y = find(uf, y);
    uf[y] = x;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool *distanceLimitedPathsExist(int n, int **edgeList, int edgeListSize, int *edgeListColSize, int **queries,
                                int queriesSize, int *queriesColSize, int *returnSize) {
    bool *pRetVal = NULL;

    (*returnSize) = queriesSize;
    pRetVal = (bool *)malloc((*returnSize) * sizeof(bool));
    if (pRetVal == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }
    memset(pRetVal, false, (*returnSize) * sizeof(bool));

    int i, j, k;

    qsort(edgeList, edgeListSize, sizeof(edgeList[0]), compareIntArray2D);

    int index[(*returnSize)][2];
    for (i = 0; i < (*returnSize); ++i) {
        index[i][0] = i;
        index[i][1] = queries[i][2];
    }
    qsort(index, (*returnSize), sizeof(index[0]), compareIntArray1D);

    int uf[n];
    for (i = 0; i < n; ++i) {
        uf[i] = i;
    }

    k = 0;
    for (j = 0; j < (*returnSize); ++j) {
        i = index[j][0];
        while ((k < edgeListSize) && (edgeList[k][2] < queries[i][2])) {
            merge(uf, edgeList[k][0], edgeList[k][1]);
            k++;
        }

        if (find(uf, queries[i][0]) == find(uf, queries[i][1])) {
            pRetVal[i] = true;
        }
    }

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_ROW_SIZE (int)(1e5)
#define MAX_COL_SIZE (3)
    struct testCaseType {
        int n;
        int edgeList[MAX_ROW_SIZE][MAX_COL_SIZE];
        int edgeListSize;
        int edgeListColSize[MAX_ROW_SIZE];
        int queries[MAX_ROW_SIZE][MAX_COL_SIZE];
        int queriesSize;
        int queriesColSize[MAX_ROW_SIZE];
        int returnSize;
    } testCase[] = {
        {3, {{0, 1, 2}, {1, 2, 4}, {2, 0, 8}, {1, 0, 16}}, 4, {3, 3, 3, 3}, {{0, 1, 2}, {0, 2, 5}}, 2, {3, 3}, 0},
        {5, {{0, 1, 10}, {1, 2, 5}, {2, 3, 9}, {3, 4, 13}}, 4, {3, 3, 3, 3}, {{0, 4, 14}, {1, 4, 13}}, 2, {3, 3}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
     *  Output: [false,true]
     *
     *  Input: n = 5, edgeList = [[0,1,10],[1,2,5],[2,3,9],[3,4,13]], queries = [[0,4,14],[1,4,13]]
     *  Output: [true,false]
     */

    int **pEdgeList = NULL;
    int **pQueries = NULL;
    bool *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, edgeList = [", testCase[i].n);
        for (j = 0; j < testCase[i].edgeListSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].edgeListColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].edgeList[j][k]);
            }
            printf("]");
        }
        printf("], queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEdgeList = (int **)malloc(testCase[i].edgeListSize * sizeof(int *));
        if (pEdgeList == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].edgeListSize; ++j) {
            pEdgeList[j] = (int *)malloc(testCase[i].edgeListColSize[j] * sizeof(int));
            if (pEdgeList[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEdgeList[k]);
                    pEdgeList[k] = NULL;
                }
                free(pEdgeList);
                pEdgeList = NULL;
                return EXIT_FAILURE;
            }
            memset(pEdgeList[j], 0, (testCase[i].edgeListColSize[j] * sizeof(int)));
            memcpy(pEdgeList[j], testCase[i].edgeList[j], (testCase[i].edgeListColSize[j] * sizeof(int)));
        }
        pQueries = (int **)malloc(testCase[i].queriesSize * sizeof(int *));
        if (pQueries == NULL) {
            perror("malloc");
            for (j = 0; j < testCase[i].edgeListSize; ++j) {
                free(pEdgeList[j]);
                pEdgeList[j] = NULL;
            }
            free(pEdgeList);
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int *)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < testCase[i].edgeListSize; ++k) {
                    free(pEdgeList[k]);
                    pEdgeList[k] = NULL;
                }
                free(pEdgeList);
                pEdgeList = NULL;
                for (k = 0; k < j; ++k) {
                    free(pQueries[k]);
                    pQueries[k] = NULL;
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, (testCase[i].queriesColSize[j] * sizeof(int)));
            memcpy(pQueries[j], testCase[i].queries[j], (testCase[i].queriesColSize[j] * sizeof(int)));
        }
        pAnswer = distanceLimitedPathsExist(testCase[i].n, pEdgeList, testCase[i].edgeListSize,
                                            testCase[i].edgeListColSize, pQueries, testCase[i].queriesSize,
                                            testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", (pAnswer[j] == true ? "true" : "false"));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].edgeListSize; ++j) {
            free(pEdgeList[j]);
            pEdgeList[j] = NULL;
        }
        free(pEdgeList);
        pEdgeList = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            free(pQueries[j]);
            pQueries[j] = NULL;
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
