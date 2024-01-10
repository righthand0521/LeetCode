#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtracking(char *digits, int *returnSize, char **pRetVal, char **phoneMap, char *combination,
                  int *combinationIdx, int index) {
    char *pTmp = NULL;

    int digitsSize = strlen(digits);
    if (index == digitsSize) {
        pTmp = (char *)malloc(((*combinationIdx) + 1) * sizeof(char));
        if (pTmp == NULL) {
            perror("malloc");
            return;
        }
        memset(pTmp, 0, (((*combinationIdx) + 1) * sizeof(char)));
        memcpy(pTmp, combination, (((*combinationIdx) + 1) * sizeof(char)));
        pRetVal[(*returnSize)++] = pTmp;
        return;
    }

    char *letters = phoneMap[digits[index] - '0'];
    int len = strlen(letters);
    for (int i = 0; i < len; i++) {
        combination[(*combinationIdx)++] = letters[i];
        combination[(*combinationIdx)] = 0;
        backtracking(digits, returnSize, pRetVal, phoneMap, combination, combinationIdx, index + 1);
        combination[--(*combinationIdx)] = 0;
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int *returnSize) {
    char **pRetVal = NULL;

    (*returnSize) = 0;

    int digitsSize = strlen(digits);

    //
    int maxReturnsize = 1;
    int i;
    for (i = 0; i < digitsSize; i++) {
        maxReturnsize *= 4;
    }
    pRetVal = (char **)malloc(maxReturnsize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    //
    if (digitsSize == 0) {
        return pRetVal;
    }

    //
    int phoneMapSize = 10;
    char **phoneMap = (char **)malloc(phoneMapSize * sizeof(char *));
    if (pRetVal == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    int phoneMapColSize = 5;
    int j;
    for (i = 0; i < phoneMapSize; ++i) {
        phoneMap[i] = (char *)malloc(phoneMapColSize * sizeof(char));
        if (phoneMap[i] == NULL) {
            perror("malloc");
            for (j = 0; j < i; ++j) {
                free(phoneMap[j]);
                phoneMap[j] = NULL;
            }
            free(phoneMap);
            phoneMap = NULL;
            free(pRetVal);
            pRetVal = NULL;
            return pRetVal;
        }
        memset(phoneMap[i], 0, (phoneMapColSize * sizeof(char)));
    }
    snprintf(phoneMap[2], (phoneMapColSize * sizeof(char)), "abc");
    snprintf(phoneMap[3], (phoneMapColSize * sizeof(char)), "def");
    snprintf(phoneMap[4], (phoneMapColSize * sizeof(char)), "ghi");
    snprintf(phoneMap[5], (phoneMapColSize * sizeof(char)), "jkl");
    snprintf(phoneMap[6], (phoneMapColSize * sizeof(char)), "mno");
    snprintf(phoneMap[7], (phoneMapColSize * sizeof(char)), "pqrs");
    snprintf(phoneMap[8], (phoneMapColSize * sizeof(char)), "tuv");
    snprintf(phoneMap[9], (phoneMapColSize * sizeof(char)), "wxyz");
    int combinationSize = digitsSize + 1;
    char *combination = (char *)malloc(combinationSize * sizeof(char));
    if (combination == NULL) {
        perror("malloc");
        free(pRetVal);
        pRetVal = NULL;
        return pRetVal;
    }
    memset(combination, 0, (combinationSize * sizeof(char)));
    int combinationIdx = 0;
    backtracking(digits, returnSize, pRetVal, phoneMap, combination, &combinationIdx, 0);

    //
    for (i = 0; i < phoneMapSize; ++i) {
        free(phoneMap[i]);
        phoneMap[i] = NULL;
    }
    free(phoneMap);
    phoneMap = NULL;
    free(combination);
    combination = NULL;

    return pRetVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (4)
    struct testCaseType {
        char digits[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"23", 0}, {"", 0}, {"2", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: digits = "23"
     *  Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
     *
     *  Input: digits = ""
     *  Output: []
     *
     *  Input: digits = "2"
     *  Output: ["a","b","c"]
     */

    char **pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: digits = \"%s\"\n", testCase[i].digits);

        pAnswer = letterCombinations(testCase[i].digits, &testCase[i].returnSize);
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
