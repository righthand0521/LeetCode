#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LETTERS (26)  // s consists only of lowercase English letters.
int maxDifference(char* s) {
    int retVal = 0;

    int frequency[MAX_LETTERS];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; s[i] != '\0'; ++i) {
        frequency[s[i] - 'a']++;
    }

    int value;
    int maxOdd = 0;
    int minEven = strlen(s);
    for (int i = 0; i < MAX_LETTERS; ++i) {
        value = frequency[i];
        if (value == 0) {
            continue;  // Skip letters that do not appear in the string.
        }

        if (value % 2 == 1) {
            if (value > maxOdd) {
                maxOdd = value;
            }
        } else {
            if (value < minEven) {
                minEven = value;
            }
        }
    }
    retVal = maxOdd - minEven;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (100)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aaaaabbc"}, {"abcabcab"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aaaaabbc"
     *  Output: 3
     *
     *  Input: s = "abcabcab"
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxDifference(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
