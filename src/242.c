#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isAnagram(char* s, char* t) {
    bool retVal = false;

    int sSize = strlen(s);
    int tSize = strlen(t);
    if (sSize != tSize) {
        return retVal;
    }

#define CHAR_RANGE (256)
    int countChar[CHAR_RANGE];
    memset(countChar, 0, sizeof(countChar));
    int i;
    for (i = 0; i < sSize; ++i) {
        countChar[(int)(s[i])]++;
        countChar[(int)(t[i])]--;
    }

    for (i = 0; i < CHAR_RANGE; ++i) {
        if (countChar[i] != 0) {
            return retVal;
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"anagram", "nagaram"}, {"rat", "car"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "anagram", t = "nagaram"
     *  Output: true
     *
     *  Input: s = "rat", t = "car"
     *  Output: false
     */

    bool pAnswer = true;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        pAnswer = isAnagram(testCase[i].s, testCase[i].t);
        printf("Output: %s\n", pAnswer ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
