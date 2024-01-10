#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORD (26)  // s and p consist of lowercase English letters.
bool isSame(int* pRecordS, int* pRecordP) {
    int retVal = false;

    int i;
    for (i = 0; i < MAX_RECORD; i++) {
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

    int lenS = strlen(s);
    int lenP = strlen(p);
    if (lenS < lenP) {
        return pRetVal;
    }

    pRetVal = (int*)malloc(lenS * sizeof(int));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }

    int i;
    int RecordS[MAX_RECORD] = {0};
    int RecordP[MAX_RECORD] = {0};

    for (i = 0; i < lenP; i++) {
        RecordS[s[i] - 'a']++;
        RecordP[p[i] - 'a']++;
    }
    if (isSame(RecordS, RecordP) == true) {
        pRetVal[(*returnSize)++] = 0;
    }

    for (i = lenP; i < lenS; i++) {
        RecordS[s[i] - 'a']++;
        RecordS[s[i - lenP] - 'a']--;
        if (isSame(RecordS, RecordP) == true) {
            pRetVal[(*returnSize)++] = i - lenP + 1;
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
