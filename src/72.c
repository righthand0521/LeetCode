#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minDistance(char* word1, char* word2) {
    int retVal = 0;

    int word1Size = strlen(word1);
    int word2Size = strlen(word2);
    int dp[word1Size + 1][word2Size + 1];
    memset(dp, 0, sizeof(dp));

    /* Example: Input: word1 = "horse", word2 = "ros"
     *      r o s
     *    0 1 2 3
     *  h 1 1 2 3
     *  o 2 2 1 2
     *  r 3 2 2 2
     *  s 4 3 3 2
     *  e 5 4 4 3
     */
    int idx1 = 0;
    for (idx1 = 0; idx1 <= word1Size; ++idx1) {
        dp[idx1][0] = idx1;
    }
    int idx2 = 0;
    for (idx2 = 0; idx2 <= word2Size; ++idx2) {
        dp[0][idx2] = idx2;
    }
    int insertOperations;
    int deleteOperations;
    int replaceOperations;
    for (idx1 = 1; idx1 <= word1Size; ++idx1) {
        for (idx2 = 1; idx2 <= word2Size; ++idx2) {
            insertOperations = dp[idx1][idx2 - 1];
            deleteOperations = dp[idx1 - 1][idx2];
            replaceOperations = dp[idx1 - 1][idx2 - 1];
            if (word1[idx1 - 1] == word2[idx2 - 1]) {
                dp[idx1][idx2] = replaceOperations;
            } else {
                dp[idx1][idx2] = 1 + fmin(fmin(insertOperations, deleteOperations), replaceOperations);
            }
        }
    }
    retVal = dp[word1Size][word2Size];

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word1;
        char* word2;
    } testCase[] = {{"horse", "ros"}, {"intention", "execution"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word1 = "horse", word2 = "ros"
     *  Output: 3
     *
     *  Input: word1 = "intention", word2 = "execution"
     *  Output: 5
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word1 = \"%s\", word2 = \"%s\"\n", testCase[i].word1, testCase[i].word2);

        answer = minDistance(testCase[i].word1, testCase[i].word2);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
