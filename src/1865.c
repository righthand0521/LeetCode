#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} HashItem;
HashItem *hashFindItem(HashItem **obj, int key) {
    HashItem *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);
    return pEntry;
}
bool hashAddItem(HashItem **obj, int key, int val) {
    if (hashFindItem(obj, key)) {
        return false;
    }
    HashItem *pEntry = (HashItem *)malloc(sizeof(HashItem));
    pEntry->key = key;
    pEntry->val = val;
    HASH_ADD_INT(*obj, key, pEntry);
    return true;
}
bool hashSetItem(HashItem **obj, int key, int val) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        hashAddItem(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}
int hashGetItem(HashItem **obj, int key, int defaultVal) {
    HashItem *pEntry = hashFindItem(obj, key);
    if (!pEntry) {
        return defaultVal;
    }
    return pEntry->val;
}
void hashFree(HashItem **obj) {
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp) {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

#endif  // HASHTABLE_H
typedef struct {
    int *nums1;
    int nums2Size;
    int *nums2;
    int nums1Size;
    HashItem *frequency;
} FindSumPairs;
FindSumPairs *findSumPairsCreate(int *nums1, int nums1Size, int *nums2, int nums2Size) {
    FindSumPairs *pObj = NULL;

    pObj = (FindSumPairs *)malloc(sizeof(FindSumPairs));
    if (pObj == NULL) {
        perror("malloc");
        return pObj;
    }
    pObj->nums1 = nums1;
    pObj->nums1Size = nums1Size;
    pObj->nums2 = nums2;
    pObj->nums2Size = nums2Size;
    pObj->frequency = NULL;
    for (int i = 0; i < nums2Size; i++) {
        hashSetItem(&pObj->frequency, nums2[i], hashGetItem(&pObj->frequency, nums2[i], 0) + 1);
    }

    return pObj;
}
void findSumPairsAdd(FindSumPairs *obj, int index, int val) {
    hashSetItem(&obj->frequency, obj->nums2[index], hashGetItem(&obj->frequency, obj->nums2[index], 0) - 1);
    obj->nums2[index] += val;
    hashSetItem(&obj->frequency, obj->nums2[index], hashGetItem(&obj->frequency, obj->nums2[index], 0) + 1);
}
int findSumPairsCount(FindSumPairs *obj, int tot) {
    int retVal = 0;

    for (int i = 0; i < obj->nums1Size; i++) {
        int rest = tot - obj->nums1[i];
        if (hashFindItem(&obj->frequency, rest)) {
            retVal += hashGetItem(&obj->frequency, rest, 0);
        }
    }

    return retVal;
}
void findSumPairsFree(FindSumPairs *obj) {
    hashFree(&obj->frequency);
    free(obj);
}
/**
 * Your FindSumPairs struct will be instantiated and called as such:
 * FindSumPairs* obj = findSumPairsCreate(nums1, nums1Size, nums2, nums2Size);
 * findSumPairsAdd(obj, index, val);
 * int param_2 = findSumPairsCount(obj, tot);
 * findSumPairsFree(obj);
 */

int main(int argc, char **argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char *methods[MAX_SIZE];
        int nums1[MAX_SIZE][MAX_SIZE];
        int nums1Size[MAX_SIZE];
        int nums2[MAX_SIZE][MAX_SIZE];
        int nums2Size[MAX_SIZE];
        int index[MAX_SIZE];
        int val[MAX_SIZE];
        int tot[MAX_SIZE];
        int calls;
    } testCase[] = {{{"FindSumPairs", "count", "add", "count", "count", "add", "add", "count"},
                     {{1, 1, 2, 2, 2, 3}, {}, {}, {}, {}, {}, {}, {}},
                     {6, 0, 0, 0, 0, 0, 0, 0},
                     {{1, 4, 5, 2, 5, 4}, {}, {}, {}, {}, {}, {}, {}},
                     {6, 0, 0, 0, 0, 0, 0, 0},
                     {INT_MAX, INT_MAX, 3, INT_MAX, INT_MAX, 0, 1, INT_MAX},
                     {INT_MAX, INT_MAX, 2, INT_MAX, INT_MAX, 1, 1, INT_MAX},
                     {INT_MAX, 7, INT_MAX, 8, 4, INT_MAX, INT_MAX, 7},
                     8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input
     *  ["FindSumPairs", "count", "add", "count", "count", "add", "add", "count"]
     *  [[[1, 1, 2, 2, 2, 3], [1, 4, 5, 2, 5, 4]], [7], [3, 2], [8], [4], [0, 1], [1, 1], [7]]
     *  Output
     *  [null, 8, null, 2, 1, null, null, 11]
     */

    FindSumPairs *obj = NULL;
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
            for (k = 0; k < testCase[i].nums1Size[j]; ++k) {
                printf("%s%d", (k == 0) ? "[[" : ", ", testCase[i].nums1[j][k]);
                printf("%s", (k == (testCase[i].nums1Size[j] - 1)) ? "], " : "");
            }
            for (k = 0; k < testCase[i].nums2Size[j]; ++k) {
                printf("%s%d", (k == 0) ? "[" : ", ", testCase[i].nums2[j][k]);
                printf("%s", (k == (testCase[i].nums2Size[j] - 1)) ? "]]" : "");
            }
            if (testCase[i].index[j] != INT_MAX) {
                printf(", [%d, %d]", testCase[i].index[j], testCase[i].val[j]);
            }
            if (testCase[i].tot[j] != INT_MAX) {
                printf(", [%d]", testCase[i].tot[j]);
            }
        }
        printf("]\n");

        printf("Output\n");
        printf("[");
        for (j = 0; j < testCase[i].calls; ++j) {
            printf("%s", (j == 0) ? "" : ", ");

            if (strcmp(testCase[i].methods[j], "FindSumPairs") == 0) {
                obj = findSumPairsCreate(testCase[i].nums1[j], testCase[i].nums1Size[j], testCase[i].nums2[j],
                                         testCase[i].nums2Size[j]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "add") == 0) {
                findSumPairsAdd(obj, testCase[i].index[j], testCase[i].val[j]);
                printf("null");
            } else if (strcmp(testCase[i].methods[j], "count") == 0) {
                retInt = findSumPairsCount(obj, testCase[i].tot[j]);
                printf("%d", retInt);
            }
        }
        printf("]\n");

        findSumPairsFree(obj);
        obj = NULL;

        printf("\n");
    }

    return EXIT_SUCCESS;
}
