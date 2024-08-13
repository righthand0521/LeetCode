#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // s and p consist of lowercase English letters.
bool isSame(int* pRecordS, int* pRecordP) {
    int retVal = false;

    int i;
    for (i = 0; i < MAX_LETTERS; i++) {
        if (pRecordS[i] != pRecordP[i]) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char* s, char* p, int* returnSize) {
    int* pRetVal = NULL;

    (*returnSize) = 0;

    int sSize = strlen(s);
    int pSize = strlen(p);
    if (sSize < pSize) {
        return pRetVal;
    }

    pRetVal = (int*)malloc(sSize * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (sSize * sizeof(int)));

    int sCount[MAX_LETTERS];
    memset(sCount, 0, sizeof(sCount));
    int pCount[MAX_LETTERS];
    memset(pCount, 0, sizeof(pCount));

    int i;
    for (i = 0; i < pSize; i++) {
        sCount[s[i] - 'a']++;
        pCount[p[i] - 'a']++;
    }
    if (isSame(sCount, pCount) == true) {
        pRetVal[(*returnSize)++] = 0;
    }

    for (i = pSize; i < sSize; i++) {
        sCount[s[i] - 'a']++;
        sCount[s[i - pSize] - 'a']--;
        if (isSame(sCount, pCount) == true) {
            pRetVal[(*returnSize)++] = i - pSize + 1;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (3 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        char p[MAX_SIZE];
        int returnSize;
    } testCase[] = {{"cbaebabacd", "abc", 0}, {"abab", "ab", 0}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "cbaebabacd", p = "abc"
     *  Output: [0,6]
     *
     *  Input: s = "abab", p = "ab"
     *  Output: [0,1,2]
     */

    int* pAnswer = NULL;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", p = \"%s\"\n", testCase[i].s, testCase[i].p);

        pAnswer = findAnagrams(testCase[i].s, testCase[i].p, &testCase[i].returnSize);
        printf("Output = [");
        for (j = 0; j < testCase[i].returnSize; ++j) {
            printf("%s%d", (j == 0) ? "" : ",", pAnswer[j]);
        }
        printf("]\n");

        printf("\n");

        if (pAnswer != NULL) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
