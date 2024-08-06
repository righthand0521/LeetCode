#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minimumPushes(char* word) {
    int retVal = 0;

    int wordSize = strlen(word);
    int quotient = wordSize / 8;
    int remainder = wordSize % 8;
    retVal = ((quotient << 2) + remainder) * (quotient + 1);

    return retVal;
}

int main(int argc, char** argv) {
#define MAX_SIZE (int)(1e5)
    struct testCaseType {
        char word[MAX_SIZE];
    } testCase[] = {{"abcde"}, {"xycdefghij"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "abcde"
     *  Output: 5
     *
     *  Input: word = "xycdefghij"
     *  Output: 12
     */

    int answer = 0;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = minimumPushes(testCase[i].word);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
