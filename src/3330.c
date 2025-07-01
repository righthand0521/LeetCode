#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int possibleStringCount(char* word) {
    int retVal = 1;

    int wordSize = strlen(word);
    for (int i = 1; i < wordSize; ++i) {
        if (word[i - 1] == word[i]) {
            retVal += 1;
        }
    }

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
    } testCase[] = {{"abbcccc"}, {"abcd"}, {"aaaa"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "abbcccc"
     *  Output: 5
     *
     *  Input: word = "abcd"
     *  Output: 1
     *
     *  Input: word = "aaaa"
     *  Output: 4
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = possibleStringCount(testCase[i].word);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
