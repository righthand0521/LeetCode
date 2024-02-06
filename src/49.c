#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (100 + 4)  // 0 <= strs[i].length <= 100
struct hashTable {
    char key[MAX_LENGTH];
    int count;
    int idx;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->count);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 - *(char*)c2);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

    //
    (*returnSize) = 0;
    (*returnColumnSizes) = NULL;

    int i, j, k;

    //
    char pSortStr[MAX_LENGTH];
    struct hashTable* pMap = NULL;
    struct hashTable* pTmp;
    for (i = 0; i < strsSize; ++i) {
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        pTmp = NULL;
        HASH_FIND_STR(pMap, pSortStr, pTmp);
        if (pTmp != NULL) {
            pTmp->count++;
            continue;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            (*returnSize) = 0;
            goto exit;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pSortStr);
        pTmp->count = 1;
        HASH_ADD_STR(pMap, key, pTmp);

        (*returnSize)++;
    }

    //
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        goto exit;
    }
    i = 0;
    for (pTmp = pMap; pTmp != NULL; pTmp = pTmp->hh.next) {
        (*returnColumnSizes)[i++] = pTmp->count;
    }
    freeAll(pMap);
    pMap = NULL;

    //
    pRetVal = (char***)malloc((*returnSize) * sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        goto exit_returnColumnSizes;
    }
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (char**)malloc(((*returnColumnSizes)[i]) * sizeof(char*));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            goto exit_returnValue;
        }
        for (j = 0; j < (*returnColumnSizes)[i]; ++j) {
            pRetVal[i][j] = (char*)malloc(MAX_LENGTH * sizeof(char));
            if (pRetVal[i][j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pRetVal[i][k]);
                    pRetVal[i][k] = NULL;
                }
                for (k = 0; k < i; ++k) {
                    free(pRetVal[k]);
                    pRetVal[k] = NULL;
                }
                goto exit_returnValue;
            }
            memset(pRetVal[i][j], 0, MAX_LENGTH);
        }
    }

    //
    int idx = 0;
    for (i = 0; i < strsSize; ++i) {
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        pTmp = NULL;
        HASH_FIND_STR(pMap, pSortStr, pTmp);
        if (pTmp != NULL) {
            snprintf(pRetVal[pTmp->idx][pTmp->count], MAX_LENGTH, "%s", strs[i]);
            pTmp->count++;
            continue;
        }
        pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
        if (pTmp == NULL) {
            perror("malloc");
            freeAll(pMap);
            pMap = NULL;
            for (j = 0; j < (*returnSize); ++j) {
                for (k = 0; k < (*returnColumnSizes)[j]; ++k) {
                    free(pRetVal[j][k]);
                    pRetVal[j][k] = NULL;
                }
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            goto exit_returnValue;
        }
        snprintf(pTmp->key, MAX_LENGTH, "%s", pSortStr);
        pTmp->count = 1;
        pTmp->idx = idx;
        HASH_ADD_STR(pMap, key, pTmp);

        snprintf(pRetVal[idx++][0], MAX_LENGTH, "%s", strs[i]);
    }

exit:
    //
    freeAll(pMap);
    pMap = NULL;

    return pRetVal;

exit_returnValue:
    free(pRetVal);
    pRetVal = NULL;

exit_returnColumnSizes:
    free((*returnColumnSizes));
    (*returnColumnSizes) = NULL;

    (*returnSize) = 0;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e4)
    struct testCaseType {
        char* strs[MAX_SIZE];
        int strsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{"eat", "tea", "tan", "ate", "nat", "bat"}, 6, 0, NULL}, {{""}, 1, 0, NULL}, {{"a"}, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: strs = ["eat","tea","tan","ate","nat","bat"]
     *  Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
     *
     *  Input: strs = [""]
     *  Output: [[""]]
     *
     *  Input: strs = ["a"]
     *  Output: [["a"]]
     */

    char** pStrs = NULL;
    char*** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: strs =  [");
        for (j = 0; j < testCase[i].strsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].strs[j]);
        }
        printf("]\n");

        pStrs = (char**)malloc(testCase[i].strsSize * sizeof(char*));
        if (pStrs == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].strsSize; ++j) {
            pStrs[j] = (char*)malloc((strlen(testCase[i].strs[j]) + 1) * sizeof(char));
            if (pStrs[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pStrs[k]) {
                        free(pStrs[k]);
                        pStrs[k] = NULL;
                    }
                }
                free(pStrs);
                pStrs = NULL;
                return EXIT_FAILURE;
            }
            memset(pStrs[j], 0, (strlen(testCase[i].strs[j]) + 1) * sizeof(char));
            memcpy(pStrs[j], testCase[i].strs[j], (strlen(testCase[i].strs[j]) + 1) * sizeof(char));
        }
        pAnswer = groupAnagrams(pStrs, testCase[i].strsSize, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                free(pAnswer[j][k]);
                pAnswer[j][k] = NULL;
            }
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
        for (j = 0; j < testCase[i].strsSize; ++j) {
            if (pStrs[j]) {
                free(pStrs[j]);
                pStrs[j] = NULL;
            }
        }
        free(pStrs);
        pStrs = NULL;
    }

    return EXIT_SUCCESS;
}
