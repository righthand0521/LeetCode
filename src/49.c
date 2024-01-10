#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (100)
struct hash_struct {
    char key[MAX_LENGTH];
    int count;
    int idx;
    UT_hash_handle hh;
};
void freeAll(struct hash_struct* pFree) {
    struct hash_struct* current;
    struct hash_struct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
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
    (*returnSize) = 0;

    int i, j, k;
    char pSortStr[MAX_LENGTH];
    struct hash_struct* map = NULL;
    struct hash_struct* temp;

    /* 1. use hash map to count strs[i] appear times to prepare malloc return arrays */
    for (i = 0; i < strsSize; ++i) {
        // sort strs[i] as hash key
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        temp = NULL;
        HASH_FIND_STR(map, pSortStr, temp);

        // strs[i] exist in hash map
        if (temp != NULL) {
            temp->count++;
            continue;
        }

        // strs[i] does not exist in hash map
        temp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
        if (temp == NULL) {
            perror("malloc");
            freeAll(map);
            map = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        snprintf(temp->key, MAX_LENGTH, "%s", pSortStr);
        temp->count = 1;
        HASH_ADD_STR(map, key, temp);

        // update returnSize
        (*returnSize)++;
    }

    /* 2. malloc return arrays */
    // update returnColumnSizes
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        freeAll(map);
        map = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    i = 0;
    for (temp = map; temp != NULL; temp = temp->hh.next) {
        (*returnColumnSizes)[i++] = temp->count;
    }

    // temporary free hash map
    freeAll(map);
    map = NULL;

    // update return char ***
    pRetVal = (char***)malloc((*returnSize) * sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }
    for (i = 0; i < (*returnSize); ++i) {
        pRetVal[i] = (char**)malloc(((*returnColumnSizes)[i]) * sizeof(char*));
        if (pRetVal[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
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
                free((*returnColumnSizes));
                (*returnColumnSizes) = NULL;
                free(pRetVal);
                pRetVal = NULL;
                (*returnSize) = 0;
                return pRetVal;
            }
            memset(pRetVal[i][j], 0, MAX_LENGTH);
        }
    }

    /* 3. re-use hash map to copy strs[i] to return arrays */
    int idx = 0;
    for (i = 0; i < strsSize; ++i) {
        // sort strs[i] as hash key
        memset(pSortStr, 0, sizeof(pSortStr));
        snprintf(pSortStr, sizeof(pSortStr), "%s", strs[i]);
        qsort(pSortStr, strlen(pSortStr), sizeof(char), compareChar);

        temp = NULL;
        HASH_FIND_STR(map, pSortStr, temp);

        // strs[i] exist in hash map
        if (temp != NULL) {
            // copy strs[i] to return arrays
            snprintf(pRetVal[temp->idx][temp->count], MAX_LENGTH, "%s", strs[i]);

            temp->count++;
            continue;
        }

        // strs[i] does not exist in hash map
        temp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
        if (temp == NULL) {
            perror("malloc");
            freeAll(map);
            map = NULL;
            for (j = 0; j < (*returnSize); ++j) {
                for (k = 0; k < (*returnColumnSizes)[j]; ++k) {
                    free(pRetVal[j][k]);
                    pRetVal[j][k] = NULL;
                }
                free(pRetVal[j]);
                pRetVal[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            free(pRetVal);
            pRetVal = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        snprintf(temp->key, MAX_LENGTH, "%s", pSortStr);
        temp->count = 1;
        temp->idx = idx;
        HASH_ADD_STR(map, key, temp);

        // copy strs[i] to return arrays
        snprintf(pRetVal[idx++][0], MAX_LENGTH, "%s", strs[i]);
    }

    // free hash map
    freeAll(map);
    map = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (10000)
    struct testCaseType {
        char* strs[MAX_SIZE];
        int strsSize;
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{{"eat", "tea", "tan", "ate", "nat", "bat"}, 6, 0, NULL}, {{""}, 1, 0, NULL}, {{"a"}, 1, 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

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
