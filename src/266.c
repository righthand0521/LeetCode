#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool canPermutePalindrome(char* s) {
    bool retVal = false;

// s consists of only lowercase English letters.
#define MAX_HASHTABLE (26)
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));

    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        ++HashTable[s[i] - 'a'];
    }

    int count = 0;
    for (i = 0; i < MAX_HASHTABLE; ++i) {
        if (HashTable[i] % 2 == 1) {
            ++count;
        }
    }
    if (count <= 1) {
        retVal = true;
    }

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5000)
    struct testCaseType {
        char s[MAX_SIZE];
    } testCase[] = {{"code"}, {"aab"}, {"carerac"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = canPermutePalindrome(testCase[i].s);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
