#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(char* s, int** dp, int i, int j) {
    if (dp[i][j]) {
        return dp[i][j];
    }

    if (i >= j) {
        return dp[i][j] = 1;
    }

    return dp[i][j] = (s[i] == s[j] ? isPalindrome(s, dp, i + 1, j - 1) : -1);
}
void dfs(char* s, int len, int idx, int** dp, char*** ret, int* retSize, int* retColSize, char** ans, int* ansSize) {
    int i, j;

    if (idx == len) {
        int ansColSize;
        char** tmp = (char**)malloc((*ansSize) * sizeof(char*));
        if (tmp == NULL) {
            perror("malloc");
            return;
        }
        for (i = 0; i < (*ansSize); ++i) {
            ansColSize = strlen(ans[i]) + 1;
            tmp[i] = (char*)malloc(ansColSize * sizeof(char));
            if (tmp[i] == NULL) {
                perror("malloc");
                for (j = 0; j < i; ++j) {
                    free(tmp[j]);
                    tmp[j] = NULL;
                }
                free(tmp);
                tmp = NULL;
                return;
            }
            memset(tmp[i], 0, (ansColSize * sizeof(char)));
            memcpy(tmp[i], ans[i], (ansColSize * sizeof(char)));
        }
        ret[(*retSize)] = tmp;
        retColSize[(*retSize)++] = (*ansSize);

        return;
    }

    char* sub = NULL;
    for (i = idx; i < len; ++i) {
        if (isPalindrome(s, dp, idx, i) == 1) {
            sub = (char*)malloc((i - idx + 2) * sizeof(char));
            if (sub == NULL) {
                perror("malloc");
                return;
            }
            for (j = idx; j <= i; ++j) {
                sub[j - idx] = s[j];
            }
            sub[i - idx + 1] = '\0';

            ans[(*ansSize)++] = sub;
            dfs(s, len, i + 1, dp, ret, retSize, retColSize, ans, ansSize);
            --(*ansSize);

            free(sub);
            sub = NULL;
        }
    }
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** partition(char* s, int* returnSize, int** returnColumnSizes) {
    char*** pRetVal = NULL;

    int i, j;

    int len = strlen(s);

    // max return size
    (*returnSize) = len * (1 << len);

    // malloc returnColumnSizes
    (*returnColumnSizes) = (int*)malloc((*returnSize) * sizeof(int));
    if ((*returnColumnSizes) == NULL) {
        perror("malloc");
        (*returnSize) = 0;
        return pRetVal;
    }

    // malloc return char*** array
    pRetVal = (char***)malloc((*returnSize) * sizeof(char**));
    if (pRetVal == NULL) {
        perror("malloc");
        free((*returnColumnSizes));
        (*returnColumnSizes) = NULL;
        (*returnSize) = 0;
        return pRetVal;
    }

    /* Dynamic Programming Preprocessing
     *  f(i,j): s[i..j] is Palindrome or not
     *            | True, i≥j
     *  f(i,j) = <
     *            | f(i+1, j−1) ∧ (s[i]=s[j]), otherwise
     */
    int* dp[len];
    for (i = 0; i < len; ++i) {
        dp[i] = (int*)malloc(len * sizeof(int));
        if (dp[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(dp[j]);
                dp[j] = NULL;
            }
            free((*returnColumnSizes));
            (*returnColumnSizes) = NULL;
            (*returnSize) = 0;
            return pRetVal;
        }
        for (j = 0; j < len; ++j) {
            dp[i][j] = 1;
        }
    }
    for (i = len - 1; i >= 0; --i) {
        for (j = i + 1; j < len; ++j) {
            dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
        }
    }

    //
    (*returnSize) = 0;
    char* answer[len];
    int answerSize = 0;
    dfs(s, len, 0, dp, pRetVal, returnSize, *returnColumnSizes, answer, &answerSize);

    // free Dynamic Programming Preprocessing
    for (i = 0; i < len; ++i) {
        free(dp[i]);
        dp[i] = NULL;
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (16)
    struct testCaseType {
        char s[MAX_SIZE];
        int returnSize;
        int* returnColumnSizes;
    } testCase[] = {{"aab", 0, NULL}, {"a", 0, NULL}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char*** pAnswer = NULL;
    int i, j, k;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = partition(testCase[i].s, &testCase[i].returnSize, &testCase[i].returnColumnSizes);
        printf("Output: [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s[", (j == 0) ? "" : ",");
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                printf("%s\"%s\"", (k == 0) ? "" : ",", pAnswer[j][k]);
            }
            printf("]");
        }
        printf("]\n");

        printf("\n");

        for (j = 0; j < testCase[i].returnSize; ++j) {
            for (k = 0; k < testCase[i].returnColumnSizes[j]; ++k) {
                free(pAnswer[j][k]);
                pAnswer[j][k] = NULL;
            }
            free(pAnswer[j]);
            pAnswer[j] = NULL;
        }
        free(pAnswer);
        pAnswer = NULL;
        free(testCase[i].returnColumnSizes);
        testCase[i].returnColumnSizes = NULL;
    }

    return EXIT_SUCCESS;
}
