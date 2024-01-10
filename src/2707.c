#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uthash/uthash.h"  // https://troydhanson.github.io/uthash/

#define MAX_WORDS_LENGTH (50 + 2)  // 1 <= dictionary[i].length <= 50
struct hash_struct {
    char words[MAX_WORDS_LENGTH];
    UT_hash_handle hh;
};
void freeAll(struct hash_struct* pFree) {
    struct hash_struct* pCurrent;
    struct hash_struct* pTmp;
    HASH_ITER(hh, pFree, pCurrent, pTmp) {
        HASH_DEL(pFree, pCurrent);
        free(pCurrent);
    }
}
int minExtraChar(char* s, char** dictionary, int dictionarySize) {
    int retVal = 0;

    struct hash_struct* pDictionarySet = NULL;
    struct hash_struct* pTmp;
    int i;
    for (i = 0; i < dictionarySize; ++i) {
        pTmp = NULL;
        HASH_FIND_STR(pDictionarySet, dictionary[i], pTmp);
        if (pTmp == NULL) {
            pTmp = (struct hash_struct*)malloc(sizeof(struct hash_struct));
            if (pTmp == NULL) {
                perror("malloc");
                freeAll(pDictionarySet);
                pDictionarySet = NULL;
                return retVal;
            }
            snprintf(pTmp->words, MAX_WORDS_LENGTH, "%s", dictionary[i]);
            HASH_ADD_STR(pDictionarySet, words, pTmp);
        }
    }

    int sSize = strlen(s);
    int dp[sSize + 1];
    memset(dp, 0, sizeof(dp));
    char buf[sSize + 1];
    int start, end;
    for (start = sSize - 1; start >= 0; start--) {
        dp[start] = dp[start + 1] + 1;
        for (end = start; end < sSize; end++) {
            memset(buf, 0, sizeof(buf));
            memcpy(buf, s + start, end - start + 1);

            pTmp = NULL;
            HASH_FIND_STR(pDictionarySet, buf, pTmp);
            if (pTmp != NULL) {
                dp[start] = fmin(dp[start], dp[end + 1]);
            }
        }
    }
    retVal = dp[0];

    freeAll(pDictionarySet);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_STRING_SIZE (50)
#define MAX_DICTIONARY_SIZE (50)
    struct testCaseType {
        char s[MAX_STRING_SIZE];
        char* dictionary[MAX_DICTIONARY_SIZE];
        int dictionarySize;
    } testCase[] = {{"leetscode", {"leet", "code", "leetcode"}, 3}, {"sayhelloworld", {"hello", "world"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leetscode", dictionary = ["leet","code","leetcode"]
     *  Output: 1
     *
     *  Input: s = "sayhelloworld", dictionary = ["hello","world"]
     *  Output: 3
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", dictionary = [", testCase[i].s);
        for (j = 0; j < testCase[i].dictionarySize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].dictionary[j]);
        }
        printf("]\n");

        answer = minExtraChar(testCase[i].s, testCase[i].dictionary, testCase[i].dictionarySize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
