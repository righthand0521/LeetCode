#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_KEY_SIZE (300 + 4)  // m == matrix.length, n == matrix[i].length, 1 <= m, n <= 300
struct hashTable {
    char key[MAX_KEY_SIZE];
    int value;
    UT_hash_handle hh;
};
void freeAll(struct hashTable* pFree) {
    struct hashTable* current;
    struct hashTable* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s: %d\n", pFree->key, pFree->value);
        HASH_DEL(pFree, current);
        free(current);
    }
}
int maxEqualRowsAfterFlips(int** matrix, int matrixSize, int* matrixColSize) {
    int retVal = 0;

    struct hashTable* pPatternFrequency = NULL;  // Map to store frequency of each pattern
    struct hashTable* pTmp;
    char patternBuilder[MAX_KEY_SIZE];
    for (int row = 0; row < matrixSize; ++row) {
        memset(patternBuilder, 0, sizeof(patternBuilder));

        // Convert row to pattern relative to its first element
        for (int col = 0; col < matrixColSize[row]; col++) {
            // 'T' if current element matches first element, 'F' otherwise
            if (matrix[row][0] == matrix[row][col]) {
                strcat(patternBuilder, "T");
            } else {
                strcat(patternBuilder, "F");
            }
        }

        // Convert pattern to string and update its frequency in map
        pTmp = NULL;
        HASH_FIND_STR(pPatternFrequency, patternBuilder, pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pPatternFrequency);
                pPatternFrequency = NULL;
                return retVal;
            }
            snprintf(pTmp->key, MAX_KEY_SIZE, "%s", patternBuilder);
            pTmp->value = 0;
            HASH_ADD_STR(pPatternFrequency, key, pTmp);
        }
        pTmp->value++;
    }

    // Find the pattern with maximum frequency
    struct hashTable* pFree = NULL;
    pTmp = NULL;
    HASH_ITER(hh, pPatternFrequency, pFree, pTmp) {
        // printf("%s: %d\n", pPatternFrequency->key, pPatternFrequency->value);
        retVal = fmax(pPatternFrequency->value, retVal);
        HASH_DEL(pPatternFrequency, pFree);
        free(pFree);
        pFree = NULL;
    }
    pPatternFrequency = NULL;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        int matrix[MAX_SIZE][MAX_SIZE];
        int matrixSize;
        int matrixColSize[MAX_SIZE];
    } testCase[] = {{{{0, 1}, {1, 1}}, 2, {2, 2}},
                    {{{0, 1}, {1, 0}}, 2, {2, 2}},
                    {{{0, 0, 0}, {0, 0, 1}, {1, 1, 0}}, 3, {3, 3, 3}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: matrix = [[0,1],[1,1]]
     *  Output: 1
     *
     *  Input: matrix = [[0,1],[1,0]]
     *  Output: 2
     *
     *  Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
     *  Output: 2
     */

    int** pMatrix = NULL;
    int answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: matrix = [");
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].matrixColSize[j]; ++k) {
                printf("%s%d", (k == 0) ? "" : ",", testCase[i].matrix[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pMatrix = (int**)malloc(testCase[i].matrixSize * sizeof(int*));
        if (pMatrix == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].matrixSize; ++j) {
            pMatrix[j] = (int*)malloc(testCase[i].matrixColSize[j] * sizeof(int));
            if (pMatrix[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pMatrix[k]) {
                        free(pMatrix[k]);
                        pMatrix[k] = NULL;
                    }
                }
                free(pMatrix);
                pMatrix = NULL;
                return EXIT_FAILURE;
            }
            memset(pMatrix[j], 0, testCase[i].matrixColSize[j] * sizeof(int));
            memcpy(pMatrix[j], testCase[i].matrix[j], testCase[i].matrixColSize[j] * sizeof(int));
        }
        answer = maxEqualRowsAfterFlips(pMatrix, testCase[i].matrixSize, testCase[i].matrixColSize);
        printf("Output: %d\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].matrixSize; ++j) {
            if (pMatrix[j]) {
                free(pMatrix[j]);
                pMatrix[j] = NULL;
            }
        }
        free(pMatrix);
        pMatrix = NULL;
    }

    return EXIT_SUCCESS;
}
