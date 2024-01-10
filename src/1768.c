#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mergeAlternately(char* word1, char* word2) {
    char* pRetVal = NULL;

    int len1 = strlen(word1);
    int len2 = strlen(word2);

    int len = len1 + len2 + 1;
    pRetVal = (char*)malloc(len * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (len * sizeof(char)));

    int idx = 0;
    int idx1 = 0;
    int idx2 = 0;
    while ((idx1 < len1) || (idx2 < len2)) {
        if (idx1 < len1) {
            pRetVal[idx++] = word1[idx1++];
        }

        if (idx2 < len2) {
            pRetVal[idx++] = word2[idx2++];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word1;
        char* word2;
    } testCase[] = {{"abc", "pqr"}, {"ab", "pqrs"}, {"abcd", "pq"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word1 = "abc", word2 = "pqr"
     *  Output: "apbqcr"
     *
     *  Input: word1 = "ab", word2 = "pqrs"
     *  Output: "apbqrs"
     *
     *  Input: word1 = "abcd", word2 = "pq"
     *  Output: "apbqcd"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word1 = \"%s\", word2 = \"%s\"\n", testCase[i].word1, testCase[i].word2);

        pAnswer = mergeAlternately(testCase[i].word1, testCase[i].word2);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
