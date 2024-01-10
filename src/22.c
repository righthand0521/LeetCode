#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RETURN_COUNT (1430)  // 1 <= n <= 8: 1, 1, 2, 5, 14, 42, 132, 429, 1430
void backtracking(char **retVal, int n, int *returnSize, char *str, int strIdx, int open, int close) {
    int maxSize = 2 * n + 1;

    if ((open == 0) && (close == 0)) {
        retVal[(*returnSize)] = (char *)calloc(maxSize, sizeof(char));
        if (retVal[(*returnSize)] == NULL) {
            perror("calloc");
            return;
        }
        snprintf(retVal[(*returnSize)++], (maxSize * sizeof(char)), "%s", str);

        return;
    }

    str[strIdx] = '(';
    if (open > 0) {
        backtracking(retVal, n, returnSize, str, strIdx + 1, open - 1, close);
    }
    if (close > open) {
        str[strIdx] = ')';
        backtracking(retVal, n, returnSize, str, strIdx + 1, open, close - 1);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **generateParenthesis(int n, int *returnSize) {
    char **pRetVal = NULL;

    pRetVal = (char **)malloc(MAX_RETURN_COUNT * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int maxSize = 2 * n + 1;
    char *str = (char *)calloc(maxSize, sizeof(char));
    if (str == NULL) {
        perror("calloc");
        return pRetVal;
    }
    int strIdx = 0;

    (*returnSize) = 0;
    backtracking(pRetVal, n, returnSize, str, strIdx, n, n);
    free(str);
    str = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
    struct testCaseType {
        int n;
        int returnSize;
    } testCase[] = {{3, 0}, {1, 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: n = 3
     *  Output: ["((()))","(()())","(())()","()(())","()()()"]
     *
     *  Input: n = 1
     *  Output: ["()"]
     */

    char **pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: n = %d\n", testCase[i].n);

        pAnswer = generateParenthesis(testCase[i].n, &testCase[i].returnSize);
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
