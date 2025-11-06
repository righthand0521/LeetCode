#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef DSU_H
#define DSU_H

typedef struct {
    int* parent;
    int size;
} DSU;
DSU* dsuCreate(int size) {
    DSU* pObj = NULL;

    pObj = (DSU*)malloc(sizeof(DSU));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->size = size;
    pObj->parent = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        pObj->parent[i] = i;
    }

    return pObj;
}
int dsuFind(DSU* pObj, int x) {
    int retVal = 0;

    if (pObj->parent[x] != x) {
        pObj->parent[x] = dsuFind(pObj, pObj->parent[x]);
    }
    retVal = pObj->parent[x];

    return retVal;
}
void dsuJoin(DSU* pObj, int u, int v) {
    //
    pObj->parent[dsuFind(pObj, v)] = dsuFind(pObj, u);
}
void dsuFree(DSU* pObj) {
    free(pObj->parent);
    pObj->parent = NULL;
    free(pObj);
    pObj = NULL;
}

#endif  // DSU_H
#ifndef HASH_H
#define DSU_H

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem* hashFindItem(HashItem** pObj, int key) {
    HashItem* pEntry = NULL;

    HASH_FIND_INT(*pObj, &key, pEntry);

    return pEntry;
}
bool hashAddItem(HashItem** pObj, int key, int val) {
    bool retVal = false;

    if (hashFindItem(pObj, key) == NULL) {
        HashItem* pEntry = (HashItem*)malloc(sizeof(HashItem));
        if (pEntry == NULL) {
            perror("malloc");
            return retVal;
        }
        pEntry->key = key;
        pEntry->val = val;
        HASH_ADD_INT(*pObj, key, pEntry);
        retVal = true;
    }

    return retVal;
}
void hashSetItem(HashItem** pObj, int key, int val) {
    HashItem* pEntry = hashFindItem(pObj, key);
    if (pEntry == NULL) {
        hashAddItem(pObj, key, val);
    } else {
        pEntry->val = val;
    }
}
int hashGetItem(HashItem** pObj, int key, int defaultVal) {
    int retVal = defaultVal;

    HashItem* pEntry = hashFindItem(pObj, key);
    if (pEntry != NULL) {
        retVal = pEntry->val;
    }

    return retVal;
}
void hashFree(HashItem** pObj) {
    HashItem* curr = NULL;
    HashItem* tmp = NULL;
    HASH_ITER(hh, *pObj, curr, tmp) {
        HASH_DEL(*pObj, curr);
        free(curr);
    }
}

