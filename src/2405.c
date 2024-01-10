#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partitionString(char *s) {
    int retVal = 0;

    // s consists of only English lowercase letters.
#define MAX_HASHTABLE_SIZE (26)
    int HashTable[MAX_HASHTABLE_SIZE];
    memset(HashTable, 0, sizeof(HashTable));

    int idx;
    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        idx = s[i] - 'a';
        if (HashTable[idx] != 0) {
            memset(HashTable, 0, sizeof(HashTable));
            ++retVal;
        }
        ++HashTable[idx];
    }
    ++retVal;

    return retVal;
}

int main(int argc, char **argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"abacaba"}, {"ssssss"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: s = "abacaba"
     *  Output: 4
     *
     *  Input: s = "ssssss"
     *  Output: 6
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = partitionString(testCase[i].s);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
