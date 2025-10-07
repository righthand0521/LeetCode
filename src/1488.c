#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

// https://leetcode.cn/problems/avoid-flood-in-the-city/solutions/590510/cyu-yan-uthashshi-xian-by-liu-xiang-3-vw7g/
struct hashTable {
    int pool;
    int day;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%d: %d\n", pFree->pool, pFree->day);
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* avoidFlood(int* rains, int rainsSize, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    pRetVal = (int*)malloc(rainsSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, rainsSize * sizeof(int));

    struct hashTable* pPoolInfo = NULL;
    struct hashTable* pSunDay = NULL;
    struct hashTable *pTemp, *s1, *s2;
    int i, j, rain;
    for (i = 0; i < rainsSize; ++i) {
        rain = rains[i];

        pTemp = NULL;
        if (rain == 0) {
            pTemp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTemp == NULL) {
                perror("malloc");
                free(pRetVal);
                pRetVal = NULL;
                goto exit;
            }
            pTemp->pool = i;
            HASH_ADD_INT(pSunDay, pool, pTemp);
            pRetVal[i] = 1;
            continue;
        }

        pRetVal[i] = -1;

        s1 = NULL;
        HASH_FIND_INT(pPoolInfo, &rain, s1);
        if (s1 == NULL) {
            s1 = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (s1 == NULL) {
                perror("malloc");
                free(pRetVal);
                pRetVal = NULL;
                goto exit;
            }
            s1->pool = rain;
            s1->day = i;
            HASH_ADD_INT(pPoolInfo, pool, s1);
            continue;
        }

        pTemp = NULL;
        s2 = NULL;
        j = 0;
        HASH_ITER(hh, pSunDay, s2, pTemp) {
            if (s2->pool > s1->day) {
                break;
            }
            j++;
        }
        if (j == HASH_COUNT(pSunDay)) {
            free(pRetVal);
            pRetVal = NULL;
            goto exit;
        }

        s1->day = i;
        pRetVal[s2->pool] = s1->pool;
        HASH_DEL(pSunDay, s2);
        free(s2);
    }
    (*returnSize) = rainsSize;

exit:
    //
    freeAll(pPoolInfo);
    pPoolInfo = NULL;
    freeAll(pSunDay);
    pSunDay = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        int rains[MAX_SIZE];
        int rainsSize;
        int returnSize;
    } testCase[] = {{{1, 2, 3, 4}, 4, 0}, {{1, 2, 0, 0, 2, 1}, 6, 0}, {{1, 2, 0, 1, 2}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: rains = [1,2,3,4]
     *  Output: [-1,-1,-1,-1]
     *
     *  Input: rains = [1,2,0,0,2,1]
     *  Output: [-1,-1,2,1,-1,-1]
     *
     *  Input: rains = [1,2,0,1,2]
     *  Output: []
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: rains = [");
        for (j = 0; j < testCase[i].rainsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].rains[j]);
        }
        printf("]\n");

        pAnswer = avoidFlood(testCase[i].rains, testCase[i].rainsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", *(pAnswer + j));
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
