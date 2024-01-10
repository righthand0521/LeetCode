#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rearrangeCharacters(char* s, char* target) {
    int retVal = 0;

    // s and target consist of lowercase English letters.
#define MAX_HASH_TABLE_SIZE (26)
    int HashTable[MAX_HASH_TABLE_SIZE][2];
    memset(HashTable, 0, sizeof(HashTable));

    int i;
    int sLen = strlen(s);
    for (i = 0; i < sLen; ++i) {
        ++HashTable[s[i] - 'a'][0];
    }
    int targetLen = strlen(target);
    for (i = 0; i < targetLen; ++i) {
        ++HashTable[target[i] - 'a'][1];
    }

    retVal = fmax(sLen, targetLen);
    for (i = 0; i < MAX_HASH_TABLE_SIZE; ++i) {
        if (HashTable[i][1] == 0) {
            continue;
        }

        retVal = fmin(retVal, (HashTable[i][0] / HashTable[i][1]));
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
#define MAX_STRING_SIZE (100)
#define MAX_TARGET_SIZE (10)
        char s[MAX_STRING_SIZE];
        char target[MAX_TARGET_SIZE];
    } testCase[] = {{"ilovecodingonleetcode", "code"},
                    {"abcba", "abc"},
                    {"abbaccaddaeea", "aaaaa"},
                    {"abc", "abcd"},
                    {"hshac", "h"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", target = \"%s\"\n", testCase[i].s, testCase[i].target);

        answer = rearrangeCharacters(testCase[i].s, testCase[i].target);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
