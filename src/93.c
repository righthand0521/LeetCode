#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.cn/problems/restore-ip-addresses/solutions/404642/hui-su-jian-zhi-0ms100-by-shaw-r/
#define MAX_IP_FORMAT_LENGTH (5)
void dfs(char* s, char** pRetVal, int* returnSize, int step, int index, int len, char* pTmp) {
    int tmpSize = len + MAX_IP_FORMAT_LENGTH;

    if (step == 4) {
        pRetVal[*returnSize] = (char*)malloc(tmpSize * sizeof(char));
        if (pRetVal[*returnSize] == NULL) {
            perror("malloc");
            return;
        }
        memset(pRetVal[*returnSize], 0, (tmpSize * sizeof(char)));

        pTmp[index + step - 1] = '\0';
        memcpy(pRetVal[*returnSize], pTmp, (sizeof(char) * tmpSize));
        (*returnSize)++;

        return;
    }

    if ((len - index - 1 <= (3 - step) * 3) && (len - index - 1 >= (3 - step))) {
        pTmp[index + step] = s[index];
        pTmp[index + step + 1] = '.';

        dfs(s, pRetVal, returnSize, step + 1, index + 1, len, pTmp);
    }

    if ((len - index - 2 <= (3 - step) * 3) && (len - index - 2 >= (3 - step)) && (s[index] != '0')) {
        pTmp[index + step] = s[index];
        pTmp[index + step + 1] = s[index + 1];
        pTmp[index + step + 2] = '.';

        dfs(s, pRetVal, returnSize, step + 1, index + 2, len, pTmp);
    }

    if ((len - index - 3 <= (3 - step) * 3 && len - index - 3 >= (3 - step) && s[index] != '0') &&
        ((s[index] - '0') * 100 + (s[index + 1] - '0') * 10 + s[index + 2] - '0' <= 255)) {
        pTmp[index + step] = s[index];
        pTmp[index + step + 1] = s[index + 1];
        pTmp[index + step + 2] = s[index + 2];
        pTmp[index + step + 3] = '.';

        dfs(s, pRetVal, returnSize, step + 1, index + 3, len, pTmp);
    }
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** restoreIpAddresses(char* s, int* returnSize) {
    char** pRetVal = NULL;

    (*returnSize) = 0;

    int len = strlen(s);
    // IP Format: xxx.xxx.xxx.xxx or x.x.x.x
    if ((len > 12) || (len < 4)) {
        return pRetVal;
    }

#define MAX_RETURN (200)
    pRetVal = (char**)malloc(MAX_RETURN * sizeof(char*));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int tmpSize = len + MAX_IP_FORMAT_LENGTH;
    char* pTmp = (char*)malloc(tmpSize * sizeof(char));
    if (pTmp == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pTmp, 0, (tmpSize * sizeof(char)));
    dfs(s, pRetVal, returnSize, 0, 0, len, pTmp);
    free(pTmp);
    pTmp = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (20)
    struct testCaseType {
        char s[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"25525511135", 0}, {"0000", 0}, {"101023", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char** pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = restoreIpAddresses(testCase[i].s, &testCase[i].returnSize);
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
