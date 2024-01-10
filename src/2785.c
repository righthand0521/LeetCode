#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareChar(const void* c1, const void* c2) {
    // ascending order
    return (*(char*)c1 > *(char*)c2);
}
char* sortVowels(char* s) {
    char* pRetVal = s;

    int sSize = strlen(s);
    int i;

    char vowels[sSize];
    memset(vowels, 0, sizeof(vowels));
    unsigned int vowelsIndex = 0;
    for (i = 0; i < sSize; ++i) {
        if ((s[i] == 'A') || (s[i] == 'E') || (s[i] == 'I') || (s[i] == 'O') || (s[i] == 'U') || (s[i] == 'a') ||
            (s[i] == 'e') || (s[i] == 'i') || (s[i] == 'o') || (s[i] == 'u')) {
            vowels[vowelsIndex++] = s[i];
        }
    }
    if (vowelsIndex == 0) {
        return pRetVal;
    }
    qsort(vowels, vowelsIndex, sizeof(char), compareChar);

    vowelsIndex = 0;
    for (i = 0; i < sSize; ++i) {
        if ((s[i] == 'A') || (s[i] == 'E') || (s[i] == 'I') || (s[i] == 'O') || (s[i] == 'U') || (s[i] == 'a') ||
            (s[i] == 'e') || (s[i] == 'i') || (s[i] == 'o') || (s[i] == 'u')) {
            pRetVal[i] = vowels[vowelsIndex++];
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"lEetcOde"}, {"lYmpH"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "lEetcOde"
     *  Output: "lEOtcede"
     *
     *  Input: s = "lYmpH"
     *  Output: "lYmpH"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        pAnswer = sortVowels(testCase[i].s);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
