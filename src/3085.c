#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumDeletions(char* word, int k) {
    int retVal = 0;

#define MAX_LETTER_SIZE (26)  // word consists only of lowercase English letters.

    int frequency[MAX_LETTER_SIZE];
    memset(frequency, 0, sizeof(frequency));
    for (int i = 0; word[i]; i++) {
        frequency[word[i] - 'a']++;
    }

    retVal = strlen(word);
    int a, b, deleted;
    for (int i = 0; i < MAX_LETTER_SIZE; i++) {
        if (frequency[i] == 0) {
            continue;
        }

        a = frequency[i];
        deleted = 0;
        for (int j = 0; j < MAX_LETTER_SIZE; j++) {
            if (frequency[j] == 0) {
                continue;
            }

            b = frequency[j];
            if (a > b) {
                deleted += b;
            } else if (b > a + k) {
                deleted += b - (a + k);
            }
        }

        if (deleted < retVal) {
            retVal = deleted;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
        int k;
    } testCase[] = {{"aabcaba", 0}, {"dabdcbdcdcd", 2}, {"aaabaaa", 2}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "aabcaba", k = 0
     *  Output: 3
     *
     *  Input: word = "dabdcbdcdcd", k = 2
     *  Output: 2
     *
     *  Input: word = "aaabaaa", k = 2
     *  Output: 1
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\", k = %d\n", testCase[i].word, testCase[i].k);

        answer = minimumDeletions(testCase[i].word, testCase[i].k);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
