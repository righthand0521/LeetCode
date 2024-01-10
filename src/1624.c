#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int maxLengthBetweenEqualCharacters(char* s) {
    int retVal = -1;

    int sSize = strlen(s);

#define MAX_LETTERS (26)  // s contains only lowercase English letters.
    int hashTable[MAX_LETTERS];
    memset(hashTable, -1, sizeof(hashTable));

    int idx;
    int i;
    for (i = 0; i < sSize; ++i) {
        idx = s[i] - 'a';
        if (hashTable[idx] != -1) {
            retVal = fmax(retVal, i - hashTable[idx] - 1);
        } else {
            hashTable[idx] = i;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (300)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"aa"}, {"abca"}, {"cbzxy"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "aa"
     *  Output: 0
     *
     *  Input: s = "abca"
     *  Output: 2
     *
     *  Input: s = "cbzxy"
     *  Output: -1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = maxLengthBetweenEqualCharacters(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
