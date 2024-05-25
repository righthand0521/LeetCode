#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/word-break-ii/solutions/162132/dfs-guan-jian-shi-jian-zhi-cyu-yan-by-xingmian/
#define MAX_WORDDICT_SIZE (100)  // 1 <= wordDict.length <= 1000
void dfs(char* s, int pos, char** res, int* returnSize, char** wordDict, int wordDictSize, int* result, int idx,
         int* fail) {
    int i, j;

    int length, p;
    if (s[pos] == '\0') {
        length = 0;
        for (i = 0; i < idx; ++i) {
            length += strlen(wordDict[result[i]]) + 1;
        }
        res[(*returnSize)] = (char*)malloc(length * sizeof(char));
        if (res[(*returnSize)] == NULL) {
            perror("malloc");
            return;
        }
        memset(res[(*returnSize)], 0, (length * sizeof(char)));

        p = 0;
        for (i = 0; i < idx; i++) {
            for (j = 0; j < strlen(wordDict[result[i]]); j++) {
                res[(*returnSize)][p++] = wordDict[result[i]][j];
            }
            res[(*returnSize)][p++] = ' ';
        }
        res[(*returnSize)][length - 1] = '\0';
        (*returnSize)++;

        return;
    }

    if (fail[pos] == 1) {
        return;
    }

    int len, sSize;
    int fail_cnt = 0;
    for (i = 0; i < wordDictSize; i++) {
        if (pos == 0) {
            memset(fail, 0, MAX_WORDDICT_SIZE * sizeof(int));
        }

        len = strlen(wordDict[i]);
        if (fail[pos + len] == 1) {
            fail_cnt++;
            continue;
        }

        sSize = strlen(s);
        if ((sSize - pos >= len) && (memcmp(s + pos, wordDict[i], len) == 0)) {
            result[idx] = i;
            dfs(s, pos + len, res, returnSize, wordDict, wordDictSize, result, idx + 1, fail);
        } else {
            fail_cnt++;
        }
    }

    if (fail_cnt == wordDictSize) {
        fail[pos] = 1;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** wordBreak(char* s, char** wordDict, int wordDictSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;
    pRetVal = (char**)malloc(MAX_WORDDICT_SIZE * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int sSize = strlen(s);
    int* pResult = (int*)malloc(sSize * sizeof(int));
    if (pResult == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pResult, -1, (sSize * sizeof(int)));
    int* pFail = (int*)malloc(MAX_WORDDICT_SIZE * sizeof(int));
    if (pFail == NULL) {
        perror("malloc");
        free(pResult);
        pResult = NULL;
        return pRetVal;
    }
    memset(pFail, 0, (MAX_WORDDICT_SIZE * sizeof(int)));

    dfs(s, 0, pRetVal, returnSize, wordDict, wordDictSize, pResult, 0, pFail);

    //
    free(pResult);
    pResult = NULL;
    free(pFail);
    pFail = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* s;
        char* wordDict[MAX_SIZE];
        int wordDictSize;
        int returnSize;
    } testCase[] = {{"catsanddog", {"cat", "cats", "and", "sand", "dog"}, 5, 0},
                    {"pineapplepenapple", {"apple", "pen", "applepen", "pine", "pineapple"}, 5, 0},
                    {"catsandog", {"cats", "dog", "sand", "and", "cat"}, 5, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
     *  Output: ["cats and dog","cat sand dog"]
     *
     *  Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
     *  Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
     *
     *  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
     *  Output: []
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", wordDict = [", testCase[i].s);
        for (j = 0; j < testCase[i].wordDictSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].wordDict[j]);
        }
        printf("]\n");

        pAnswer = wordBreak(testCase[i].s, testCase[i].wordDict, testCase[i].wordDictSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
