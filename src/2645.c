#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://leetcode.com/problems/minimum-additions-to-make-valid-string/solutions/3421831/java-c-python-easy-and-concise-with-explanation/
int addMinimum(char* word) {
    int retVal = 0;

    int count = 0;
    char previousChar = 'z';
    int wordSize = strlen(word);
    int i;
    for (i = 0; i < wordSize; ++i) {
        count += (word[i] <= previousChar);
        previousChar = word[i];
    }
    retVal = 3 * count - wordSize;

    return retVal;
}

int main(int argc, char** argv) {
    struct testCaseType {
        char* word;
    } testCase[] = {{"b"}, {"aaa"}, {"abc"}};
    int numberOfTestCase = sizeof(testCase) / sizeof(testCase[0]);
    /* Example
     *  Input: word = "b"
     *  Output: 2
     *
     *  Input: word = "aaa"
     *  Output: 6
     *
     *  Input: word = "abc"
     *  Output: 0
     */

    int answer;
    int i;
    for (i = 0; i < numberOfTestCase; ++i) {
        printf("Input: word = \"%s\"\n", testCase[i].word);

        answer = addMinimum(testCase[i].word);
        printf("Output: %d\n", answer);

        printf("\n");
    }

    return EXIT_SUCCESS;
}
