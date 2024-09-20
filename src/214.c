#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
void kmp(char* s, int* pPrefixTable) {
    int sSize = strlen(s);

    int length = 0;
    int i;
    for (i = 1; i < sSize; i++) {
        while ((length > 0) && (s[i] != s[length])) {
            length = pPrefixTable[length - 1];
        }

        if (s[i] == s[length]) {
            length++;
        }

        pPrefixTable[i] = length;
    }
}
char* shortestPalindrome(char* s) {
    char* pRetVal = NULL;

    int sSize = strlen(s);
    int i;

    char reversedString[sSize + 1];
    memset(reversedString, 0, sizeof(reversedString));
    for (i = 0; i < sSize; ++i) {
        reversedString[i] = s[sSize - 1 - i];
    }

    int combinedStringSize = 2 * (sSize + 1) + 1;
    char combinedString[combinedStringSize];
    memset(combinedString, 0, sizeof(combinedString));
    snprintf(combinedString, sizeof(combinedString), "%s#%s", s, reversedString);

    int* pPrefixTable = (int*)malloc(combinedStringSize * sizeof(int));
    memset(pPrefixTable, 0, (combinedStringSize * sizeof(int)));
    kmp(combinedString, pPrefixTable);
    int palindromeLength = pPrefixTable[strlen(combinedString) - 1];

    char suffix[sSize + 1];
    memset(suffix, 0, sizeof(suffix));
    strncpy(suffix, reversedString, sSize - palindromeLength);

    pRetVal = (char*)malloc(combinedStringSize * sizeof(char));
    memset(pRetVal, 0, (combinedStringSize * sizeof(char)));
    snprintf(pRetVal, (combinedStringSize * sizeof(char)), "%s%s", suffix, s);

    //
    free(pPrefixTable);
    pPrefixTable = NULL;

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aacecaaa"}, {"abcd"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aacecaaa"
     *  Output: "aaacecaaa"
     *
     *  Input: s = "abcd"
     *  Output: "dcbabcd"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = shortestPalindrome(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        free(pAnswer);
        pAnswer = NULL;
    }

    return EXIT_SUCCESS;
}
