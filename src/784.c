#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtracking(char *s, int idx, char **returnValue, int *returnSize) {
    while ((s[idx] != '\0') && (isdigit(s[idx]))) {
        ++idx;
    }

    if (s[idx] == '\0') {
        returnValue[(*returnSize)] = (char *)malloc((strlen(s) + 1) * sizeof(char));
        if (returnValue[(*returnSize)] == NULL) {
            perror("malloc");
            return;
        }
        memset(returnValue[(*returnSize)], 0, ((strlen(s) + 1) * sizeof(char)));
        memcpy(returnValue[(*returnSize)], s, ((strlen(s) + 1) * sizeof(char)));
        (*returnSize)++;

        return;
    }

    s[idx] ^= 32;
    backtracking(s, idx + 1, returnValue, returnSize);

    s[idx] ^= 32;
    backtracking(s, idx + 1, returnValue, returnSize);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCasePermutation(char *s, int *returnSize) {
    char **pRetVal = NULL;

    int len = strlen(s);

    (*returnSize) = 0;
    pRetVal = (char **)malloc((1 << len) * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    backtracking(s, 0, pRetVal, returnSize);

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (12)
    struct testCaseType {
        char s[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"a1b2", 0}, {"3z4", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char **pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = letterCasePermutation(testCase[i].s, &testCase[i].returnSize);
        printf("Output = [");
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
