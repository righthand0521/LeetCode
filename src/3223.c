#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumLength(char* s) {
    int retVal = 0;

#define MAX_LETTTER (26)  // s consists only of lowercase English letters.
    int charFrequency[MAX_LETTTER];
    memset(charFrequency, 0, sizeof(charFrequency));

    int sSize = strlen(s);
    for (int i = 0; i < sSize; ++i) {
        charFrequency[s[i] - 'a']++;
    }

    for (int i = 0; i < MAX_LETTTER; ++i) {
        if (charFrequency[i] == 0) {
            continue;
        }

        if (charFrequency[i] % 2 == 0) {
            retVal += 2;
        } else {
            retVal += 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (2 * 100000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abaacbcbb"}, {"aa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abaacbcbb"
     *  Output: 5
     *
     *  Input: s = "aa"
     *  Output: 2
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = minimumLength(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
