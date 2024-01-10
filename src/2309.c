#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* greatestLetter(char* s) {
    char* pRetVal = NULL;

    pRetVal = (char*)malloc(2 * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (2 * sizeof(char)));

// s consists of lowercase and uppercase English letters.
#define SHIFT_LOWERCASE (0)
#define SHIFT_UPPERCASE (1)
#define MAX_HASHTABLE (26)
    int HashTable[MAX_HASHTABLE];
    memset(HashTable, 0, sizeof(HashTable));

    int len = strlen(s);
    int i;
    for (i = 0; i < len; ++i) {
        if ((s[i] >= 'A') && (s[i] <= 'Z')) {
            HashTable[s[i] - 'A'] |= (1 << SHIFT_UPPERCASE);
        } else if ((s[i] >= 'a') && (s[i] <= 'z')) {
            HashTable[s[i] - 'a'] |= (1 << SHIFT_LOWERCASE);
        }
    }

    for (i = (MAX_HASHTABLE - 1); i >= 0; --i) {
        if (HashTable[i] == ((1 << SHIFT_LOWERCASE) | (1 << SHIFT_UPPERCASE))) {
            snprintf(pRetVal, (2 * sizeof(char)), "%c", i + 'A');
            break;
        }
    }

    return pRetVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
#define MAX_SIZE (1000)
        char s[MAX_SIZE];
    } testCase[] = {{"lEeTcOdE"}, {"arRAzFif"}, {"AbCdEfGhIjK"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);

    char* answer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: s = \"%s\"\n", testCase[i].s);

        answer = greatestLetter(testCase[i].s);
        printf("Output: \"%s\"\n", answer);

        printf("\n");

        free(answer);
        answer = NULL;
    }

    return EXIT_SUCCESS;
}
