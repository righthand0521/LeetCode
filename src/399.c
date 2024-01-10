#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

typedef struct hashTable {
    char key[8];
    int val;
    UT_hash_handle hh;
} hashTable;
int findroot(int *p, double *w, int x) {
    if (p[x] != x) {
        int root = findroot(p, w, p[x]);
        w[x] = w[x] * w[p[x]];
        p[x] = root;
    }

    return p[x];
}
void merge(int *p, double *w, int x, int y, double val) {
    int rootx = findroot(p, w, x);
    int rooty = findroot(p, w, y);
    p[rootx] = rooty;
    w[rootx] = val * w[y] / w[x];
}
void freeAll(hashTable *pFree) {
    hashTable *current;
    hashTable *tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        HASH_DEL(pFree, current);
        free(current);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double *calcEquation(char ***equations, int equationsSize, int *equationsColSize, double *values, int valuesSize,
                     char ***queries, int queriesSize, int *queriesColSize, int *returnSize) {
    double *pRetVal = NULL;

    (*returnSize) = 0;
    int i;

    hashTable *pHashMap = NULL;

    //
    hashTable *pHash1, *pHash2;
    int id = 0;
    for (i = 0; i < equationsSize; i++) {
        pHash1 = NULL;
        HASH_FIND_STR(pHashMap, equations[i][0], pHash1);
        if (pHash1 == NULL) {
            pHash1 = (hashTable *)malloc(sizeof(hashTable));
            if (pHash1 == NULL) {
                perror("malloc");
                freeAll(pHashMap);
                pHashMap = NULL;
                return pRetVal;
            }
            pHash1->val = id++;
            strcpy(pHash1->key, equations[i][0]);
            HASH_ADD_STR(pHashMap, key, pHash1);
        }

        pHash2 = NULL;
        HASH_FIND_STR(pHashMap, equations[i][1], pHash2);
        if (pHash2 == NULL) {
            pHash2 = (hashTable *)malloc(sizeof(hashTable));
            if (pHash2 == NULL) {
                perror("malloc");
                freeAll(pHashMap);
                pHashMap = NULL;
                return pRetVal;
            }
            pHash2->val = id++;
            strcpy(pHash2->key, equations[i][1]);
            HASH_ADD_STR(pHashMap, key, pHash2);
        }
    }

    //
    int *p = (int *)malloc(sizeof(int) * id);
    if (p == NULL) {
        perror("malloc");
        freeAll(pHashMap);
        pHashMap = NULL;
        return pRetVal;
    }
    double *w = (double *)malloc(sizeof(double) * id);
    if (w == NULL) {
        perror("malloc");
        freeAll(pHashMap);
        pHashMap = NULL;
        free(p);
        p = NULL;
        return pRetVal;
    }
    for (i = 0; i < id; i++) {
        p[i] = i;
        w[i] = 1.0;
    }

    for (i = 0; i < equationsSize; i++) {
        pHash1 = NULL;
        HASH_FIND_STR(pHashMap, equations[i][0], pHash1);
        pHash2 = NULL;
        HASH_FIND_STR(pHashMap, equations[i][1], pHash2);
        merge(p, w, pHash1->val, pHash2->val, values[i]);
    }

    //
    pRetVal = (double *)malloc(sizeof(double) * queriesSize);
    if (pRetVal == NULL) {
        perror("malloc");
        freeAll(pHashMap);
        pHashMap = NULL;
        free(p);
        p = NULL;
        free(w);
        w = NULL;
        return pRetVal;
    }

    int v1, v2;
    double result;
    for (i = 0; i < queriesSize; i++) {
        result = -1.0;

        pHash1 = NULL;
        HASH_FIND_STR(pHashMap, queries[i][0], pHash1);
        pHash2 = NULL;
        HASH_FIND_STR(pHashMap, queries[i][1], pHash2);
        if (pHash1 && pHash2) {
            v1 = pHash1->val;
            v2 = pHash2->val;
            if (findroot(p, w, v1) == findroot(p, w, v2)) {
                result = w[v1] / w[v2];
            }
        }
        pRetVal[(*returnSize)++] = result;
    }

    //
    freeAll(pHashMap);
    pHashMap = NULL;
    free(p);
    p = NULL;
    free(w);
    w = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char *equations[MAX_SIZE][2];
        int equationsSize;
        int equationsColSize[MAX_SIZE];
        double values[MAX_SIZE];
        int valuesSize;
        char *queries[MAX_SIZE][2];
        int queriesSize;
        int queriesColSize[MAX_SIZE];
        int returnSize;
    } testCase[] = {
        {{{"a", "b"}, {"b", "c"}},
         2,
         {2, 2},
         {2.0, 3.0},
         2,
         {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}},
         5,
         {2, 2, 2, 2, 2},
         0},
        {{{"a", "b"}, {"b", "c"}, {"bc", "cd"}},
         3,
         {2, 2, 2},
         {1.5, 2.5, 5.0},
         3,
         {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}},
         4,
         {2, 2, 2, 2},
         0},
        {{{"a", "b"}}, 1, {2}, {0.5}, 1, {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}}, 4, {2, 2, 2, 2}, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0],
     *  queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
     *  Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
     *
     *  Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
     *  queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
     *  Output: [3.75000,0.40000,5.00000,0.20000]
     *
     *  Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
     *  Output: [0.50000,2.00000,-1.00000,-1.00000]
     */

    char ***pEquations = NULL;
    char ***pQueries = NULL;
    double *pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: equations = [");
        for (j = 0; j < testCase[i].equationsSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].equationsColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].equations[j][k]);
            }
            printf("]");
        }
        printf("], values = [");
        for (j = 0; j < testCase[i].valuesSize; ++j) {
            printf("%s%.1f", (j == 0) ? "" : ",", testCase[i].values[j]);
        }
        printf("], queries = [");
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            printf("%s%s", (j == 0) ? "" : ",", "[");
            for (k = 0; k < testCase[i].queriesColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].queries[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pEquations = (char ***)malloc(testCase[i].equationsSize * sizeof(char **));
        if (pEquations == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].equationsSize; ++j) {
            pEquations[j] = (char **)malloc(testCase[i].equationsColSize[j] * sizeof(char *));
            if (pEquations[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pEquations[k]);
                    pEquations[k] = NULL;
                }
                free(pEquations);
                pEquations = NULL;
                return EXIT_FAILURE;
            }
            memset(pEquations[j], 0, (testCase[i].equationsColSize[j] * sizeof(char *)));
            memcpy(pEquations[j], testCase[i].equations[j], (testCase[i].equationsColSize[j] * sizeof(char *)));
        }
        pQueries = (char ***)malloc(testCase[i].queriesSize * sizeof(char **));
        if (pQueries == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            pQueries[j] = (char **)malloc(testCase[i].queriesColSize[j] * sizeof(char *));
            if (pQueries[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pQueries[k]);
                    pQueries[k] = NULL;
                }
                free(pQueries);
                pQueries = NULL;
                return EXIT_FAILURE;
            }
            memset(pQueries[j], 0, (testCase[i].queriesColSize[j] * sizeof(char *)));
            memcpy(pQueries[j], testCase[i].queries[j], (testCase[i].queriesColSize[j] * sizeof(char *)));
        }
        pAnswer = calcEquation(pEquations, testCase[i].equationsSize, testCase[i].equationsColSize, testCase[i].values,
                               testCase[i].valuesSize, pQueries, testCase[i].queriesSize, testCase[i].queriesColSize,
                               &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%.5f", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].equationsSize; ++j) {
            free(pEquations[j]);
            pEquations[j] = NULL;
        }
        free(pEquations);
        pEquations = NULL;
        for (j = 0; j < testCase[i].queriesSize; ++j) {
            free(pQueries[j]);
            pQueries[j] = NULL;
        }
        free(pQueries);
        pQueries = NULL;
    }

    return EXIT_SUCCESS;
}
