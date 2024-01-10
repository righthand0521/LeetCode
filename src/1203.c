#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* topologicalSort(int* returnSize, int* degree, int** graph, int* graphColSize, int* items, int itemsSize) {
    int* pRetVal = NULL;

    int i;

    int recordQueue[itemsSize];
    memset(recordQueue, 0, sizeof(recordQueue));
    int recordQueueHead = 0;
    int recordQueueTail = 0;
    for (i = 0; i < itemsSize; i++) {
        if (degree[items[i]] == 0) {
            recordQueue[recordQueueTail++] = items[i];
        }
    }

    (*returnSize) = 0;
    int* pVisited = (int*)malloc(itemsSize * sizeof(int));
    if (pVisited == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pVisited, 0, (itemsSize * sizeof(int)));
    int u, v;
    while (recordQueueHead < recordQueueTail) {
        u = recordQueue[recordQueueHead++];
        pVisited[(*returnSize)++] = u;

        for (i = 0; i < graphColSize[u]; i++) {
            v = graph[u][i];
            if (--degree[v] == 0) {
                recordQueue[recordQueueTail++] = v;
            }
        }
    }

    if ((*returnSize) == itemsSize) {
        pRetVal = pVisited;
    } else {
        free(pVisited);
        pVisited = NULL;
        (*returnSize) = 0;
    }

    return pRetVal;
}
void freeGroupItem(int** groupItem, int groupItemSize) {
    int i;
    for (i = 0; i < groupItemSize; ++i) {
        free(groupItem[i]);
        groupItem[i] = NULL;
    }
}
void freeGroupGraph(int** groupGraph, int groupGraphSize) {
    int i;
    for (i = 0; i < groupGraphSize; ++i) {
        free(groupGraph[i]);
        groupGraph[i] = NULL;
    }
}
void freeItemGraph(int** itemGraph, int itemGraphSize) {
    int i;
    for (i = 0; i < itemGraphSize; ++i) {
        free(itemGraph[i]);
        itemGraph[i] = NULL;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortItems(int n, int m, int* group, int groupSize, int** beforeItems, int beforeItemsSize, int* beforeItemsColSize,
               int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;
    int i, j;

    //
    int groupItemSize = n + m;
    int* groupItem[groupItemSize];
    int groupItemColSize[groupItemSize];
    int groupItemColCapacity[groupItemSize];
    for (i = 0; i < groupItemSize; i++) {
        groupItem[i] = (int*)malloc(sizeof(int));
        if (groupItem[i] == NULL) {
            perror("malloc");
            freeGroupItem(groupItem, i);
            return pRetVal;
        }
        groupItemColSize[i] = 0;
        groupItemColCapacity[i] = 0;
    }
    //
    int leftId = m;
    for (i = 0; i < n; ++i) {
        if (group[i] == -1) {
            group[i] = leftId++;
        }
        if (groupItemColSize[group[i]] == groupItemColCapacity[group[i]]) {
            int* x = &groupItemColCapacity[group[i]];
            *x = (*x) ? (*x) * 2 : 1;
            groupItem[group[i]] = (int*)realloc(groupItem[group[i]], sizeof(int) * (*x));
            if (groupItem[group[i]] == NULL) {
                perror("malloc");
                freeGroupItem(groupItem, groupItemSize);
                return pRetVal;
            }
        }
        groupItem[group[i]][groupItemColSize[group[i]]++] = i;
    }

    //
    int groupGraphSize = n + m;
    int* groupGraph[groupGraphSize];
    int groupGraphColSize[groupGraphSize];
    int groupGraphColCapacity[groupGraphSize];
    for (i = 0; i < groupGraphSize; i++) {
        groupGraph[i] = (int*)malloc(sizeof(int));
        if (groupGraph[i] == NULL) {
            perror("malloc");
            freeGroupItem(groupItem, groupItemSize);
            freeGroupGraph(groupGraph, i);
            return pRetVal;
        }
        groupGraphColSize[i] = 0;
        groupGraphColCapacity[i] = 0;
    }
    //
    int itemGraphSize = n;
    int* itemGraph[itemGraphSize];
    int itemGraphColSize[itemGraphSize];
    int itemGraphColCapacity[itemGraphSize];
    for (i = 0; i < itemGraphSize; i++) {
        itemGraph[i] = (int*)malloc(sizeof(int));
        if (itemGraph[i] == NULL) {
            perror("malloc");
            freeGroupItem(groupItem, groupItemSize);
            freeGroupGraph(groupGraph, groupGraphSize);
            freeItemGraph(itemGraph, i);
            return pRetVal;
        }
        itemGraphColSize[i] = 0;
        itemGraphColCapacity[i] = 0;
    }
    //
    int groupDegree[n + m];
    memset(groupDegree, 0, sizeof(groupDegree));
    int itemDegree[n];
    memset(itemDegree, 0, sizeof(itemDegree));
    int item, beforeGroupId;
    int groupId;
    for (i = 0; i < n; ++i) {
        groupId = group[i];
        for (j = 0; j < beforeItemsColSize[i]; j++) {
            item = beforeItems[i][j];
            beforeGroupId = group[item];
            if (beforeGroupId == groupId) {
                itemDegree[i]++;
                if (itemGraphColSize[item] == itemGraphColCapacity[item]) {
                    int* x = &itemGraphColCapacity[item];
                    (*x) = (*x) ? (*x) * 2 : 1;
                    itemGraph[item] = (int*)realloc(itemGraph[item], (*x) * sizeof(int));
                    if (itemGraph[item] == NULL) {
                        perror("malloc");
                        freeGroupItem(groupItem, groupItemSize);
                        freeGroupGraph(groupGraph, groupGraphSize);
                        freeItemGraph(itemGraph, itemGraphSize);
                        return pRetVal;
                    }
                }
                itemGraph[item][itemGraphColSize[item]++] = i;
            } else {
                groupDegree[groupId]++;
                if (groupGraphColSize[beforeGroupId] == groupGraphColCapacity[beforeGroupId]) {
                    int* x = &groupGraphColCapacity[beforeGroupId];
                    (*x) = (*x) ? (*x) * 2 : 1;
                    groupGraph[beforeGroupId] = (int*)realloc(groupGraph[beforeGroupId], (*x) * sizeof(int));
                    if (groupGraph[beforeGroupId] == NULL) {
                        perror("malloc");
                        freeGroupItem(groupItem, groupItemSize);
                        freeGroupGraph(groupGraph, groupGraphSize);
                        freeItemGraph(itemGraph, itemGraphSize);
                        return pRetVal;
                    }
                }
                groupGraph[beforeGroupId][groupGraphColSize[beforeGroupId]++] = groupId;
            }
        }
    }

    //
    int id[n + m];
    for (i = 0; i < n + m; ++i) {
        id[i] = i;
    }
    int groupTopSortSize;
    int* groupTopSort = topologicalSort(&groupTopSortSize, groupDegree, groupGraph, groupGraphColSize, id, n + m);
    if (groupTopSortSize == 0) {
        freeGroupItem(groupItem, groupItemSize);
        freeGroupGraph(groupGraph, groupGraphSize);
        freeItemGraph(itemGraph, itemGraphSize);
        return pRetVal;
    }
    //
    pRetVal = (int*)malloc(groupTopSortSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        freeGroupItem(groupItem, groupItemSize);
        freeGroupGraph(groupGraph, groupGraphSize);
        freeItemGraph(itemGraph, itemGraphSize);
        free(groupTopSort);
        groupTopSort = NULL;
        return pRetVal;
    }
    //
    int* pRet = NULL;
    int retSize;
    int curGroupId, curGroupSize;
    for (i = 0; i < groupTopSortSize; i++) {
        curGroupId = groupTopSort[i];
        curGroupSize = groupItemColSize[curGroupId];
        if (curGroupSize == 0) {
            continue;
        }

        pRet = topologicalSort(&retSize, itemDegree, itemGraph, itemGraphColSize, groupItem[curGroupId],
                               groupItemColSize[curGroupId]);
        if (retSize == 0) {
            freeGroupItem(groupItem, groupItemSize);
            freeGroupGraph(groupGraph, groupGraphSize);
            freeItemGraph(itemGraph, itemGraphSize);
            free(groupTopSort);
            groupTopSort = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        for (j = 0; j < retSize; j++) {
            pRetVal[(*returnSize)++] = pRet[j];
        }
        free(pRet);
        pRet = NULL;
    }

    //
    freeGroupItem(groupItem, groupItemSize);
    freeGroupGraph(groupGraph, groupGraphSize);
    freeItemGraph(itemGraph, itemGraphSize);
    free(groupTopSort);
    groupTopSort = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(3 * 100)
    struct testCaseType {
        int n;
        int m;
        int group[MAX_SIZE];
        int groupSize;
        int beforeItems[MAX_SIZE][MAX_SIZE];
        int beforeItemsSize;
        int beforeItemsColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {
        {8, 2, {-1, -1, 1, 0, 0, 1, 0, -1}, 8, {{}, {6}, {5}, {6}, {3, 6}, {}, {}, {}}, 8, {0, 1, 1, 1, 2, 0, 0, 0}, 0},
        {8, 2, {-1, -1, 1, 0, 0, 1, 0, -1}, 8, {{}, {6}, {5}, {6}, {3}, {}, {4}, {}}, 8, {0, 1, 1, 1, 1, 0, 1, 0}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3,6],[],[],[]]
     *  Output: [6,3,4,1,5,2,0,7]
     *
     *  Input: n = 8, m = 2, group = [-1,-1,1,0,0,1,0,-1], beforeItems = [[],[6],[5],[6],[3],[],[4],[]]
     *  Output: []
     */

    int** pBeforeItems = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d, m = %d, group =  [", testCase[i].n, testCase[i].m);
        for (j = 0; j < testCase[i].groupSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].group[j]);
        }
        printf("], beforeItems =  [");
        for (j = 0; j < testCase[i].beforeItemsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].beforeItemsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].beforeItems[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pBeforeItems = (int**)malloc(testCase[i].beforeItemsSize * sizeof(int*));
        if (pBeforeItems == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].beforeItemsSize; ++j) {
            pBeforeItems[j] = (int*)malloc(testCase[i].beforeItemsColSize[j] * sizeof(int));
            if (pBeforeItems[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pBeforeItems[k]) {
                        free(pBeforeItems[k]);
                        pBeforeItems[k] = NULL;
                    }
                }
                free(pBeforeItems);
                pBeforeItems = NULL;
                return EXIT_FAILURE;
            }
            memset(pBeforeItems[j], 0, testCase[i].beforeItemsColSize[j] * sizeof(int));
            memcpy(pBeforeItems[j], testCase[i].beforeItems[j], testCase[i].beforeItemsColSize[j] * sizeof(int));
        }
        pAnswer = sortItems(testCase[i].n, testCase[i].m, testCase[i].group, testCase[i].groupSize, pBeforeItems,
                            testCase[i].beforeItemsSize, testCase[i].beforeItemsColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].beforeItemsSize; ++j) {
            if (pBeforeItems[j]) {
                free(pBeforeItems[j]);
                pBeforeItems[j] = NULL;
            }
        }
        free(pBeforeItems);
        pBeforeItems = NULL;
    }

    return EXIT_SUCCESS;
}
