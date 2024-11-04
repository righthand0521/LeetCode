#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* compressedString(char* word) {
    char* pRetVal = NULL;

    int wordSize = strlen(word);
    int retValSize = 2 * wordSize + 1;
    pRetVal = (char*)malloc(retValSize * sizeof(char));
    if (pRetVal == NULL) {
        perror("malloc");
        return pRetVal;
    }
    memset(pRetVal, 0, (retValSize * sizeof(char)));

    int idx = 0;
    int count = 1;
    int i;
    for (i = 1; i < wordSize; ++i) {
        if ((word[i] == word[i - 1]) && (count < 9)) {
            count++;
            continue;
        }
        idx += snprintf(pRetVal + idx, retValSize - idx, "%d%c", count, word[i - 1]);
        count = 1;
    }
    idx += snprintf(pRetVal + idx, retValSize - idx, "%d%c", count, word[wordSize - 1]);

    return pRetVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(2 * 100000)
    struct testCaseType {
        char word[MAX_SIZE];
    } testCase[] = {{"abcde"}, {"aaaaaaaaaaaaaabb"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "abcde"
     *  Output: "1a1b1c1d1e"
     *
     *  Input: word = "aaaaaaaaaaaaaabb"
     *  Output: "9a5a2b"
     */

    char* pAnswer = NULL;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        pAnswer = compressedString(testCase[i].word);
        printf("Output: \"%s\"\n", pAnswer);

        printf("\n");

        if (pAnswer) {
            free(pAnswer);
            pAnswer = NULL;
        }
    }

    return EXIT_SUCCESS;
}
