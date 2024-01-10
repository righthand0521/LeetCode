#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/lru-cache/solutions/727484/c-uthash-uthashdi-ceng-shi-xian-de-shu-j-wbpw/
typedef struct {
    int key;
    int value;
    UT_hash_handle hh;
} LRUCache;

LRUCache* globalCache = NULL;
int globalCapacity;

LRUCache* lRUCacheCreate(int capacity) {
    globalCapacity = capacity;

    return globalCache;
}
int lRUCacheGet(LRUCache* obj, int key) {
    int retVal = -1;

    LRUCache* pTemp = NULL;
    HASH_FIND_INT(globalCache, &key, pTemp);
    if (pTemp == NULL) {
        return retVal;
    }
    HASH_DEL(globalCache, pTemp);
    HASH_ADD_INT(globalCache, key, pTemp);
    retVal = pTemp->value;

    return retVal;
}
void lRUCachePut(LRUCache* obj, int key, int value) {
    LRUCache* pCurrent = NULL;
    LRUCache* pNext = NULL;

    HASH_FIND_INT(globalCache, &key, pCurrent);
    if (pCurrent != NULL) {
        HASH_DEL(globalCache, pCurrent);
        pCurrent->key = key;
        pCurrent->value = value;
        HASH_ADD_INT(globalCache, key, pCurrent);
        return;
    }

    int globalCacheSize = HASH_COUNT(globalCache);
    if (globalCacheSize == globalCapacity) {
        HASH_ITER(hh, globalCache, pCurrent, pNext) {
            HASH_DEL(globalCache, pCurrent);
            free(pCurrent);
            break;
        }
    }
    LRUCache* pNew = (LRUCache*)malloc(sizeof(LRUCache));
    if (pNew == NULL) {
        perror("malloc");
        return;
    }
    pNew->key = key;
    pNew->value = value;
    HASH_ADD_INT(globalCache, key, pNew);
}
void lRUCacheFree(LRUCache* obj) {
    LRUCache* pCurrent = NULL;
    LRUCache* pNext = NULL;
    HASH_ITER(hh, globalCache, pCurrent, pNext) {
        // printf("%d: %d\n", globalCache->key, globalCache->value);
        HASH_DEL(globalCache, pCurrent);
        free(pCurrent);
    }
}
/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* methods[MAX_SIZE];
        int value[MAX_SIZE][3];
        int valSize[MAX_SIZE];
        int calls;
    } testCase[] = {{{"LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"},
                     {{2}, {1, 1}, {2, 2}, {1}, {3, 3}, {2}, {4, 4}, {1}, {3}, {4}},
                     {1, 2, 2, 1, 2, 1, 2, 1, 1, 1},
                     10},
                    {{"LRUCache", "put", "put", "get", "put", "put", "get"},
                     {{2}, {2, 1}, {2, 2}, {2}, {1, 1}, {4, 1}, {2}},
                     {1, 2, 2, 1, 2, 2, 1},
                     7}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
     *  [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
     *  Output
     *  [null, null, null, 1, null, -1, null, -1, 3, 4]
     *
     *  Input
     *  ["LRUCache", "put", "put", "get", "put", "put", "get"]
     *  [[2], [2,1], [2,2], [2], [1,1], [4,1], [2]]
     *  Output
     *  [null, null, null, 2, null, null, -1]
     */

    LRUCache* obj = NULL;
    int retInt;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ", ", testCase[i].methods[j]);
        }
        printf("]\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s[", (j == 0) ? "" : ", ");
            for (k = 0; k < testCase[i].valSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ", ", testCase[i].value[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ", ");

            if (strcmp(testCase[i].methods[j], "LRUCache") == 0) {
                obj = lRUCacheCreate(testCase[i].value[j][0]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "get") == 0) {
                retInt = lRUCacheGet(obj, testCase[i].value[j][0]);
                printf("%d", retInt);
            } else if (strcmp(testCase[i].methods[j], "put") == 0) {
                lRUCachePut(obj, testCase[i].value[j][0], testCase[i].value[j][1]);
                printf("null");
            }
        }
        printf("]\n");

        lRUCacheFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
