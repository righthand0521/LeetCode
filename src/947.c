#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

struct hashStruct {
    int index;
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
int getUnionFind(int* pUnionFind, int idx) {
    if (pUnionFind[idx] != idx) {
        pUnionFind[idx] = getUnionFind(pUnionFind, pUnionFind[idx]);
    }

    return pUnionFind[idx];
}
int merge(int* pUnionFind, int exist, int new) {
    int existValue = getUnionFind(pUnionFind, exist);
    int newValue = getUnionFind(pUnionFind, new);
    if (existValue == newValue) {
        return 0;
    }
    pUnionFind[newValue] = existValue;

    return 1;
}

int removeStones(int** stones, int stonesSize, int* stonesColSize) {
    int retVal = stonesSize;

    int i;

    int UnionFind[stonesSize];
    for (i = 0; i < stonesSize; ++i) {
        UnionFind[i] = i;
    }

    struct hashStruct* hashRow = NULL;
    struct hashStruct* tmpRow;
    struct hashStruct* hashCol = NULL;
    struct hashStruct* tmpCol;
    int count = stonesSize;
    for (i = 0; i < stonesSize; ++i) {
        tmpRow = NULL;
        HASH_FIND_INT(hashRow, stones[i], tmpRow);
        if (tmpRow) {
            count -= merge(UnionFind, tmpRow->index, i);
        } else {
            tmpRow = malloc(sizeof(struct hashStruct));
            if (tmpRow == NULL) {
                perror("malloc");
                freeAll(hashRow);
                freeAll(hashCol);
                return retVal;
            }
            tmpRow->value = stones[i][0];
            tmpRow->index = i;
            HASH_ADD_INT(hashRow, value, tmpRow);
        }

        tmpCol = NULL;
        HASH_FIND_INT(hashCol, stones[i] + 1, tmpCol);
        if (tmpCol) {
            count -= merge(UnionFind, tmpCol->index, i);
        } else {
            tmpCol = malloc(sizeof(struct hashStruct));
            if (tmpCol == NULL) {
                perror("malloc");
                freeAll(hashRow);
                freeAll(hashCol);
                return retVal;
            }
            tmpCol->value = stones[i][1];
            tmpCol->index = i;
            HASH_ADD_INT(hashCol, value, tmpCol);
        }
    }
    retVal -= count;
    freeAll(hashRow);
    freeAll(hashCol);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        int stones[MAX_SIZE][2];
        int stonesSize;
        int stonesColSize;
    } testCase[] = {{{{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}}, 6, 2},
                    {{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}, 5, 2},
                    {{{0, 0}}, 1, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int** pStones = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: stones = [");
        for (j = 0; j < testCase[i].stonesSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].stonesColSize; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].stones[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pStones = (int**)malloc(testCase[i].stonesSize * sizeof(int*));
        if (pStones == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].stonesSize; ++j) {
            pStones[j] = (int*)malloc(testCase[i].stonesColSize * sizeof(int));
            if (pStones[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pStones[k]) {
                        free(pStones[k]);
                    }
                }
                free(pStones);
                pStones = NULL;
                return EXIT_FAILURE;
            }
            memset(pStones[j], 0, testCase[i].stonesColSize * sizeof(int));
            memcpy(pStones[j], testCase[i].stones[j], testCase[i].stonesColSize * sizeof(int));
        }
        answer = removeStones(pStones, testCase[i].stonesSize, &testCase[i].stonesColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].stonesSize; ++j) {
            if (pStones[j]) {
                free(pStones[j]);
            }
        }
        free(pStones);
        pStones = NULL;
    }

    return EXIT_SUCCESS;
}
