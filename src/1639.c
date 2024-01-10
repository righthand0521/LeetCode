#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/solutions/917779/java-c-python-space-o-n/
#define MODULO (int)(1e9 + 7)
int numWays(char** words, int wordsSize, char* target) {
    int retVal = 0;

    int targetSize = strlen(target);
    long dp[targetSize + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    int wordLength = strlen(words[0]);
    int count[26];  // words[i] and target contain only lowercase English letters.
    int i, j;
    for (i = 0; i < wordLength; ++i) {
        memset(count, 0, sizeof(count));
        for (j = 0; j < wordsSize; ++j) {
            count[words[j][i] - 'a']++;
        }

        for (j = targetSize - 1; j >= 0; --j) {
            dp[j + 1] += dp[j] * count[target[j] - 'a'] % MODULO;
        }
    }
    retVal = dp[targetSize] % MODULO;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        char target[MAX_SIZE];
    } testCase[] = {{{"acca", "bbbb", "caca"}, 3, "aba"}, {{"abba", "baab"}, 2, "bab"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["acca","bbbb","caca"], target = "aba"
     *  Output: 6
     *
     *  Input: words = ["abba","baab"], target = "bab"
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], target = \"%s\"\n", testCase[i].target);

        answer = numWays(testCase[i].words, testCase[i].wordsSize, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
