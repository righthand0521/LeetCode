#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isIsomorphic(char* s, char* t) {
    bool retVal = false;

    // t.length == s.length
#if 0
    if (strlen(s) != strlen(t))
    {
        return retVal;
    }
#endif

    // s and t consist of any valid ascii character.
#define MAX_HASHTABLE_SIZE (128)
    int HASH_TABLE[2][MAX_HASHTABLE_SIZE] = {0};
    int idx = 1;
    while (*s) {
        HASH_TABLE[0][(unsigned char)*s] =
            (HASH_TABLE[0][(unsigned char)*s] == 0) ? idx : HASH_TABLE[0][(unsigned char)*s];
        HASH_TABLE[1][(unsigned char)*t] =
            (HASH_TABLE[1][(unsigned char)*t] == 0) ? idx : HASH_TABLE[1][(unsigned char)*t];
        if (HASH_TABLE[0][(unsigned char)*s] != HASH_TABLE[1][(unsigned char)*t]) {
            return retVal;
        }

        ++s;
        ++t;
        ++idx;
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (5 * 10000)
    struct testCaseType {
        char s[MAX_SIZE];
        char t[MAX_SIZE];
    } testCase[] = {{"egg", "add"},
                    {"foo", "bar"},
                    {"paper", "title"},
                    {"badc", "baba"},
                    {"abcdefghijklmnopqrstuvwxyzva", "abcdefghijklmnopqrstuvwxyzck"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\", t = \"%s\"\n", testCase[i].s, testCase[i].t);

        answer = isIsomorphic(testCase[i].s, testCase[i].t);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
