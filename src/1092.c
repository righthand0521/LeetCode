#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestCommonSupersequence(char* str1, char* str2) {
    char* pRetVal = NULL;

    int str1Size = strlen(str1);
    int str2Size = strlen(str2);

    // Initialize the base cases
    int dp[str1Size + 1][str2Size + 1];
    memset(dp, 0, sizeof(dp));
    // When str2 is empty, the supersequence is str1 itself (length = row index)
    for (int row = 0; row <= str1Size; row++) {
        dp[row][0] = row;
    }
    // When str1 is empty, the supersequence is str2 itself (length = col index)
    for (int col = 0; col <= str2Size; col++) {
        dp[0][col] = col;
    }

    for (int row = 1; row <= str1Size; row++) {
        for (int col = 1; col <= str2Size; col++) {
            if (str1[row - 1] == str2[col - 1]) {  // If characters match, inherit the length from the diagonal + 1
                dp[row][col] = dp[row - 1][col - 1] + 1;
            } else {  // If characters do not match, take the minimum length option + 1
                dp[row][col] = fmin(dp[row - 1][col], dp[row][col - 1]) + 1;
            }
        }
    }

    // Reverse the built sequence to get the correct order
    int idx = str1Size + str2Size;
    char buf[idx + 1];
    memset(buf, 0, sizeof(buf));

    int row = str1Size;
    int col = str2Size;
    while ((row > 0) && (col > 0)) {
        if (str1[row - 1] == str2[col - 1]) {  // If characters match, take it from diagonal
            buf[--idx] = str1[row - 1];
            row--;
            col--;
        } else if (dp[row - 1][col] < dp[row][col - 1]) {  // If str1’s character is part of the retVal, move up
            buf[--idx] = str1[row - 1];
            row--;
        } else {  // If str2’s character is part of the retVal, move left
            buf[--idx] = str2[col - 1];
            col--;
        }
    }

    // Append any remaining characters If there are leftover characters in str1
    while (row > 0) {
        buf[--idx] = str1[row - 1];
        row--;
    }
    // If there are leftover characters in str2
    while (col > 0) {
        buf[--idx] = str2[col - 1];
        col--;
    }

    int returnSize = strlen(buf + idx) + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));
    memcpy(pRetVal, buf + idx, returnSize - 1);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (1000)
    struct testCaseType {
        char str1[MAX_SIZE];
        char str2[MAX_SIZE];
    } testCase[] = {{"abac", "cab"}, {"aaaaaaaa", "aaaaaaaa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: str1 = "abac", str2 = "cab"
     *  Output: "cabac"
     *
     *  Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
     *  Output: "aaaaaaaa"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: str1 = \"%s\", str2 = \"%s\"\n", testCase[i].str1, testCase[i].str2);

        pAnswer = shortestCommonSupersequence(testCase[i].str1, testCase[i].str2);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
