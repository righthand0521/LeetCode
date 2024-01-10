#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool wordBreak(char* s, char** wordDict, int wordDictSize) {
    bool retVal = false;

    int sSize = strlen(s);

    bool dp[sSize + 1];
    memset(dp, false, sizeof(dp));
    dp[0] = true;
    char sub[sSize + 1];
    int i, j, k;
    for (i = 1; i <= sSize; i++) {
        for (j = 0; j < i; j++) {
            if (dp[j] == false) {
                continue;
            }

            memset(sub, 0, sizeof(sub));
            strncpy(sub, s + j, i - j);
            for (k = 0; k < wordDictSize; ++k) {
                if (strcmp(sub, wordDict[k]) == 0) {
                    dp[i] = true;
                    j = i;
                    break;
                }
            }
        }
    }
    retVal = dp[sSize];

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_STRING_SIZE (300)
#define MAX_WORDDICT_SIZE (1000)
    struct testCaseType {
        char s[MAX_STRING_SIZE];
        char* wordDict[MAX_WORDDICT_SIZE];
        int wordDictSize;
    } testCase[] = {{"leetcode", {"leet", "code"}, 2},
                    {"applepenapple", {"apple", "pen"}, 2},
                    {"catsandog", {"cats", "dog", "sand", "and", "cat"}, 5}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "leetcode", wordDict = ["leet","code"]
     *  Output: true
     *
     *  Input: s = "applepenapple", wordDict = ["apple","pen"]
     *  Output: true
     *
     *  Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
     *  Output: false
     */

    bool answer = false;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", wordDict = [", testCase[i].s);
        for (j = 0; j < testCase[i].wordDictSize; ++j) {
            printf("%s\"%s\"", (j == 0 ? "" : ","), testCase[i].wordDict[j]);
        }
        printf("]\n");

        answer = wordBreak(testCase[i].s, testCase[i].wordDict, testCase[i].wordDictSize);
        printf("Output: %s\n", (answer == true ? "true" : "false"));

        printf("\n");
    }

    return EXIT_SUCCESS;
}
