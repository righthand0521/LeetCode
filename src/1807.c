#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_LENGTH (10 + 1)
struct hashStruct {
    char key[MAX_LENGTH];
    char value[MAX_LENGTH];
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
char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    char* pRetVal = NULL;

    int i;

    //
    int len = strlen(s);
    pRetVal = (char*)malloc((MAX_LENGTH - 2) * len * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, ((MAX_LENGTH - 2) * len * sizeof(char)));
    int returnSize = 0;

    //
    struct hashStruct* pKnowledgeHash = NULL;
    struct hashStruct* pAdd;
    for (i = 0; i < knowledgeSize; ++i) {
        pAdd = NULL;
        HASH_FIND_STR(pKnowledgeHash, knowledge[i][0], pAdd);
        pAdd = (struct hashStruct*)malloc(sizeof(struct hashStruct));
        if (pAdd == NULL) {
            perror("malloc");
            freeAll(pKnowledgeHash);
            free(pRetVal);
            return pRetVal;
        }
        snprintf(pAdd->key, MAX_LENGTH, "%s", knowledge[i][0]);
        snprintf(pAdd->value, MAX_LENGTH, "%s", knowledge[i][1]);
        HASH_ADD_STR(pKnowledgeHash, key, pAdd);
    }

    //
    bool findKey = false;
    char key[len];
    memset(key, 0, sizeof(key));
    int keySize = 0;
    struct hashStruct* pFind;
    for (i = 0; i < len; ++i) {
        if (s[i] == '(') {
            findKey = true;
        } else if (s[i] == ')') {
            pFind = NULL;
            HASH_FIND_STR(pKnowledgeHash, key, pFind);
            if (pFind != NULL) {
                returnSize += sprintf(pRetVal + returnSize, "%s", pFind->value);
            } else {
                pRetVal[returnSize++] = '?';
            }
            findKey = false;
            memset(key, 0, sizeof(key));
            keySize = 0;
        } else {
            if (findKey == true) {
                key[keySize++] = s[i];
            } else {
                pRetVal[returnSize++] = s[i];
            }
        }
    }

    //
    freeAll(pKnowledgeHash);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        char knowledge[MAX_SIZE][2][MAX_LENGTH];
        int knowledgeSize;
        int knowledgeColSize[MAX_SIZE];
    } testCase[] = {{"(name)is(age)yearsold", {{"name", "bob"}, {"age", "two"}}, 2, {2, 2}},
                    {"hi(name)", {{"a", "b"}}, 1, {2}},
                    {"(a)(a)(a)aaa", {{"a", "yes"}}, 1, {2}}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char*** pKnowledge = NULL;
    char* pAnswer = NULL;
    int i, j, k, l;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", knowledge = [", testCase[i].s);
        for (j = 0; j < testCase[i].knowledgeSize; ++j) {
            printf("%s[", (j == 0 ? "" : ","));
            for (k = 0; k < testCase[i].knowledgeColSize[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", testCase[i].knowledge[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        pKnowledge = (char***)malloc(testCase[i].knowledgeSize * sizeof(char**));
        if (pKnowledge == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].knowledgeSize; ++j) {
            pKnowledge[j] = (char**)malloc(testCase[i].knowledgeColSize[j] * sizeof(char*));
            if (pKnowledge[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    free(pKnowledge[k]);
                    pKnowledge[k] = NULL;
                }
                free(pKnowledge);
                pKnowledge = NULL;
                return EXIT_FAILURE;
            }
            memset(pKnowledge[j], 0, testCase[i].knowledgeColSize[j] * sizeof(char*));

            for (k = 0; k < 2; ++k) {
                pKnowledge[j][k] = (char*)malloc(MAX_LENGTH * sizeof(char));
                if (pKnowledge[j][k] == NULL) {
                    perror("malloc");
                    for (l = 0; l < k; ++l) {
                        free(pKnowledge[j][l]);
                        pKnowledge[j][l] = NULL;
                    }
                    for (l = 0; l < j; ++l) {
                        free(pKnowledge[l]);
                        pKnowledge[l] = NULL;
                    }
                    free(pKnowledge);
                    pKnowledge = NULL;
                    return EXIT_FAILURE;
                }
                memset(pKnowledge[j][k], 0, (MAX_LENGTH * sizeof(char)));
                memcpy(pKnowledge[j][k], testCase[i].knowledge[j][k], (MAX_LENGTH * sizeof(char)));
            }
        }
        pAnswer = evaluate(testCase[i].s, pKnowledge, testCase[i].knowledgeSize, testCase[i].knowledgeColSize);
        printf("Output: %s\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
        for (j = 0; j < testCase[i].knowledgeSize; ++j) {
            for (k = 0; k < 2; ++k) {
                free(pKnowledge[j][k]);
                pKnowledge[j][k] = NULL;
            }
            if (pKnowledge[j]) {
                free(pKnowledge[j]);
                pKnowledge[j] = NULL;
            }
        }
        free(pKnowledge);
        pKnowledge = NULL;
    }

    return EXIT_SUCCESS;
}
