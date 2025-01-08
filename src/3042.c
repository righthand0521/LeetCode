#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countPrefixSuffixPairs(char** words, int wordsSize) {
    int retVal = 0;

    int wordiSize, wordjSize;
    int i, j;
    for (i = 0; i < wordsSize; ++i) {
        for (j = i + 1; j < wordsSize; ++j) {
            wordiSize = strlen(words[i]);
            wordjSize = strlen(words[j]);
            if (wordiSize > wordjSize) {
                continue;
            }

            if (strncmp(words[j], words[i], wordiSize) != 0) {
                continue;
            }
            if (strncmp(words[j] + (wordjSize - wordiSize), words[i], wordiSize) != 0) {
                continue;
            }

            ++retVal;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100000)
    struct testCaseType {
        char* words[MAX_SIZE];
        int wordsSize;
    } testCase[] = {{{"a", "aba", "ababa", "aa"}, 4}, {{"pa", "papa", "ma", "mama"}, 4}, {{"abab", "ab"}, 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: words = ["a","aba","ababa","aa"]
     *  Output: 4
     *
     *  Input: words = ["pa","papa","ma","mama"]
     *  Output: 2
     *
     *  Input: words = ["abab","ab"]
     *  Output: 0
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: words = [");
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = countPrefixSuffixPairs(testCase[i].words, testCase[i].wordsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
