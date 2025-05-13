#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULO (int)(1e9 + 7)
#define LETTERSIZE (26)  // s consists only of lowercase English letters.
int lengthAfterTransformations(char* s, int t) {
    int retVal = 0;

    int hashTable[LETTERSIZE];
    memset(hashTable, 0, sizeof(hashTable));
    for (int i = 0; s[i]; i++) {
        hashTable[s[i] - 'a']++;
    }

    int next[LETTERSIZE];
    for (int round = 0; round < t; round++) {
        memset(next, 0, sizeof(next));
        next[0] = hashTable[LETTERSIZE - 1];
        next[1] = (hashTable[LETTERSIZE - 1] + hashTable[0]) % MODULO;
        for (int i = 2; i < LETTERSIZE; i++) {
            next[i] = hashTable[i - 1];
        }
        memcpy(hashTable, next, sizeof(hashTable));
    }

    for (int i = 0; i < LETTERSIZE; i++) {
        retVal = (retVal + hashTable[i]) % MODULO;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
        int t;
    } testCase[] = {{"abcyy", 2}, {"azbk", 1}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abcyy", t = 2
     *  Output: 7
     *
     *  Input: s = "azbk", t = 1
     *  Output: 5
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = %d\n", testCase[i].s, testCase[i].t);

        answer = lengthAfterTransformations(testCase[i].s, testCase[i].t);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
