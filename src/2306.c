#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_IDEAS_CHAR (26)       // ideas[i] consists of lowercase English letters.
#define MAX_NAME_LENGTH (10 + 2)  // 1 <= ideas[i].length <= 10
struct hash_struct {
    char idea[MAX_NAME_LENGTH];
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
long long distinctNames(char** ideas, int ideasSize) {
    long long retVal = 0;

    int i, j;

    //
    struct hash_struct* hashTable = NULL;
    struct hash_struct* pTmp;
    for (i = 0; i < ideasSize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(hashTable, ideas[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(hashTable);
                hashTable = NULL;
                return retVal;
            }
            snprintf(pTmp->idea, MAX_NAME_LENGTH, "%s", ideas[i]);
            HASH_ADD_STR(hashTable, idea, pTmp);
        }
    }

    //
    long long statistic[MAX_IDEAS_CHAR][MAX_IDEAS_CHAR];
    memset(statistic, 0, sizeof(statistic));
    int prefix;
    char buf[MAX_NAME_LENGTH];
    for (i = 0; i < ideasSize; ++i) {
        prefix = ideas[i][0] - 'a';

        for (j = 0; j < MAX_IDEAS_CHAR; ++j) {
            memset(buf, 0, sizeof(buf));
#if 0  // Time Limit Exceeded
            snprintf(buf, sizeof(buf), "%c%s", j + 'a', ideas[i] + 1);
#else
            buf[0] = j + 'a';
            strncpy(buf + 1, ideas[i] + 1, sizeof(buf) - 2);
#endif

            pTmp = NULL;
            HASH_FIND_STR(hashTable, buf, pTmp);
            if (pTmp == NULL) {
                ++statistic[prefix][j];
            }
        }
    }
    freeAll(hashTable);

    //
    for (i = 0; i < MAX_IDEAS_CHAR; ++i) {
        for (j = 0; j < MAX_IDEAS_CHAR; ++j) {
            retVal += (statistic[i][j] * statistic[j][i]);
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(50000)
#define MAX_LENGTH (10)
    struct testCaseType {
        char ideas[MAX_SIZE][MAX_LENGTH];
        int ideasSize;
    } testCase[] = {{{"coffee", "donuts", "time", "toffee"}, 4}, {{"lack", "back"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char** pIdeas = NULL;
    long long answer = 0;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: ideas =  [");
        for (j = 0; j < testCase[i].ideasSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].ideas[j]);
        }
        printf("]\n");

        pIdeas = (char**)malloc(testCase[i].ideasSize * sizeof(char*));
        if (pIdeas == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
        for (j = 0; j < testCase[i].ideasSize; ++j) {
            pIdeas[j] = (char*)malloc((strlen(testCase[i].ideas[j]) + 1) * sizeof(char));
            if (pIdeas[j] == NULL) {
                perror("malloc");
                for (k = 0; k < j; ++k) {
                    if (pIdeas[k]) {
                        free(pIdeas[k]);
                        pIdeas[k] = NULL;
                    }
                }
                free(pIdeas);
                pIdeas = NULL;
                return EXIT_FAILURE;
            }
            memset(pIdeas[j], 0, (strlen(testCase[i].ideas[j]) + 1) * sizeof(char));
            memcpy(pIdeas[j], testCase[i].ideas[j], (strlen(testCase[i].ideas[j]) + 1) * sizeof(char));
        }
        answer = distinctNames(pIdeas, testCase[i].ideasSize);
        printf("Output: %lld\n", answer);

        printf("\n");

        for (j = 0; j < testCase[i].ideasSize; ++j) {
            free(pIdeas[j]);
            pIdeas[j] = NULL;
        }
        free(pIdeas);
    }

    return EXIT_SUCCESS;
}
