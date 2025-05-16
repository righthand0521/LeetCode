#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check(const char* s1, const char* s2) {
    bool retVal = false;

    int s1Size = strlen(s1);
    int s2Size = strlen(s2);
    if (s1Size != s2Size) {
        return retVal;
    }

    int diff = 0;
    for (int i = 0; s1[i]; i++) {
        if (s1[i] == s2[i]) {
            continue;
        }

        diff++;
        if (diff > 1) {
            return retVal;
        }
    }
    if (diff == 1) {
        retVal = true;
    }

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** getWordsInLongestSubsequence(char** words, int wordsSize, int* groups, int groupsSize, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int dp[wordsSize];
    int prev[wordsSize];
    for (int i = 0; i < wordsSize; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }
    int maxIndex = 0;
    for (int i = 1; i < wordsSize; i++) {
        for (int j = 0; j < i; j++) {
            if ((check(words[i], words[j]) == true) && (dp[j] + 1 > dp[i]) && (groups[i] != groups[j])) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }

        if (dp[i] > dp[maxIndex]) {
            maxIndex = i;
        }
    }

    int count = 0;
    for (int i = maxIndex; i >= 0; i = prev[i]) {
        count++;
    }

    pRetVal = (char**)malloc(count * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int index = 0;
    for (int i = maxIndex; i >= 0; i = prev[i]) {
        pRetVal[index++] = words[i];
    }

    char* temp;
    for (int i = 0; i < count / 2; i++) {
        temp = pRetVal[i];
        pRetVal[i] = pRetVal[count - 1 - i];
        pRetVal[count - 1 - i] = temp;
    }

    (*returnSize) = count;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        int groups[MAX_SIZE];
        int groupsSize;
        int returnSize;
    } testCase[] = {{{"bab", "dab", "cab"}, 3, {1, 2, 2}, 3, 0}, {{"a", "b", "c", "d"}, 4, {1, 2, 3, 4}, 4, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["bab","dab","cab"], groups = [1,2,2]
     *  Output: ["bab","cab"]
     *
     *  Input: words = ["a","b","c","d"], groups = [1,2,3,4]
     *  Output: ["a","b","c","d"]
     */

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], groups = [");
        for (j = 0; j < testCase[i].groupsSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", testCase[i].groups[j]);
        }
        printf("]\n");

        pAnswer = getWordsInLongestSubsequence(testCase[i].words, testCase[i].wordsSize, testCase[i].groups,
                                               testCase[i].groupsSize, &testCase[i].returnSize);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        // for (j = 0; j < testCase[i].returnSize; ++j) {
        //     free(pAnswer[j]);
        //     pAnswer[j] = NULL;
        // }
        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
