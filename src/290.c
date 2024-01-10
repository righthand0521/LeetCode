#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool wordPattern(char* pattern, char* s) {
    bool retVal = false;

    int i, j;

    // pattern contains only lower-case English letters.
#define HASHTABLE_SIZE (26)
    char* HASH_TABLE[HASHTABLE_SIZE];
    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        HASH_TABLE[i] = NULL;
    }

    // All the words in s are separated by a single space.
#define SEPARATED " "
    char* pStr = strtok(s, SEPARATED);
    while ((pStr != NULL) && (*pattern)) {
        if (HASH_TABLE[(unsigned char)(*pattern) - 'a'] == NULL) {
            HASH_TABLE[(unsigned char)(*pattern) - 'a'] = pStr;
        } else if (strcmp(HASH_TABLE[(unsigned char)(*pattern) - 'a'], pStr) != 0) {
            return retVal;
        }

        ++pattern;
        pStr = strtok(NULL, SEPARATED);
    }
    if ((pStr != NULL) || (*pattern)) {
        return retVal;
    }

    for (i = 0; i < HASHTABLE_SIZE; ++i) {
        if (HASH_TABLE[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < HASHTABLE_SIZE; ++j) {
            if (HASH_TABLE[j] == NULL) {
                continue;
            }
            if (strcmp(HASH_TABLE[i], HASH_TABLE[j]) == 0) {
                return retVal;
            }
        }
    }
    retVal = true;

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_PATTERN_SIZE (300)
#define MAX_S_SIZE (3000)
    struct testCaseType {
        char pattern[MAX_PATTERN_SIZE];
        char s[MAX_S_SIZE];
    } testCase[] = {{"abba", "dog cat cat dog"},
                    {"abba", "dog cat cat fish"},
                    {"aaaa", "dog cat cat dog"},
                    {"abba", "dog dog dog dog"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    bool answer = false;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: pattern = \"%s\", s = \"%s\"\n", testCase[i].pattern, testCase[i].s);

        answer = wordPattern(testCase[i].pattern, testCase[i].s);
        printf("Output: %s\n", (answer == true) ? "true" : "false");

        printf("\n");
    }

    return EXIT_SUCCESS;
}
