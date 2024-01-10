#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char letters;
    int number;
} pair;
int compareStruct(const void* a, const void* b) {
    int pa = ((pair*)a)->number;
    int pb = ((pair*)b)->number;

    return (pa < pb);
}
char* reorganizeString(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int returnSize = sSize + 1;
    pRetVal = (char*)malloc(returnSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (returnSize * sizeof(char)));

#define MAX_LETTERS (26)  // s consists of lowercase English letters.
    pair* pCount = malloc(MAX_LETTERS * sizeof(pair));
    if (pCount == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pCount, 0, (MAX_LETTERS * sizeof(pair)));
    int maxCount = -1;
    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';  // s consists of lowercase English letters.
        pCount[idx].letters = s[i];
        pCount[idx].number += 1;
        maxCount = fmax(maxCount, pCount[idx].number);
    }

    if (maxCount > ((sSize + 1) / 2)) {
        free(pCount);
        pCount = NULL;
        return pRetVal;
    }

    qsort(pCount, MAX_LETTERS, sizeof(pair), compareStruct);
    idx = 0;
    int j;
    for (i = 0; i < MAX_LETTERS; ++i) {
        if (pCount[i].letters == 0) {
            continue;
        }

        for (j = 0; j < pCount[i].number; ++j) {
            pRetVal[idx] = pCount[i].letters;
            idx += 2;
            if (idx >= sSize) {
                idx = 1;
            }
        }
    }

    free(pCount);
    pCount = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (500 + 4)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aab"}, {"aaab"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aab"
     *  Output: "aba"
     *
     *  Input: s = "aaab"
     *  Output: ""
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = reorganizeString(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
