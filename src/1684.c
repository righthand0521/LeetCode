#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countConsistentStrings(char *allowed, char **words, int wordsSize) {
    int retVal = 0;

    int i, j;

    int allowedChars[26];  // words[i] and allowed contain only lowercase English letters.
    memset(allowedChars, 0, sizeof(allowedChars));
    int allowedSize = strlen(allowed);
    for (i = 0; i < allowedSize; ++i) {
        allowedChars[allowed[i] - 'a'] = 1;
    }

    int wordSize;
    int isConsistent;
    for (i = 0; i < wordsSize; ++i) {
        isConsistent = 1;
        wordSize = strlen(words[i]);
        for (j = 0; j < wordSize; ++j) {
            if (allowedChars[words[i][j] - 'a'] == 0) {
                isConsistent = 0;
                break;
            }
        }
        if (isConsistent == 1) {
            retVal += 1;
        }
    }

    return retVal;
}

int main(int argc, char **argv) {
    // 1 <= words.length <= 10^4
    // 1 <= allowed.length <= 26
    // 1 <= words[i].length <= 10
    struct testCaseType {
        char allowed[26];
        char *words[10];
        int wordsSize;
    } testCase[] = {{"ab", {"ad", "bd", "aaab", "baa", "badab"}, 4},
                    {"abc", {"a", "b", "c", "ab", "ac", "bc", "abc"}, 7},
                    {"cad", {"cc", "acd", "b", "ba", "bac", "bad", "ac", "d"}, 8}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
     *  Output: 2
     *
     *  Input: allowed = "abc", words = ["a","b","c","ab","ac","bc","abc"]
     *  Output: 7
     *
     *  Input: allowed = "cad", words = ["cc","acd","b","ba","bac","bad","ac","d"]
     *  Output: 4
     */

    int answer;
    int i, j;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: allowed = \"%s\", words = [", testCase[i].allowed);
        for (j = 0; j < testCase[i].wordsSize; ++j) {
            printf("%s\"%s\"", (j == 0) ? "" : ",", testCase[i].words[j]);
        }
        printf("]\n");

        answer = countConsistentStrings(testCase[i].allowed, testCase[i].words, testCase[i].wordsSize);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
