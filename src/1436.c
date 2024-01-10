#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (10 + 1)
struct hashStruct {
    char key[MAX_LENGTH];
    UT_hash_handle hh;
};
void freeAll(struct hashStruct* pFree) {
    struct hashStruct* current;
    struct hashStruct* tmp;
    HASH_ITER(hh, pFree, current, tmp) {
        // printf("%s\n", pFree->key);
        HASH_DEL(pFree, current);
        free(current);
    }
}
char* destCity(char*** paths, int pathsSize, int* pathsColSize) {
    char* pRetVal = NULL;

    struct hashStruct* pOutgoing = NULL;
    struct hashStruct* pAdd;
    int i;
    for (i = 0; i < pathsSize; ++i) {
        pAdd = NULL;
        HASH_FIND_STR(pOutgoing, paths[i][0], pAdd);
        pAdd = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (pAdd == NULL) {
            perror("malloc");
            freeAll(pOutgoing);
            free(pRetVal);
            return pRetVal;
        }
        snprintf(pAdd->key, MAX_LENGTH, "%s", paths[i][0]);
        HASH_ADD_STR(pOutgoing, key, pAdd);
    }

    for (i = 0; i < pathsSize; ++i) {
        pAdd = NULL;
        HASH_FIND_STR(pOutgoing, paths[i][1], pAdd);
        if (pAdd == NULL) {
            pRetVal = paths[i][1];
            break;
        }
    }

    freeAll(pOutgoing);
    pOutgoing = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(100)
    struct testCaseType {
        char paths[MAX_SIZE][2][MAX_LENGTH];
        int pathsSize;
        int pathsColSize[MAX_SIZE];
    } testCase[] = {{{{"London", "New York"}, {"New York", "Lima"}, {"Lima", "Sao Paulo"}}, 3, {2, 2, 2}},
                    {{{"B", "C"}, {"D", "B"}, {"C", "A"}}, 3, {2, 2, 2}},
                    {{{"A", "Z"}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
     *  Output: "Sao Paulo"
     *
     *  Input: paths = [["B","C"],["D","B"],["C","A"]]
     *  Output: "A"
     *
     *  Input: paths = [["A","Z"]]
     *  Output: "Z"
     */

    char*** pPaths = NULL;
    char* pAnswer = NULL;
    int i, j, k, l;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: paths = [");
        for (j = 0; j < testCase[i].pathsSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].pathsColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].paths[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pPaths = (char***)malloc(testCase[i].pathsSize * sizeof(char**));
        if (pPaths == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].pathsSize; ++j) {
            pPaths[j] = (char**)malloc(testCase[i].pathsColSize[j] * sizeof(char*));
            if (pPaths[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pPaths[k]);
                    pPaths[k] = NULL;
                }
                free(pPaths);
                pPaths = NULL;
                return EXIT_FAILURE;
            }
            memset(pPaths[j], 0, testCase[i].pathsColSize[j] * sizeof(char*));

            for (k = 0; k < 2; ++k) {
                pPaths[j][k] = (char*)malloc(MAX_LENGTH * sizeof(char));
                if (pPaths[j][k] == NULL) {
                    perror("malloc");
                    for (l = 0; l < k; ++l) {
                        free(pPaths[j][l]);
                        pPaths[j][l] = NULL;
                    }
                    for (l = 0; l < j; ++l) {
                        free(pPaths[l]);
                        pPaths[l] = NULL;
                    }
                    free(pPaths);
                    pPaths = NULL;
                    return EXIT_FAILURE;
                }
                memset(pPaths[j][k], 0, (MAX_LENGTH * sizeof(char)));
                memcpy(pPaths[j][k], testCase[i].paths[j][k], (MAX_LENGTH * sizeof(char)));
            }
        }
        pAnswer = destCity(pPaths, testCase[i].pathsSize, testCase[i].pathsColSize);
        printf("Output: %s\n", pAnswer);

        printf("\n");

        for (j = 0; j < testCase[i].pathsSize; ++j) {
            for (k = 0; k < 2; ++k) {
                free(pPaths[j][k]);
                pPaths[j][k] = NULL;
            }
            if (pPaths[j]) {
                free(pPaths[j]);
                pPaths[j] = NULL;
            }
        }
        free(pPaths);
        pPaths = NULL;
    }

    return EXIT_SUCCESS;
}
