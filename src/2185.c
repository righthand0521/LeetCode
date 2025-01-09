#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prefixCount(char** words, int wordsSize, char* pref) {
    int retVal = 0;

    int len = strlen(pref);
    int i;
    for (i = 0; i < wordsSize; ++i) {
        if (strncmp(words[i], pref, len) == 0) {
            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
        char* pref;
    } testCase[] = {{{"pay", "attention", "practice", "attend"}, 4, "at"},
                    {{"leetcode", "win", "loops", "success"}, 4, "code"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["pay","attention","practice","attend"], pref = "at"
     *  Output: 2
     *
     *  Input: words = ["leetcode","win","loops","success"], pref = "code"
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("], pref = \"%s\"\n", testCase[i].pref);

        answer = prefixCount(testCase[i].words, testCase[i].wordsSize, testCase[i].pref);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