#endif  // HASH_H
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* processQueries(int c, int** connections, int connectionsSize, int* connectionsColSize, int** queries,
                    int queriesSize, int* queriesColSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    DSU* dsu = dsuCreate(c + 1);
    for (int i = 0; i < connectionsSize; i++) {
        dsuJoin(dsu, connections[i][0], connections[i][1]);
    }

    bool* online = (bool*)malloc((c + 1) * sizeof(bool));
    int* offlineCounts = (int*)calloc(c + 1, sizeof(int));
    for (int i = 0; i <= c; i++) {
        online[i] = true;
    }
    for (int i = 0; i < queriesSize; i++) {
        int op = queries[i][0];
        int x = queries[i][1];
        if (op == 2) {
            online[x] = false;
            offlineCounts[x]++;
        }
    }

    HashItem* minimumOnlineStations = NULL;
    for (int i = 1; i <= c; i++) {
        int root = dsuFind(dsu, i);
        if (hashFindItem(&minimumOnlineStations, root) == NULL) {
            hashAddItem(&minimumOnlineStations, root, -1);
        }

        int station = hashGetItem(&minimumOnlineStations, root, -1);
        if (online[i]) {
            if (station == -1 || station > i) {
                hashSetItem(&minimumOnlineStations, root, i);
            }
        }
    }

    pRetVal = (int*)malloc(queriesSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit;
    }

    for (int i = queriesSize - 1; i >= 0; i--) {
        int op = queries[i][0];
        int x = queries[i][1];
        int root = dsuFind(dsu, x);
        int station = hashGetItem(&minimumOnlineStations, root, -1);

        if (op == 1) {
            if (online[x]) {
                pRetVal[(*returnSize)++] = x;
            } else {
                pRetVal[(*returnSize)++] = station;
            }
        }

        if (op == 2) {
            if (offlineCounts[x] > 1) {
                offlineCounts[x]--;
            } else {
                online[x] = true;
                if (station == -1 || station > x) {
                    hashSetItem(&minimumOnlineStations, root, x);
                }
            }
        }
    }

    for (int i = 0, j = (*returnSize) - 1; i < j; i++, j--) {
        int temp = pRetVal[i];
        pRetVal[i] = pRetVal[j];
        pRetVal[j] = temp;
    }

exit:
    dsuFree(dsu);
    free(online);
    free(offlineCounts);
    hashFree(&minimumOnlineStations);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 1000)
    struct testCaseType {
        int c;
        int connections[MAX_SIZE][2];
        int connectionsSize;
        int connectionsColSize[MAX_SIZE];
        int queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {{5,
                     {{1, 2}, {2, 3}, {3, 4}, {4, 5}},
                     4,
                     {2, 2, 2, 2},
                     {{1, 3}, {2, 1}, {1, 1}, {2, 2}, {1, 2}},
                     5,
                     {2, 2, 2, 2, 2}},
                    {3, {}, 0, {}, {{1, 1}, {2, 1}, {1, 1}}, 3, {2, 2, 2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: c = 5, connections = [[1,2],[2,3],[3,4],[4,5]], queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]
     *  Output: [3,2,3]
     *
     *  Input: c = 3, connections = [], queries = [[1,1],[2,1],[1,1]]
     *  Output: [1,-1]
     */

    int retVal = EXIT_SUCCESS;
    int** pConnections = NULL;
    int** pQueries = NULL;
    int* pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: c = %d, connections =  [", testCase[i].c);
        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].connectionsColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].connections[j][k]);
            }
            printf("]");
        }
        printf("], queries =  [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
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
                retVal = EXIT_FAILURE;
                goto exit_pConnections;
            }
            memset(pConnections[j], 0, testCase[i].connectionsColSize[j] * sizeof(int));
            memcpy(pConnections[j], testCase[i].connections[j], testCase[i].connectionsColSize[j] * sizeof(int));
        }
        pQueries = (int**)malloc(testCase[i].queriesSize * sizeof(int*));
        if (pQueries == NULL) {
            perror("malloc");
            retVal = EXIT_FAILURE;
            goto exit_pConnections;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (int*)malloc(testCase[i].queriesColSize[j] * sizeof(int));
            if (pQueries[j] == NULL) {
                perror("malloc");
                retVal = EXIT_FAILURE;
                goto exit_pQueries;
            }
            memset(pQueries[j], 0, testCase[i].queriesColSize[j] * sizeof(int));
            memcpy(pQueries[j], testCase[i].queries[j], testCase[i].queriesColSize[j] * sizeof(int));
        }
        pAnswer =
            processQueries(testCase[i].c, pConnections, testCase[i].connectionsSize, testCase[i].connectionsColSize,
                           pQueries, testCase[i].queriesSize, testCase[i].queriesColSize, &testCase[i].returnSize);
        printf("Output:[");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    exit_pQueries:
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            if (pQueries[j]) {
                free(pQueries[j]);
                pQueries[j] = NULL;
            }
        }
        free(pQueries);
        pQueries = NULL;
    exit_pConnections:
        for (j = 0; j < testCase[i].connectionsSize; ++j) {
            if (pConnections[j]) {
                free(pConnections[j]);
                pConnections[j] = NULL;
            }
        }
        free(pConnections);
        pConnections = NULL;

        if (retVal == EXIT_FAILURE) {
            break;
        }
    }

    return retVal;
}
